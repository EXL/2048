#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"

#include "2048.h"

VMINT layer_hdl[1];
VMINT screen_width;
VMINT screen_height;
vm_graphic_color color;

// Most MRE functions use wide (UCS2) strings, here's a general purpose buffer for them
VMWCHAR ucs2_str[128];

#define VALUE_MAX_SIZE 5 // "2048\0"
#define SCORE_MAX_SIZE 16 // "Score: 999999..."

#define FIELD_MARGIN (screen_width/20)
#define FIELD_SIZE (screen_width - FIELD_MARGIN*2)
#define TILE_MARGIN (screen_width/80)
#define TILE_SIZE (FIELD_SIZE/LINE_SIZE - TILE_MARGIN*2)

// Sets current drawing color to the given 32-bit ARGB color value. MRE uses
// 16-bit RGB565 color values, so this function converts them.
void set_color(int new_color) {
	int r = (new_color & 0x00FF0000) >> 16;
	int g = (new_color & 0x0000FF00) >> 8;
	int b = new_color & 0x000000FF;
	color.vm_color_565 = VM_COLOR_888_TO_565(r, g, b);
	vm_graphic_setcolor(&color);
}

void draw_tile(int value, int x, int y) {
	const int bg = e_background(value);
	const int fg = e_foreground(value);
	set_color((e_win || e_lose) ? bg - COLOR_FADE : bg);

	// Draw rounded rectangle made up of rectangles and circles
	const int rad = TILE_SIZE/12;
	vm_graphic_fill_rect_ex(layer_hdl[0], x+rad, y, TILE_SIZE - rad*2, TILE_SIZE);
	vm_graphic_fill_rect_ex(layer_hdl[0], x, y+rad, TILE_SIZE, TILE_SIZE - rad*2);
	vm_graphic_fill_ellipse_ex(layer_hdl[0], x, y, rad*2, rad*2);
	vm_graphic_fill_ellipse_ex(layer_hdl[0], x + TILE_SIZE - rad*2, y, rad*2, rad*2);
	vm_graphic_fill_ellipse_ex(layer_hdl[0], x, y + TILE_SIZE - rad*2, rad*2, rad*2);
	vm_graphic_fill_ellipse_ex(layer_hdl[0], x + TILE_SIZE - rad*2, y + TILE_SIZE - rad*2, rad*2, rad*2);

	if (!value) return;

	char num_str[VALUE_MAX_SIZE];
	sprintf(num_str, "%d", value);
	vm_ascii_to_ucs2(ucs2_str, 256, num_str);

	vm_graphic_set_font(value > 1000 ? VM_SMALL_FONT : VM_MEDIUM_FONT);
	const int text_x = x + TILE_SIZE/2 - vm_graphic_get_string_width(ucs2_str)/2;
	const int text_y = y + TILE_SIZE/2 - vm_graphic_get_character_height()/2;

	set_color((e_win || e_lose) ? fg - COLOR_FADE : fg);
	vm_graphic_textout_to_layer(layer_hdl[0], text_x, text_y, ucs2_str, 256);
}

void draw_final() {
	int text_x, text_y;

	if (e_win || e_lose) {
		VMWSTR text = e_win ? u"You won!" : u"Game over!";
		text_x = screen_width/2 - vm_graphic_get_string_width(text)/2;
		text_y = screen_height/2 - vm_graphic_get_character_height()/2;

		set_color(COLOR_FINAL);
		vm_graphic_textout_to_layer(layer_hdl[0], text_x, screen_height/2, text, 256);
	}

	vm_graphic_set_font(VM_SMALL_FONT);
	text_y = screen_height - vm_graphic_get_character_height() - 4;
	set_color((e_win || e_lose) ? COLOR_TEXT - COLOR_FADE : COLOR_TEXT);
	vm_graphic_textout_to_layer(layer_hdl[0], 4, text_y, u"Restart", 256);

	text_x = screen_width - vm_graphic_get_string_width(u"Exit") - 4;
	vm_graphic_textout_to_layer(layer_hdl[0], text_x, text_y, u"Exit", 256);

	char score_str[SCORE_MAX_SIZE];
	sprintf(score_str, "Score: %d", e_score);
	vm_ascii_to_ucs2(ucs2_str, 256, score_str);

	vm_graphic_set_font(VM_LARGE_FONT);
	text_x = screen_width/2 - vm_graphic_get_string_width(ucs2_str)/2;
	vm_graphic_textout_to_layer(layer_hdl[0], text_x, 4, ucs2_str, 256);
}

void draw() {
	set_color((e_win || e_lose) ? COLOR_BOARD - COLOR_FADE : COLOR_BOARD);
	vm_graphic_fill_rect_ex(layer_hdl[0], 0, 0, screen_width, screen_height);

	for (int y = 0; y < LINE_SIZE; y++) {
		for (int x = 0; x < LINE_SIZE; x++) {
			draw_tile(
				e_board[x + y * LINE_SIZE],
				FIELD_MARGIN + TILE_MARGIN/2 + x*(TILE_SIZE + TILE_MARGIN*2),
				screen_height/2 - FIELD_SIZE/2 + y*(TILE_SIZE + TILE_MARGIN*2)
			);
		}
	}
	draw_final();
	vm_graphic_flush_layer(layer_hdl, 1);
}

void load_game() {
	if (vm_file_get_attributes(u"e:\\2048\\2048.sav") == -1) return;

	VMFILE file = vm_file_open(u"e:\\2048\\2048.sav", MODE_READ, 1);
	int unused;
	vm_file_read(file, &e_win, sizeof(int), &unused);
	vm_file_read(file, &e_lose, sizeof(int), &unused);
	vm_file_read(file, &e_score, sizeof(int), &unused);
	vm_file_read(file, &e_board, sizeof(int)*BOARD_SIZE, &unused);
	vm_file_close(file);
}

void save_game() {
	VMFILE file = vm_file_open(u"e:\\2048\\2048.sav", MODE_CREATE_ALWAYS_WRITE, 1);
	int unused;
	vm_file_write(file, &e_win, sizeof(int), &unused);
	vm_file_write(file, &e_lose, sizeof(int), &unused);
	vm_file_write(file, &e_score, sizeof(int), &unused);
	vm_file_write(file, &e_board, sizeof(int)*BOARD_SIZE, &unused);
	vm_file_close(file);
}

void handle_keyevt(VMINT event, VMINT keycode) {
	if (event != VM_KEY_EVENT_UP) return;
	if (keycode == VM_KEY_RIGHT_SOFTKEY || keycode == VM_KEY_BACK) {
		save_game();
		if( layer_hdl[0] != -1 ) {
			vm_graphic_delete_layer(layer_hdl[0]);
		}
		vm_exit_app();
	} else {
		e_key(keycode);
	}
	draw();
}

void handle_penevt(VMINT event, VMINT x, VMINT y) {
}

void handle_sysevt(VMINT message, VMINT param) {
	switch (message) {
		case VM_MSG_CREATE:
		case VM_MSG_ACTIVE:
			// Create base layer that has same size as the screen.
			screen_width = vm_graphic_get_screen_width();
			screen_height = vm_graphic_get_screen_height();
			layer_hdl[0] = vm_graphic_create_layer(0, 0, screen_width, screen_height, VM_NO_TRANS_COLOR);
			vm_graphic_set_clip(0, 0, screen_width, screen_height);
			draw();
			break;
			
		case VM_MSG_PAINT: {
			draw();
			break;
		}
			
		case VM_MSG_INACTIVE:
		case VM_MSG_QUIT:
			save_game();
			if( layer_hdl[0] != -1 ) {
				vm_graphic_delete_layer(layer_hdl[0]);
			}
			break;
	}
}

void vm_main(void) {
	vm_file_mkdir(u"e:\\2048");
	
	// Initialize layer handle
	layer_hdl[0] = -1;

	vm_switch_power_saving_mode(turn_off_mode);
	vm_graphic_set_font(VM_SMALL_FONT);
	
	// Register MRE event handlers
	vm_reg_sysevt_callback(handle_sysevt);
	vm_reg_keyboard_callback(handle_keyevt);
	vm_reg_pen_callback(handle_penevt);

	e_init(VM_KEY_LEFT_SOFTKEY, VM_KEY_LEFT, VM_KEY_RIGHT, VM_KEY_UP, VM_KEY_DOWN);
	load_game();
}