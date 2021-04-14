#include "2048.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <string.h>

#define VALUE_MAX_SIZE      5  /* "2048\0" */
#define SCORE_MAX_SIZE      16 /* "Score: 999999..." */

#define WIDTH               340
#define HEIGHT              400
#define TILE_SIZE           64
#define TILE_MARGIN         16
#define OFFSET_COORD(coord) (coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN)

static XFontStruct *font_small = NULL, *font_middle = NULL, *font_normal = NULL, *font_large = NULL;

static void set_window_settings();
static void draw();

main() {
	Display *display;
	int screen;
	Window window;
	Atom wm_delete_window;
	XEvent event;

	e_init(XK_Escape, XK_Left, XK_Right, XK_Up, XK_Down);

	display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "Cannot open display.\n");
		return 1;
	}
	screen = DefaultScreen(display);
	window = XCreateSimpleWindow(display, RootWindow(display, screen), 50, 50, WIDTH, HEIGHT, 1,
		BlackPixel(display, screen), WhitePixel(display, screen));
	XStoreName(display, window, "2048-Xlib");
	set_window_settings(display, window, "2048-Xlib");
	XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);

	wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &wm_delete_window, 1);

	font_small = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--20-140-100-100-p-105-iso8859-1");
	font_middle = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--25-180-100-100-p-138-iso8859-1");
	font_normal = XLoadQueryFont(display, "-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
	font_large = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");

	while (1) {
		XNextEvent(display, &event);
		if (event.type == Expose) {
			draw(display, screen, window);
		}
		if (event.type == KeyPress) {
			KeySym key = XLookupKeysym(&event.xkey, 0);
			switch (key) {
				case XK_q: goto end;         break;
				case XK_w: e_key(XK_Up);     break;
				case XK_s: e_key(XK_Down);   break;
				case XK_a: e_key(XK_Left);   break;
				case XK_d: e_key(XK_Right);  break;
				case XK_r: e_key(XK_Escape); break;
				default  : e_key(key);       break;
			}
			event.type = Expose;
			XSendEvent(display, window, True, ExposureMask, &event);
		}
		/* Detect closing window by [X] button in the title bar. */
		/* https://stackoverflow.com/a/1186544 */
		if (event.type == ClientMessage && (Atom)event.xclient.data.l[0] == wm_delete_window) {
			break;
		}
	}

end:
	XCloseDisplay(display);
}

static void set_window_settings(display, window, name) Display *display; Window window; char *name; {
	XClassHint classHint;
	XSizeHints sizeHints;
	classHint.res_name = name;
	/* classHint.res_class = name; */
	XSetClassHint(display, window, &classHint);
	sizeHints.flags = PMinSize | PMaxSize;
	sizeHints.min_width = sizeHints.max_width = WIDTH;
	sizeHints.min_height = sizeHints.max_height = HEIGHT;
	XSetWMNormalHints(display, window, &sizeHints);
}

static void draw_tile(display, screen, window, x, y) Display *display; int screen; Window window; int x; int y; {
	int value = e_board[x + y * LINE_SIZE];
	int xOffset = OFFSET_COORD(x), yOffset = OFFSET_COORD(y);
	int w = TILE_SIZE / 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
	XSetForeground(display, DefaultGC(display, screen),
		(e_win || e_lose) ? WhitePixel(display, screen) : BlackPixel(display, screen));
	/* HACK: Emulating XFillRoundedRectangle() method in 6 calls, similar to GTK+1 version. */
	XFillArc(display, window, DefaultGC(display, screen), xOffset, yOffset, rect, rect, -64*180, -64*90);
	XFillArc(display, window, DefaultGC(display, screen), xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90);
	XFillArc(display, window, DefaultGC(display, screen), xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
	XFillArc(display, window, DefaultGC(display, screen), xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
	XFillRectangle(display, window, DefaultGC(display, screen), xOffset, yOffset + qw, TILE_SIZE + 1, rw);
	XFillRectangle(display, window, DefaultGC(display, screen), xOffset + qw, yOffset, rw, TILE_SIZE + 1);
	if (value) {
		int w, h, size;
		char str_value[VALUE_MAX_SIZE];
		XFontStruct *current_font = NULL;
		size = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
		memset(str_value, 0, VALUE_MAX_SIZE);
		if (font_small && font_middle && font_large)
			current_font = (value < 100) ? font_large : (value < 1000) ? font_middle : font_small;
		sprintf(str_value, "%d", value);
		if (current_font)
			XSetFont(display, DefaultGC(display, screen), current_font->fid);
		w = (current_font) ? XTextWidth(current_font, str_value, strlen(str_value)) : 10;
		h = size + 4;
		XSetForeground(display, DefaultGC(display, screen),
			(e_win || e_lose) ? BlackPixel(display, screen) : WhitePixel(display, screen));
		XDrawString(display, window, DefaultGC(display, screen),
			xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2,
			str_value, strlen(str_value));
	}
}

static void draw_final(display, screen, window) Display *display; int screen; Window window; {
	char strScore[SCORE_MAX_SIZE];
	int w, h = 20;
	char *strReset = "ESC to Restart!";
	memset(strScore, 0, SCORE_MAX_SIZE);
	if (e_win || e_lose) {
		char *center = (e_win) ? "You won!" : "Game Over!";
		XSetForeground(display, DefaultGC(display, screen), WhitePixel(display, screen));
		if (font_large)
			XSetFont(display, DefaultGC(display, screen), font_large->fid);
		w = (font_large) ? XTextWidth(font_large, center, strlen(center)) : 50;
		XDrawString(display, window, DefaultGC(display, screen),
			WIDTH / 2 - (w - 3) / 2, HEIGHT - TILE_SIZE / 2 - TILE_MARGIN, center, strlen(center));
	}
	XSetForeground(display, DefaultGC(display, screen),
		(e_win || e_lose) ? WhitePixel(display, screen) : BlackPixel(display, screen));
	if (font_normal)
		XSetFont(display, DefaultGC(display, screen), font_normal->fid);
	XDrawString(display, window, DefaultGC(display, screen), TILE_MARGIN, HEIGHT - h,
		strReset, strlen(strReset));
	sprintf(strScore, "Score: %d", e_score);
	w = (font_normal) ? XTextWidth(font_normal, strScore, strlen(strScore)) : 50;
	XDrawString(display, window, DefaultGC(display, screen), WIDTH - (w - 3) - TILE_MARGIN, HEIGHT - h,
		strScore, strlen(strScore));
}

static void draw(display, screen, window) Display *display; int screen; Window window; {
	int y = 0, x;
	XSetForeground(display, DefaultGC(display, screen),
		(e_win || e_lose) ? BlackPixel(display, screen) : WhitePixel(display, screen));
	XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, WIDTH, HEIGHT);
	for (; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			draw_tile(display, screen, window, x, y);
	draw_final(display, screen, window);
}
