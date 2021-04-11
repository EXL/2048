// https://ergodic.ugr.es/cphys_pedro/unix/athena8.html
// https://ergodic.ugr.es/cphys_pedro/unix/athena9.html

#include "2048.h"

#include <X11/Intrinsic.h>
#include <X11/Xaw/Box.h>
#include <X11/Core.h>
#include <X11/StringDefs.h>
#include <X11/keysym.h>

#include <stdio.h>
#include <stdlib.h>

#define VALUE_MAX_SIZE 5  /* "2048\0" */
#define SCORE_MAX_SIZE 16 /* "Score: 999999..." */

static int WIDTH  = 340;
static int HEIGHT = 400;
static int TILE_SIZE = 64;
static int TILE_MARGIN = 16;

static GC gc = NULL;
static Atom wm_delete_window = 0;
static XtAppContext context = NULL;
static XFontStruct *font_small = NULL, *font_middle = NULL, *font_normal = NULL, *font_large = NULL;

static int offset_coords(coord) int coord; { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
static unsigned fade_color(rgb) unsigned rgb; { return rgb - COLOR_FADE; }

static void quit() {
	XtDestroyApplicationContext(context);
	exit(0);
}

static void set_window_settings(display, window, width, height) Display *display; Window window; int width; int height; {
	XSizeHints sizeHints;
	sizeHints.flags = PMinSize | PMaxSize;
	sizeHints.min_width = sizeHints.max_width = width;
	sizeHints.min_height = sizeHints.max_height = height;
	XSetWMNormalHints(display, window, &sizeHints);
}

static void draw_tile(display, window, value, x, y, win, lose) Display *display; Window window; int value; int x; int y; int win; int lose; {
	unsigned bkg = e_background(value), frg = e_foreground(value);
	int xOffset = offset_coords(x), yOffset = offset_coords(y);
	int w = TILE_SIZE / 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
	XSetForeground(display, gc, (win || lose) ? fade_color(bkg) : bkg);
	// HACK: Emulating XFillRoundedRectangle() method in 6 calls, similar to Xlib version.
	XFillArc(display, window, gc, xOffset, yOffset, rect, rect, -64*180, -64*90);
	XFillArc(display, window, gc, xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90);
	XFillArc(display, window, gc, xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
	XFillArc(display, window, gc, xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
	XFillRectangle(display, window, gc, xOffset, yOffset + qw, TILE_SIZE + 1, rw);
	XFillRectangle(display, window, gc, xOffset + qw, yOffset, rw, TILE_SIZE + 1);
	if (value) {
		char str_value[VALUE_MAX_SIZE];
		int w, h, size;
		XFontStruct *current_font = NULL;
		memset(str_value, 0, VALUE_MAX_SIZE);
		size = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
		if (font_small && font_middle && font_large)
			current_font = (value < 100) ? font_large : (value < 1000) ? font_middle : font_small;
		sprintf(str_value, "%d", value);
		if (current_font)
			XSetFont(display, gc, current_font->fid);
		w = (current_font) ? XTextWidth(current_font, str_value, strlen(str_value)) : 10;
		h = size + 4;
		XSetForeground(display, gc, (win || lose) ? fade_color(frg) : frg);
		XDrawString(display, window, gc,
			xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2,
			str_value, strlen(str_value));
	}
}

static void draw_final(display, window, win, lose) Display *display; Window window; int win; int lose; {
	char strScore[39];
	int w;
	char *strReset = "ESC to Restart!";
	int h = 20;
	if (win || lose) {
		int w;
		char *center = (win) ? "You won!" : "Game Over!";
		XSetForeground(display, gc, COLOR_FINAL);
		if (font_large)
			XSetFont(display, gc, font_large->fid);
		w = (font_large) ? XTextWidth(font_large, center, strlen(center)) : 50;
		XDrawString(display, window, gc, WIDTH / 2 - (w - 3) / 2, HEIGHT / 2,
			center, strlen(center));
	}
	memset(strScore, 0, SCORE_MAX_SIZE);
	XSetForeground(display, gc, (win || lose) ? fade_color(COLOR_TEXT) : COLOR_TEXT);
	if (font_normal)
		XSetFont(display, gc, font_normal->fid);
	XDrawString(display, window, gc, TILE_MARGIN, HEIGHT - h,
		strReset, strlen(strReset));
	sprintf(strScore, "Score: %d", e_score);
	w = (font_normal) ? XTextWidth(font_normal, strScore, strlen(strScore)) : 50;
	XDrawString(display, window, gc, WIDTH - (w - 3) - TILE_MARGIN, HEIGHT - h,
		strScore, strlen(strScore));
}

static void expose_event(widget, client, event) Widget widget; XtPointer client; XExposeEvent *event; {
	int y, x;
	Display *display = XtDisplay(widget);
	Window window = XtWindow(widget);
	XSetForeground(display, gc, (e_win || e_lose) ? fade_color(COLOR_BOARD) : COLOR_BOARD);
	XFillRectangle(display, window, gc, 0, 0, WIDTH, HEIGHT);
	for (y = 0; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			draw_tile(display, window, e_board[x + y * LINE_SIZE], x, y, e_win, e_lose);
	draw_final(display, window, e_win, e_lose);
}

static void key_press_event(widget, client, event) Widget widget; XtPointer client; XKeyPressedEvent *event; {
	KeySym keysym = XtGetActionKeysym((XEvent *) event, NULL);
	if (keysym == XK_q)
		quit();
	else {
		e_key(keysym);
		event->type = Expose;
		//XtDispatchEventToWidget(widget, (XEvent *) event);
	}
}

static void client_message_event(widget, client, event) Widget widget; XtPointer client; XEvent *event; {
	if (event->type == ClientMessage && (Atom)event->xclient.data.l[0] == wm_delete_window)
		quit();
}

int main(argc, argv) int argc; char *argv[]; {
	int n, m;
	Display *display;
	Arg box_args[2];
	Arg core_args[4];

	Widget top = XtAppInitialize(&context, "2048-Xaw", NULL, 0, &argc, argv, NULL, NULL, 0);
	Widget box = XtCreateManagedWidget("box", boxWidgetClass, top, NULL, 0);
	Widget drawing = XtCreateManagedWidget("core", coreWidgetClass, box, NULL, 0);

	e_init(XK_Escape, XK_Left, XK_Right, XK_Up, XK_Down);

	n = 0;
	XtSetArg(core_args[n], XtNwidth, WIDTH); n++;
	XtSetArg(core_args[n], XtNheight, HEIGHT); n++;
	XtSetArg(core_args[n], XtNborderWidth, 0); n++;
	XtSetArg(core_args[n], XtNbackground, COLOR_BOARD); n++;
	XtSetValues(drawing, core_args, n);
	m = 0;
	XtSetArg(box_args[m], XtNhSpace, 0); m++;
	XtSetArg(box_args[m], XtNvSpace, 0); m++;
	XtSetValues(box, box_args, m);

	XtAddEventHandler(top, ClientMessage, TRUE, (void *) client_message_event, NULL);
	XtAddEventHandler(drawing, ExposureMask, FALSE, (void *) expose_event, NULL);
	XtAddEventHandler(drawing, KeyPressMask, FALSE, (void *) key_press_event, NULL);

	display = XtDisplay(drawing);

	font_small = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--20-140-100-100-p-105-iso8859-1");
	font_middle = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--25-180-100-100-p-138-iso8859-1");
	font_normal = XLoadQueryFont(display, "-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
	font_large = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");

	XtRealizeWidget(top);
	set_window_settings(display, XtWindow(top), WIDTH, HEIGHT);
	XtSetKeyboardFocus(top, drawing);

	wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
	(void) XSetWMProtocols(display, XtWindow(top), &wm_delete_window, 1);

	gc = XCreateGC(display, XtWindow(drawing), 0, NULL);

	XtAppMainLoop(context);
	return 0;
}
