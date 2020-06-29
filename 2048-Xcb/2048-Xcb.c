#include "2048.h"

#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xcb_icccm.h>

#include <X11/keysym.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define VALUE_MAX_SIZE 5 // "2048\0"

static const int WIDTH  = 340;
static const int HEIGHT = 400;
static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static xcb_gc_t font_small, font_middle, font_normal, font_large;
static xcb_font_t font_small_fid, font_middle_fid, font_normal_fid, font_large_fid;

static inline int offset_coords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
static inline unsigned fade_color(unsigned rgb) { return rgb - COLOR_FADE; }

// https://xcb.freedesktop.org/tutorial/fonts/
static xcb_gc_t create_font_gcontext(xcb_connection_t *connection, xcb_window_t window,
                                     xcb_font_t *fontId, const char *font_name) {
	xcb_font_t fid = xcb_generate_id(connection);
	xcb_void_cookie_t font_cookie = xcb_open_font_checked(connection, fid, strlen(font_name), font_name);
	if (xcb_request_check(connection, font_cookie))
		font_cookie = xcb_open_font_checked(connection, fid, strlen("fixed"), "fixed"); // Use Default Fixed Font.
	xcb_gcontext_t font_gcontext = xcb_generate_id(connection);
	uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
	uint32_t values[3] = { COLOR_TEXT, COLOR_BOARD, fid };
	xcb_create_gc_checked(connection, font_gcontext, window, mask, values);
	*fontId = fid;
	return font_gcontext;
}

static void draw_string(xcb_connection_t *connection, xcb_window_t window, xcb_gc_t font,
                        unsigned bkg, unsigned frg, int x, int y, const char *text, int len) {
	xcb_change_gc(connection, font, XCB_GC_BACKGROUND, &bkg);
	xcb_change_gc(connection, font, XCB_GC_FOREGROUND, &frg);
	xcb_image_text_8_checked(connection, len, window, font, x, y, text);
}

// https://github.com/jvvv/9wm-xcb/blob/master/grab.c
static void draw_string_transparent(xcb_connection_t *connection, xcb_window_t window, xcb_gc_t font,
                                    unsigned bkg, unsigned frg, int x, int y, const char *text, int len) {
	xcb_change_gc(connection, font, XCB_GC_BACKGROUND, &bkg);
	xcb_change_gc(connection, font, XCB_GC_FOREGROUND, &frg);
	struct {
		uint8_t nchars;
		int8_t delta;
		uint8_t text[256];
	} item;
	item.nchars = len;
	item.delta = 0;
	int i = 0;
	for (; i < len; ++i)
		item.text[i] = text[i];
	xcb_poly_text_8(connection, window, font, x, y, item.nchars + 2, (const uint8_t *) &item);
}

static void invalidate(xcb_connection_t *connection, xcb_window_t window) {
	xcb_expose_event_t expose_event;
	expose_event.window = window;
	expose_event.response_type = XCB_EXPOSE;
	expose_event.x = 0;
	expose_event.y = 0;
	expose_event.width = WIDTH;
	expose_event.height = HEIGHT;
	xcb_send_event(connection, 0, window, XCB_EVENT_MASK_EXPOSURE, (const char *) &expose_event);
	xcb_flush(connection);
}

xcb_char2b_t *convert_str_to_char2b(const char *str, int len) {
	xcb_char2b_t *ret = malloc(len * sizeof(xcb_char2b_t));
	if (!ret)
		return NULL;
	int i = 0;
	for (; i < len; ++i) {
		ret[i].byte1 = 0;
		ret[i].byte2 = str[i];
	}
	return ret;
}

// https://github.com/enn/xcb-examples/blob/master/font_box.c
// https://github.com/ryanflannery/xtabs/blob/master/xutil.c <= Wrong cast!
void measure_str(xcb_connection_t *connection, const char *str, int len, xcb_font_t font, int *width, int *height) {
	xcb_char2b_t *xcb_str = convert_str_to_char2b(str, len);
	xcb_query_text_extents_reply_t *reply = xcb_query_text_extents_reply(connection,
		xcb_query_text_extents(connection, font, strlen(str), xcb_str), NULL);
	*width = reply->overall_width;
	*height = reply->overall_ascent + reply->overall_descent;
	free(xcb_str);
	free(reply);
}

void measure_str_computed(int len, int *width, int *height) {
	int w, h;
	switch (len) {
		default:
		case 1: w = 18; h = 24; break;
		case 2: w = 36; h = 24; break;
		case 3: w = 39; h = 18; break;
		case 4: w = 40; h = 13; break;
	}
	*width = w - 1;
	*height = h + 4;
}

static void draw_tile(xcb_connection_t *connection, xcb_window_t window, xcb_gcontext_t gcontext,
                      int value, int x, int y, int win, int lose) {
	const unsigned bkg = e_background(value), frg = e_foreground(value);
	const int xOffset = offset_coords(x), yOffset = offset_coords(y);
	const unsigned background = (win || lose) ? fade_color(bkg) : bkg;
	xcb_change_gc(connection, gcontext, XCB_GC_FOREGROUND, &background);
	const int w = TILE_SIZE / 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
	xcb_arc_t arcs[4] = {
		{ xOffset, yOffset, rect, rect, -64*180, -64*90 },
		{ xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90 },
		{ xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90 },
		{ xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90 }
	};
	xcb_poly_fill_arc(connection, window, gcontext, 4, arcs);
	xcb_rectangle_t rects[2] =  {
		{ xOffset, yOffset + qw, TILE_SIZE + 1, rw },
		{ xOffset + qw, yOffset, rw, TILE_SIZE + 1 }
	};
	xcb_poly_fill_rectangle(connection, window, gcontext, 2, rects);
	if (value) {
		const xcb_gc_t font_gc = (value < 100) ? font_large : (value < 1000) ? font_middle : font_small;
		char str_value[VALUE_MAX_SIZE];
		snprintf(str_value, VALUE_MAX_SIZE, "%d", value);
		int w, h, len = strlen(str_value);
		measure_str_computed(len, &w, &h);
		draw_string(connection, window, font_gc, background, ((win || lose) ? fade_color(frg) : frg),
			xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, str_value, len);
	}
}

static void draw_final(xcb_connection_t *connection, xcb_window_t window, int win, int lose) {
	if (win || lose) {
		const char *center = (win) ? "You won!" : "Game Over!";
		int w, h, len = strlen(center);
		measure_str(connection, center, len, font_large_fid, &w, &h);
		draw_string_transparent(connection, window, font_large, 0, COLOR_FINAL,
			WIDTH / 2 - (w - 3) / 2, HEIGHT / 2, center, len);
	}
	const unsigned bkg = ((win || lose) ? fade_color(COLOR_BOARD) : COLOR_BOARD);
	const unsigned frg = ((win || lose) ? fade_color(COLOR_TEXT) : COLOR_TEXT);
	const char *strReset = "ESC to Restart!";
	char strScore[16];
	snprintf(strScore, 16, "Score: %d", e_score);
	int w, h, len = strlen(strScore);
	measure_str(connection, strScore, len, font_normal, &w, &h);
	draw_string(connection, window, font_normal, bkg, frg, TILE_MARGIN, HEIGHT - h, strReset, strlen(strReset));
	draw_string(connection, window, font_normal, bkg, frg, WIDTH - (w - 3) - TILE_MARGIN, HEIGHT - h, strScore, len);
}

static void draw(xcb_connection_t *connection, xcb_window_t window, xcb_gcontext_t gcontext) {
	const unsigned color = (e_win || e_lose) ? fade_color(COLOR_BOARD) : COLOR_BOARD;
	xcb_change_gc(connection, gcontext, XCB_GC_FOREGROUND, &color);
	xcb_rectangle_t screen_rect = { 0, 0, WIDTH, HEIGHT };
	xcb_poly_fill_rectangle(connection, window, gcontext, 1, &screen_rect);
	int y = 0, x;
	for (; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			draw_tile(connection, window, gcontext, e_board[x + y * LINE_SIZE], x, y, e_win, e_lose);
	draw_final(connection, window, e_win, e_lose);
}

int main(void) {
	e_init(XK_Escape, XK_Left, XK_Right, XK_Up, XK_Down);

	xcb_connection_t *connection = xcb_connect(NULL, NULL);
	if (xcb_connection_has_error(connection)) {
		fprintf(stderr, "Cannot open display.\n");
		return 1;
	}
	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
	xcb_gcontext_t gcontext = xcb_generate_id(connection);

	xcb_window_t window = screen->root;
	uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	uint32_t values[2] = { screen->black_pixel, 0 };
	xcb_create_gc(connection, gcontext, window, mask, values);

	window = xcb_generate_id(connection);
	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = COLOR_BOARD;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
	xcb_create_window(connection, screen->root_depth, window, screen->root, 50, 50, WIDTH, HEIGHT, 1,
		XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, values);

	font_small = create_font_gcontext(connection, window, &font_small_fid,
		"-adobe-helvetica-bold-r-normal--20-140-100-100-p-105-iso8859-1");
	font_middle = create_font_gcontext(connection, window, &font_middle_fid,
		"-adobe-helvetica-bold-r-normal--25-180-100-100-p-138-iso8859-1");
	font_normal = create_font_gcontext(connection, window, &font_normal_fid,
		"-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
	font_large = create_font_gcontext(connection, window, &font_large_fid,
		"-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");

	const char *window_title = "2048-Xcb";
	xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
		strlen(window_title), window_title);

	xcb_map_window(connection, window);
	// See: https://stackoverflow.com/a/27771295
	xcb_size_hints_t size_hints;
	xcb_icccm_size_hints_set_min_size(&size_hints, WIDTH, HEIGHT);
	xcb_icccm_size_hints_set_max_size(&size_hints, WIDTH, HEIGHT);
	xcb_icccm_set_wm_size_hints(connection, window, XCB_ATOM_WM_NORMAL_HINTS, &size_hints);
	xcb_flush(connection);

	xcb_key_symbols_t *key_symbols = xcb_key_symbols_alloc(connection);
	int done = 0;
	xcb_generic_event_t *event = NULL;
	while (!done && (event = xcb_wait_for_event(connection))) {
		switch (event->response_type & ~0x80) {
			case XCB_EXPOSE:
				draw(connection, window, gcontext);
				xcb_flush(connection);
				break;
			case XCB_KEY_PRESS: {
				xcb_key_press_event_t *keypress_event = (xcb_key_press_event_t *)(event);
				xcb_keysym_t keysym = xcb_key_symbols_get_keysym(key_symbols, keypress_event->detail, 0);
				switch (keysym) {
					case XK_q:
						done = 1;
						break;
					default:
						e_key(keysym);
						break;
				}
				invalidate(connection, window);
				break;
			}
		}
		free(event);
	}
	xcb_key_symbols_free(key_symbols);
	xcb_close_font(connection, font_large_fid);
	xcb_close_font(connection, font_normal_fid);
	xcb_close_font(connection, font_middle_fid);
	xcb_close_font(connection, font_small_fid);
	xcb_free_gc(connection, font_large);
	xcb_free_gc(connection, font_normal);
	xcb_free_gc(connection, font_middle);
	xcb_free_gc(connection, font_small);
	xcb_disconnect(connection);
	return 0;
}
