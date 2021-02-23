#include "2048.h"

#include <genesis.h>

static void displayBoard() {
    int y = 0, x;
    char tile[5];

    for (; y < LINE_SIZE; ++y)
        for (x = 0; x < LINE_SIZE; ++x) {
            intToStr(e_board[x + y * LINE_SIZE], tile, 5);
            VDP_drawText(tile, x * 6, y * 4);
        }

    /*
    intToStr(j_joy, tile, 5);
    VDP_drawText(tile, 0, y * 5);
    intToStr(j_change, tile, 5);
    VDP_drawText(tile, 6, y * 5);
    intToStr(j_state, tile, 5);
    VDP_drawText(tile, 12, y * 5);
    intToStr(j_pressed, tile, 5);
    VDP_drawText(tile, 18, y * 5);
    */
}

static void joyEvent(u16 joy, u16 changed, u16 state) {
    const u16 value = changed & state;

    if (value & BUTTON_LEFT)
        e_key(BUTTON_LEFT);
    else if (value & BUTTON_RIGHT)
        e_key(BUTTON_RIGHT);
    else if (value & BUTTON_UP)
        e_key(BUTTON_UP);
    else if (value & BUTTON_DOWN)
        e_key(BUTTON_DOWN);
    else if (value & BUTTON_START || value & BUTTON_A || value & BUTTON_B)
        e_key(BUTTON_START);
}

int main(bool hardReset) {
    e_init(BUTTON_START, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN);
//    updateBoard();

    JOY_setEventHandler(joyEvent);

    while(TRUE) {
//        handleInput();

        displayBoard();

        SYS_doVBlankProcess();
    }

    return 0;
}
