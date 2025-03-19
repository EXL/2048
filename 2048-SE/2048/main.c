#define SE

#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\cfg_items.h"

#include "..\..\src\2048.h"

#include "conf_loader.h"
#include "config_data.h"
#include "icon32.h"
#include "icon64.h"
#include "rand.h"

#define BOOKNAME "2048"
#define DISPNAME "2048_Board"
#define SAVED_FILE L"2048.sav"

#define ABOUT_STR "Popular puzzle game for Sony Ericsson A1/A2 as native ELF-application"

#define ELF_BCFG_CONFIG_EVENT 994

#define SCORE_MAX_SIZE 32

#define FONT_H(f) (f & 0xFF)

#define SUB_COLOR(a, b) (0xFF000000 + (a - b))

typedef enum SOFTKEYS_ID
{
    SK_EMPTY,
    SK_NEWGAME,
    SK_SAVEGAME,
    SK_LOADGAME,
    SK_SETTINGS,
    SK_HELP,
    SK_ABOUT,
    SK_LAST,
} SOFTKEYS_ID;

typedef struct MYBOOK : BOOK
{
    GUI *board;
    GUI *feedback;
    TEXTID feedback_txt;
    IMAGEID feedback_icn;
    int key_count;
    int chip_id;
} MYBOOK;

typedef struct DISP_OBJ_2048 : DISP_OBJ
{
    int scr_width;
    int scr_height;
    int margin_const;
    int field_margin;
    int field_size;
    int tile_margin;
    int tile_size;
    int score_y;
    int arc;

    int font_small;
    int font_medium;
    int font_large;

    TEXTID tile_txt;
    TEXTID score_txt;

    int tmp_board[BOARD_SIZE];
    int tmp_win, tmp_lose, tmp_score;
} DISP_OBJ_2048;

typedef struct
{
    BOOK *book;
} MSG;

void elf_exit()
{
    SUBPROC(mfree_adr(), &ELF_BEGIN);
}

int is_my_book(BOOK *book)
{
    return 0 == strcmp(book->xbook->name, BOOKNAME);
}

static int terminate_elf(void *, BOOK *book)
{
    FreeBook(book);
    return 1;
}

static int show_author_info(void *mess, BOOK *book)
{
    MSG *msg = (MSG *)mess;
    MYBOOK *mbk = (MYBOOK *)book;
    MessageBox(EMPTY_TEXTID, STR("v 1.0\n(c) farid\n\n2048 Engine by EXL"), mbk->feedback_icn, 1, 0, msg->book);
    return 1;
}

static int bcfg_config(void *mess, BOOK *book)
{
    FSTAT _fstat;
    wchar_t bcfg_path[256];
    if (fstat(GetDir(DIR_ELFS | MEM_INTERNAL), L"BcfgEdit.elf", &_fstat) == 0)
        wstrcpy(bcfg_path, GetDir(DIR_ELFS | MEM_INTERNAL));
    else if (fstat(GetDir(DIR_ELFS | MEM_EXTERNAL), L"BcfgEdit.elf", &_fstat) == 0)
        wstrcpy(bcfg_path, GetDir(DIR_ELFS | MEM_EXTERNAL));
    else
    {
        MessageBox(EMPTY_TEXTID, STR("BcfgEdit.elf not found"), NOIMAGE, 1, 5000, 0);
        return (1);
    }
    wstrcat(bcfg_path, L"/BcfgEdit.elf");
    elfload(bcfg_path, (void *)successed_config_path, (void *)successed_config_name, 0);
    return (1);
}

static int reconfig_elf(void *mess, BOOK *book)
{
    RECONFIG_EVENT_DATA *reconf = (RECONFIG_EVENT_DATA *)mess;

    if (!wstrcmpi(reconf->path, successed_config_path) && !wstrcmpi(reconf->name, successed_config_name))
    {
        InitConfig();

        MYBOOK *mbk = (MYBOOK *)FindBook(is_my_book);
        DispObject_InvalidateRect(GUIObject_GetDispObject(mbk->board), NULL);
        return 1;
    }
    return 0;
}

int board_gui_on_create(DISP_OBJ_2048 *disp)
{
    e_init(KEY_DEL, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);

    disp->tile_txt = EMPTY_TEXTID;
    disp->score_txt = EMPTY_TEXTID;

    disp->scr_width = Display_GetWidth(0);
    disp->scr_height = Display_GetHeight(0);

    switch (disp->scr_width)
    {
    case 128:
        disp->arc = 4;
        disp->margin_const = 12;
        disp->font_small = FONT_E_12R;
        disp->font_medium = FONT_E_14R;
        disp->font_large = FONT_E_16R;
        disp->score_y = 6;
        break;
    case 176:
        disp->arc = 6;
        disp->margin_const = 16;
        disp->font_small = FONT_E_14R;
        disp->font_medium = FONT_E_16R;
        disp->font_large = FONT_E_18R;
        disp->score_y = 8;
        break;
    default:
        disp->arc = 8;
        disp->margin_const = 20;
        disp->font_small = FONT_E_18R;
        disp->font_medium = FONT_E_24R;
        disp->font_large = FONT_E_30R;
        disp->score_y = 12;
        break;
    }

    disp->field_margin = disp->scr_width / disp->margin_const;
    disp->field_size = disp->scr_width - disp->field_margin * 2;
    disp->tile_margin = disp->scr_width / (disp->margin_const * 4);
    disp->tile_size = disp->field_size / LINE_SIZE - disp->tile_margin * 2;

    if ((GetChipID() & CHIPID_MASK) == CHIPID_DB3350)
    {
        if (disp->scr_height > 320) // Aino =)
            disp->score_y = 48;
        else
            disp->score_y = 20;
    }
    return 1;
}

void board_gui_on_close(DISP_OBJ_2048 *disp)
{
    TextID_Destroy(disp->tile_txt);
    TextID_Destroy(disp->score_txt);
}

void draw_tile(DISP_OBJ_2048 *disp, GC *gc, int value, int x, int y)
{
    int bg_color = e_background(value);
    int fg_color = e_foreground(value);

    if (e_win || e_lose)
    {
        bg_color = SUB_COLOR(bg_color, COLOR_FADE);
        fg_color = SUB_COLOR(fg_color, COLOR_FADE);
    }

    RECT rc;
    rc.x1 = x;
    rc.x2 = x + disp->tile_size;
    rc.y1 = y;
    rc.y2 = y + disp->tile_size;

    if (tile_style)
    {
        GC_SetPenColor(gc, clBlack);
        GC_SetBrushColor(gc, bg_color);
        GC_DrawRoundRect(gc, &rc, disp->arc, disp->arc, 1, 1);
    }
    else
        DrawRect(rc.x1, rc.y1, rc.x2, rc.y2, clBlack, bg_color);

    if (!value)
        return;

    disp->tile_txt = TextID_CreateIntegerID(value);

    int font = disp->font_large;
    if (value > 64)
        font = disp->font_medium;
    if (value > 512)
        font = disp->font_small;

    int text_y = y + (disp->tile_size / 4);

    SetFont(font);
    DrawString(disp->tile_txt, 2, x, text_y, x + disp->tile_size, y + disp->tile_size, 0, 0, fg_color, fg_color);
    TextID_Destroy(disp->tile_txt);
}

void draw_score(DISP_OBJ_2048 *disp)
{
    int text_color = COLOR_TEXT;
    if (e_win || e_lose)
        text_color = SUB_COLOR(text_color, COLOR_FADE);

    wchar_t score_str[SCORE_MAX_SIZE];
    snwprintf(score_str, MAXELEMS(score_str), L"Score: %d", e_score);
    disp->score_txt = TextID_Create(score_str, ENC_UCS2, SCORE_MAX_SIZE);

    SetFont(disp->font_medium);
    DrawString(disp->score_txt, 2, 0, disp->score_y, disp->scr_width, disp->score_y + FONT_H(disp->font_medium), 0, 0, text_color, 0);
    TextID_Destroy(disp->score_txt);

    if (disp->scr_height == 432)
    {
        TEXTID help = STR("Press dpad to move\nPress '0' to undo\nPress 'C' to reset");
        SetFont(disp->font_small);
        DrawString(help, 2, 0, 350, disp->scr_width, disp->scr_height, 0, 0, COLOR_TEXT, 0);
        TextID_Destroy(help);
    }
}

void draw_final(DISP_OBJ_2048 *disp, GC *gc)
{
    TEXTID text = e_win ? STR("You win!") : STR("Game over!");

    SetFont(disp->font_large);
    int text_w = Disp_GetTextIDWidth(text, TextID_GetLength(text));

    RECT rc;
    rc.x1 = disp->scr_width / 2 - text_w / 2 - disp->margin_const;
    rc.x2 = rc.x1 + text_w + (disp->margin_const * 2);
    rc.y1 = disp->scr_height / 2 - FONT_H(disp->font_large);
    rc.y2 = rc.y1 + FONT_H(disp->font_large) * 3;

    int pen_color = (int)SUB_COLOR(COLOR_FINAL, COLOR_FADE);
    GC_SetPenColor(gc, pen_color);
    GC_SetBrushColor(gc, COLOR_OVERLAY);
    GC_DrawRoundRect(gc, &rc, disp->arc, disp->arc, 1, 1);

    SetFont(disp->font_large);
    DrawString(text, 2, 0, disp->scr_height / 2, disp->scr_width, disp->scr_height, 0, 0, COLOR_FINAL, COLOR_FINAL);
    TextID_Destroy(text);
}

void board_gui_on_redraw(DISP_OBJ_2048 *disp, int, int, int)
{
    GC *gc = get_DisplayGC();

    for (int y = 0; y < LINE_SIZE; y++)
    {
        for (int x = 0; x < LINE_SIZE; x++)
        {
            draw_tile(disp, gc,
                      e_board[x + y * LINE_SIZE],
                      disp->field_margin + disp->tile_margin / 2 + x * (disp->tile_size + disp->tile_margin * 2),
                      disp->scr_height / 2 - disp->field_size / 2 + y * (disp->tile_size + disp->tile_margin * 2));
        }
    }
    draw_score(disp);

    if (e_win || e_lose)
        draw_final(disp, gc);
}

void save_state(DISP_OBJ_2048 *disp)
{
    memset(disp->tmp_board, 0, BOARD_SIZE * sizeof(int));
    memcpy(disp->tmp_board, e_board, BOARD_SIZE * sizeof(int));
    disp->tmp_win = e_win;
    disp->tmp_lose = e_lose;
    disp->tmp_score = e_score;
}

void load_state(DISP_OBJ_2048 *disp)
{
    memcpy(e_board, disp->tmp_board, BOARD_SIZE * sizeof(int));
    e_win = disp->tmp_win;
    e_lose = disp->tmp_lose;
    e_score = disp->tmp_score;
}

void board_gui_on_key(DISP_OBJ_2048 *disp, int scan_code, int count, int repeat_num, int key_mode)
{
    if (key_mode == KBD_SHORT_PRESS)
    {
        // Register another keys =)
        if (scan_code == KEY_UP || scan_code == KEY_DIGITAL_0 + 2)
        {
            save_state(disp);
            e_key(KEY_UP);
        }
        else if (scan_code == KEY_LEFT || scan_code == KEY_DIGITAL_0 + 4)
        {
            save_state(disp);
            e_key(KEY_LEFT);
        }
        else if (scan_code == KEY_RIGHT || scan_code == KEY_DIGITAL_0 + 6)
        {
            save_state(disp);
            e_key(KEY_RIGHT);
        }
        else if (scan_code == KEY_DOWN || scan_code == KEY_DIGITAL_0 + 8)
        {
            save_state(disp);
            e_key(KEY_DOWN);
        }
        else if (scan_code == KEY_DIGITAL_0)
        {
            load_state(disp);
        }
        else if (scan_code == KEY_DEL)
        {
            e_key(scan_code);
        }
        DispObject_InvalidateRect(disp, NULL);
    }
}

void board_gui_on_layout(DISP_OBJ_2048 *disp, void *layoutstruct)
{
    DispObject_SetLayerColor(disp, COLOR_BOARD);
}

void board_gui_constr(DISP_DESC *desc)
{
    DISP_DESC_SetName(desc, DISPNAME);
    DISP_DESC_SetSize(desc, sizeof(DISP_OBJ_2048));
    DISP_DESC_SetOnCreate(desc, (DISP_OBJ_ONCREATE_METHOD)board_gui_on_create);
    DISP_DESC_SetOnClose(desc, (DISP_OBJ_ONCLOSE_METHOD)board_gui_on_close);
    DISP_DESC_SetOnRedraw(desc, (DISP_OBJ_ONREDRAW_METHOD)board_gui_on_redraw);
    DISP_DESC_SetOnKey(desc, (DISP_OBJ_ONKEY_METHOD)board_gui_on_key);
    DISP_DESC_SetOnLayout(desc, (DISP_OBJ_ONLAYOUT_METHOD)board_gui_on_layout);
}

void board_gui_destr(GUI *)
{
}

void board_gui_callback(DISP_OBJ *, void *, GUI *gui)
{
    if (e_win || e_lose)
    {
        for (int i = SK_SAVEGAME; i < SK_LAST; i++)
        {
            GUIObject_SoftKeys_SetVisible(gui, i, FALSE);
        }
    }
    else
    {
        for (int i = SK_NEWGAME; i < SK_LAST; i++)
        {
            GUIObject_SoftKeys_SetVisible(gui, i, TRUE);
        }
    }
}

GUI *CreateBoardGUI(MYBOOK *mbk)
{
    GUI *board_gui = (GUI *)malloc(sizeof(GUI));
    if (!GUIObject_Create(board_gui, board_gui_destr, board_gui_constr, mbk, board_gui_callback, 0, sizeof(GUI)))
    {
        mfree(board_gui);
        return NULL;
    }

    if (mbk)
        BookObj_AddGUIObject(mbk, board_gui);

    if (Display_GetHeight(0) < 432)
        GUIObject_SetStyle(board_gui, UI_OverlayStyle_TrueFullScreen);

    GUIObject_SetTitleType(board_gui, UI_TitleMode_None);
    if (mbk->chip_id != CHIPID_DB2000 || mbk->chip_id != CHIPID_DB2010)
        GUIObject_SoftKeys_RemoveBackground(board_gui);
    return board_gui;
}

void gui_on_back(BOOK *book, GUI *gui)
{
    FreeBook(book);
}

void gui_on_reset(BOOK *book, GUI *gui)
{
    MYBOOK *mbk = (MYBOOK *)book;
    e_key(KEY_DEL);
    for (int i = SK_NEWGAME; i < SK_LAST; i++)
    {
        GUIObject_SoftKeys_SetVisible(mbk->board, i, TRUE);
    }
    DispObject_InvalidateRect(GUIObject_GetDispObject(mbk->board), NULL);
}

void gui_on_save(BOOK *book, GUI *gui)
{
    int file = _fopen(GetDir(DIR_INI), SAVED_FILE, FSX_O_RDWR, FSX_S_IREAD | FSX_S_IWRITE, 0);
    fwrite(file, &e_win, sizeof(int));
    fwrite(file, &e_lose, sizeof(int));
    fwrite(file, &e_score, sizeof(int));
    fwrite(file, &e_board, sizeof(int) * BOARD_SIZE);
    fclose(file);

    MessageBox(EMPTY_TEXTID, STR("Saved!"), NOIMAGE, 1, 0, NULL);
}

void gui_on_load(BOOK *book, GUI *gui)
{
    FSTAT _fstat;
    if (fstat(GetDir(DIR_INI), SAVED_FILE, &_fstat) < 0)
    {
        MessageBox(EMPTY_TEXTID, STR("No saved file found!"), NOIMAGE, 1, 0, NULL);
        return;
    }

    int file = _fopen(GetDir(DIR_INI), SAVED_FILE, FSX_O_RDONLY, FSX_S_IREAD | FSX_S_IWRITE, 0);
    fread(file, &e_win, sizeof(int));
    fread(file, &e_lose, sizeof(int));
    fread(file, &e_score, sizeof(int));
    fread(file, &e_board, sizeof(int) * BOARD_SIZE);
    fclose(file);

    MessageBox(EMPTY_TEXTID, STR("Loaded!"), NOIMAGE, 1, 0, NULL);

    MYBOOK *mbk = (MYBOOK *)book;
    DispObject_InvalidateRect(GUIObject_GetDispObject(mbk->board), NULL);
}

void gui_on_settings(BOOK *book, GUI *gui)
{
    bcfg_config(NULL, NULL);
}

void help_on_close(BOOK *book, GUI *gui)
{
    MYBOOK *mbk = (MYBOOK *)book;
    if (mbk->feedback)
    {
        GUIObject_Destroy(mbk->feedback);
        mbk->feedback = 0;
    }
    mbk->key_count = 0;
    TextID_Destroy(mbk->feedback_txt);
}

void constr_help_str(MYBOOK *mbk)
{
    TEXTID spacer = 0x78000000 + ':';

    TEXTID keys[18];
    keys[0] = KeyCode2Name(KEY_UP);
    keys[1] = spacer;
    keys[2] = STR("Move tile up\n");

    keys[3] = KeyCode2Name(KEY_LEFT);
    keys[4] = spacer;
    keys[5] = STR("Move tile left\n");

    keys[6] = KeyCode2Name(KEY_RIGHT);
    keys[7] = spacer;
    keys[8] = STR("Move tile right\n");

    keys[9] = KeyCode2Name(KEY_DOWN);
    keys[10] = spacer;
    keys[11] = STR("Move tile down\n");

    keys[12] = KeyCode2Name(KEY_DIGITAL_0);
    keys[13] = spacer;
    keys[14] = STR("undo game\n");

    keys[15] = KeyCode2Name(KEY_DEL);
    keys[16] = spacer;
    keys[17] = STR("reset game\n");

    mbk->feedback_txt = TextID_Create(keys, ENC_TEXTID, MAXELEMS(keys));
}

void gui_on_help(BOOK *book, GUI *gui)
{
    MYBOOK *mbk = (MYBOOK *)book;
    constr_help_str(mbk);

    mbk->feedback = TextFeedbackWindow(mbk, 0);
    Feedback_SetTextExtended(mbk->feedback, mbk->feedback_txt, 0);
    GUIObject_SetStyle(mbk->feedback, UI_OverlayStyle_Default);
    GUIObject_SoftKeys_SetAction(mbk->feedback, ACTION_BACK, help_on_close);
    GUIObject_Show(mbk->feedback);
}

void about_on_easteregg(BOOK *book, int key, int unk, int unk2)
{
    MYBOOK *mbk = (MYBOOK *)book;

    if (key == KEY_DIGITAL_0)
        mbk->key_count++;
    else
        mbk->key_count = 0;

    if (mbk->key_count > 4)
    {
        mbk->feedback_txt = STR("2048\nv1.0\n\n(c) farid\n\n2048 Engine by EXL");
        Feedback_SetTextExtended(mbk->feedback, mbk->feedback_txt, 0);
    }
}

void about_on_close(BOOK *book)
{
    MYBOOK *mbk = (MYBOOK *)book;
    if (mbk->feedback)
    {
        GUIObject_Destroy(mbk->feedback);
        mbk->feedback = 0;
    }
    mbk->key_count = 0;
    TextID_Destroy(mbk->feedback_txt);
}

void gui_on_about(BOOK *book, GUI *gui)
{
    MYBOOK *mbk = (MYBOOK *)book;

    mbk->feedback_txt = STR(ABOUT_STR);

    mbk->feedback = TextFeedbackWindow(mbk, 0);
    Feedback_SetTextExtended(mbk->feedback, mbk->feedback_txt, 0);
    Feedback_SetKeyHook(mbk->feedback, about_on_easteregg);
    Feedback_SetTimeout(mbk->feedback, 10000);
    Feedback_SetOnClose(mbk->feedback, about_on_close);
    GUIObject_SetStyle(mbk->feedback, UI_OverlayStyle_Default);
    GUIObject_Show(mbk->feedback);
}

void gui_on_nothing(BOOK *book, GUI *gui)
{
}

static int maindisplay_enter_action(void *r0, BOOK *book)
{
    MYBOOK *mbk = (MYBOOK *)book;
    mbk->board = CreateBoardGUI(mbk);
    GUIObject_SoftKeys_SetText(mbk->board, SK_EMPTY, 0x78000020); // Tricky hack to hide center softkeys =)
    GUIObject_SoftKeys_SetAction(mbk->board, SK_EMPTY, gui_on_nothing);
    GUIObject_SoftKeys_SetText(mbk->board, SK_NEWGAME, STR("New.."));
    GUIObject_SoftKeys_SetAction(mbk->board, SK_NEWGAME, gui_on_reset);
    GUIObject_SoftKeys_SetText(mbk->board, SK_SAVEGAME, STR("Save.."));
    GUIObject_SoftKeys_SetAction(mbk->board, SK_SAVEGAME, gui_on_save);
    GUIObject_SoftKeys_SetText(mbk->board, SK_LOADGAME, STR("Load.."));
    GUIObject_SoftKeys_SetAction(mbk->board, SK_LOADGAME, gui_on_load);
    GUIObject_SoftKeys_SetText(mbk->board, SK_SETTINGS, STR("Settings"));
    GUIObject_SoftKeys_SetAction(mbk->board, SK_SETTINGS, gui_on_settings);
    GUIObject_SoftKeys_SetText(mbk->board, SK_HELP, STR("Help"));
    GUIObject_SoftKeys_SetAction(mbk->board, SK_HELP, gui_on_help);
    GUIObject_SoftKeys_SetText(mbk->board, SK_ABOUT, STR("About"));
    GUIObject_SoftKeys_SetAction(mbk->board, SK_ABOUT, gui_on_about);
    GUIObject_SoftKeys_SetText(mbk->board, ACTION_BACK, STR("Exit"));
    GUIObject_SoftKeys_SetAction(mbk->board, ACTION_BACK, gui_on_back);
    GUIObject_Show(mbk->board);
    return 1;
}

const PAGE_MSG My_Main_Page[] @ "DYN_PAGE" =
{
    PAGE_ENTER_EVENT_TAG, maindisplay_enter_action,
    NIL_EVENT_TAG, NULL
};

const PAGE_DESC MyMain_Page = {"2048_Main_Page", 0, My_Main_Page};

const PAGE_MSG My_Base_Page[] @ "DYN_PAGE" =
{
    ELF_SHOW_INFO_EVENT, show_author_info,
    ELF_TERMINATE_EVENT, terminate_elf,
    ELF_BCFG_CONFIG_EVENT, bcfg_config,
    ELF_RECONFIG_EVENT, reconfig_elf,
    NIL_EVENT_TAG, NULL
};

const PAGE_DESC MyBase_Page = {"2048_Base_Page", 0, My_Base_Page};

void on_close_book(BOOK *book)
{
    MYBOOK *mbk = (MYBOOK *)book;
    if (mbk->board)
    {
        GUIObject_Destroy(mbk->board);
        mbk->board = 0;
    }
    if (mbk->feedback)
    {
        GUIObject_Destroy(mbk->feedback);
        mbk->feedback = 0;
    }
    TextID_Destroy(mbk->feedback_txt);
    ImageID_Free(mbk->feedback_icn);
    SUBPROC(elf_exit);
}

void create_2048_book()
{
    MYBOOK *mbk = (MYBOOK *)malloc(sizeof(MYBOOK));
    memset(mbk, 0, sizeof(MYBOOK));
    if (!CreateBook(mbk, on_close_book, &MyBase_Page, BOOKNAME, NO_BOOK_ID, NULL))
    {
        mfree(mbk);
        return;
    }
    mbk->board = 0;
    mbk->feedback = 0;
    mbk->key_count = 0;
    mbk->chip_id = GetChipID() & CHIPID_MASK;

    if (Display_GetWidth(0) == 240)
    {
        void *picon64 = malloc(sizeof(icon64_png));
        memcpy(picon64, icon64_png, sizeof(icon64_png));
        ImageID_GetIndirect(picon64, sizeof(icon64_png), NULL, L"png", &mbk->feedback_icn);
    }
    else
    {
        void *picon32 = malloc(sizeof(icon32_png));
        memcpy(picon32, icon32_png, sizeof(icon32_png));
        ImageID_GetIndirect(picon32, sizeof(icon32_png), NULL, L"png", &mbk->feedback_icn);
    }

    BookObj_GotoPage(mbk, &MyMain_Page);
}

int main()
{
    MYBOOK *mbk = (MYBOOK *)FindBook(is_my_book);
    if (mbk)
    {
        BookObj_SetFocus(mbk, 0);
        SUBPROC(elf_exit);
    }
    else
    {
        InitConfig();
        create_2048_book();
    }

    return (0);
}
