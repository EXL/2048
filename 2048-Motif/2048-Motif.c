// http://www.ist.co.uk/motif/books/vol6A/ch-11.fm.html

#include "2048.h"

#include <Xm/Xm.h>
#include <Xm/DrawingA.h>

#include <stdlib.h>
#include <stdio.h>

#define VALUE_MAX_SIZE 5 // "2048\0"

static const int WIDTH  = 340;
static const int HEIGHT = 400;
static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static XtAppContext context = NULL;
static Pixmap pixmap = 0;
static XFontStruct *font_small = NULL, *font_middle = NULL, *font_normal = NULL, *font_large = NULL;

static inline int offset_coords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
static inline unsigned fade_color(unsigned rgb) { return rgb - COLOR_FADE; }

static void quit() {
	XtDestroyApplicationContext(context);
	exit(0);
}

static void draw_tile(Display *display, Pixmap pixmap, GC gc, int value, int x, int y, int win, int lose) {
	const unsigned bkg = e_background(value), frg = e_foreground(value);
	const int xOffset = offset_coords(x), yOffset = offset_coords(y);
	XSetForeground(display, gc, (win || lose) ? fade_color(bkg) : bkg);
	// HACK: Emulating XFillRoundedRectangle() method in 6 calls, similar to Xlib version.
	const int w = TILE_SIZE / 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
	XFillArc(display, pixmap, gc, xOffset, yOffset, rect, rect, -64*180, -64*90);
	XFillArc(display, pixmap, gc, xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90);
	XFillArc(display, pixmap, gc, xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
	XFillArc(display, pixmap, gc, xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
	XFillRectangle(display, pixmap, gc, xOffset, yOffset + qw, TILE_SIZE, rw);
	XFillRectangle(display, pixmap, gc, xOffset + qw, yOffset, rw, TILE_SIZE);
	if (value) {
		XFontStruct *current_font = NULL;
		if (font_small && font_middle && font_large)
			current_font = (value < 100) ? font_large : (value < 1000) ? font_middle : font_small;
		const int size = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
		char str_value[VALUE_MAX_SIZE];
		snprintf(str_value, VALUE_MAX_SIZE, "%d", value);
		if (current_font)
			XSetFont(display, gc, current_font->fid);
		const int w = (current_font) ? XTextWidth(current_font, str_value, strlen(str_value)) : 10, h = size + 4;
		XSetForeground(display, gc, (win || lose) ? fade_color(frg) : frg);
		XDrawString(display, pixmap, gc,
			xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2,
			str_value, strlen(str_value));
	}
}

static void draw_final(Display *display, Pixmap pixmap, GC gc, int win, int lose) {
	if (win || lose) {
		XSetForeground(display, gc, COLOR_FINAL);
		if (font_large)
			XSetFont(display, gc, font_large->fid);
		const char *center = (win) ? "You won!" : "Game Over!";
		const int w = (font_large) ? XTextWidth(font_large, center, strlen(center)) : 50;
		XDrawString(display, pixmap, gc, WIDTH / 2 - (w - 3) / 2, HEIGHT / 2,
			center, strlen(center));
	}
	XSetForeground(display, gc, (win || lose) ? fade_color(COLOR_TEXT) : COLOR_TEXT);
	const char *strReset = "ESC to Restart!";
	if (font_normal)
		XSetFont(display, gc, font_normal->fid);
	const int h = 20;
	XDrawString(display, pixmap, gc, TILE_MARGIN, HEIGHT - h,
		strReset, strlen(strReset));
	char strScore[16];
	snprintf(strScore, 16, "Score: %d", e_score);
	const int w = (font_normal) ? XTextWidth(font_normal, strScore, strlen(strScore)) : 50;
	XDrawString(display, pixmap, gc, WIDTH - (w - 3) - TILE_MARGIN, HEIGHT - h,
		strScore, strlen(strScore));
}

static void general_callback(Widget widget, _X_UNUSED XtPointer client_data, XtPointer call_data) {
	XmDrawingAreaCallbackStruct *dacs = (XmDrawingAreaCallbackStruct *) call_data;
	XEvent *event = dacs->event;
	Window window = XtWindow(widget);
	if (dacs->reason == XmCR_INPUT) {
		if (event->xany.type == KeyPress) {
			KeySym keysym = XLookupKeysym((XKeyEvent *) event, 0);
			if (keysym == XK_q)
				quit();
			else {
				e_key(keysym);
				// Source: http://users.polytech.unice.fr/~buffa/cours/X11_Motif/motif-faq/part6/faq-doc-2.html
				XmDrawingAreaCallbackStruct da_struct;
				da_struct.reason = XmCR_EXPOSE;
				da_struct.event = (XEvent *) event;
				da_struct.window = window;
				XtCallCallbacks(widget, XmNexposeCallback, (XtPointer) &da_struct);
			}
		}
	} else if (dacs->reason == XmCR_EXPOSE) {
		Display *display = event->xany.display;
		GC gc;
		XtVaGetValues(widget, XmNuserData, &gc, NULL);
		XSetForeground(display, gc, (e_win || e_lose) ? fade_color(COLOR_BOARD) : COLOR_BOARD);
		XFillRectangle(display, pixmap, gc, 0, 0, WIDTH, HEIGHT);
		int y = 0, x;
		for (; y < LINE_SIZE; ++y) {
			for (x = 0; x < LINE_SIZE; ++x)
				draw_tile(display, pixmap, gc, e_board[x + y * LINE_SIZE], x, y, e_win, e_lose);
		}
		draw_final(display, pixmap, gc, e_win, e_lose);
		XCopyArea(display, pixmap, window, gc, 0, 0, WIDTH, HEIGHT, 0, 0);
	}
}

int main(int argc, char *argv[]) {
	e_init(XK_Escape, XK_Left, XK_Right, XK_Up, XK_Down);

	XtSetLanguageProc(NULL, NULL, NULL);
	Widget top = XtVaOpenApplication(&context, "2048-Motif", NULL, 0, &argc, argv, NULL, sessionShellWidgetClass,
		XmNwidth, WIDTH, XmNheight, HEIGHT, NULL);
	Widget drawing = XmCreateDrawingArea(top, "drawing", NULL, 0);
	Display *display = XtDisplay(drawing);
	Screen *screen = XtScreen(drawing);
	GC gc = XCreateGC(display, RootWindowOfScreen(screen), 0, NULL);
	XtVaSetValues(drawing, XmNuserData, gc, NULL);
	XtManageChild(drawing);
	pixmap = XCreatePixmap(display, RootWindowOfScreen(screen), WIDTH, HEIGHT, DefaultDepthOfScreen(screen));
	XSetForeground(display, gc, COLOR_BOARD);
	XFillRectangle(display, pixmap, gc, 0, 0, WIDTH, HEIGHT);

	XtAddCallback(drawing, XmNinputCallback, general_callback, NULL);
	XtAddCallback(drawing, XmNexposeCallback, general_callback, NULL);

	font_small = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--20-140-100-100-p-105-iso8859-1");
	font_middle = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--25-180-100-100-p-138-iso8859-1");
	font_normal = XLoadQueryFont(display, "-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
	font_large = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");

	XtRealizeWidget(top);

	XtAppMainLoop(context);
	return 0;
}
