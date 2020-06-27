// https://ergodic.ugr.es/cphys_pedro/unix/athena8.html
// https://ergodic.ugr.es/cphys_pedro/unix/athena9.html

#include "2048.h"

#include <X11/Xaw/Box.h>
#include <X11/Core.h>
#include <X11/StringDefs.h>

#include <stdio.h>
#include <stdlib.h>

#define VALUE_MAX_SIZE 5 // "2048\0"

static const int WIDTH  = 340;
static const int HEIGHT = 400;
static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static GC gc = NULL;
static Atom wm_delete_window = 0;
static XtAppContext context = NULL;
static XFontStruct *font_small = NULL, *font_middle = NULL, *font_normal = NULL, *font_large = NULL;

static inline int offset_coords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
static inline unsigned fade_color(unsigned rgb) { return rgb - COLOR_FADE; }

static void quit() {
	XtDestroyApplicationContext(context);
	exit(0);
}

static void draw_tile(Display *display, Window window, int value, int x, int y, int win, int lose) {
	const unsigned bkg = e_background(value), frg = e_foreground(value);
	const int xOffset = offset_coords(x), yOffset = offset_coords(y);
	XSetForeground(display, gc, (win || lose) ? fade_color(bkg) : bkg);
	// HACK: Emulating XFillRoundedRectangle() method in 6 calls, similar to Xlib version.
	const int w = TILE_SIZE / 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
	XFillArc(display, window, gc, xOffset, yOffset, rect, rect, -64*180, -64*90);
	XFillArc(display, window, gc, xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90);
	XFillArc(display, window, gc, xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
	XFillArc(display, window, gc, xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
	XFillRectangle(display, window, gc, xOffset, yOffset + qw, TILE_SIZE + 1, rw);
	XFillRectangle(display, window, gc, xOffset + qw, yOffset, rw, TILE_SIZE + 1);
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
		XDrawString(display, window, gc,
			xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2,
			str_value, strlen(str_value));
	}
}

static void draw_final(Display *display, Window window, int win, int lose) {
	if (win || lose) {
		XSetForeground(display, gc, COLOR_FINAL);
		if (font_large)
			XSetFont(display, gc, font_large->fid);
		const char *center = (win) ? "You won!" : "Game Over!";
		const int w = (font_large) ? XTextWidth(font_large, center, strlen(center)) : 50;
		XDrawString(display, window, gc, WIDTH / 2 - (w - 3) / 2, HEIGHT / 2,
			center, strlen(center));
	}
	XSetForeground(display, gc, (win || lose) ? fade_color(COLOR_TEXT) : COLOR_TEXT);
	const char *strReset = "ESC to Restart!";
	if (font_normal)
		XSetFont(display, gc, font_normal->fid);
	const int h = 20;
	XDrawString(display, window, gc, TILE_MARGIN, HEIGHT - h,
		strReset, strlen(strReset));
	char strScore[16];
	snprintf(strScore, 16, "Score: %d", e_score);
	const int w = (font_normal) ? XTextWidth(font_normal, strScore, strlen(strScore)) : 50;
	XDrawString(display, window, gc, WIDTH - (w - 3) - TILE_MARGIN, HEIGHT - h,
		strScore, strlen(strScore));
}

static void expose_event(Widget widget, _X_UNUSED XtPointer client, _X_UNUSED XExposeEvent *event) {
	Display *display = XtDisplay(widget);
	Window window = XtWindow(widget);
	XSetForeground(display, gc, (e_win || e_lose) ? fade_color(COLOR_BOARD) : COLOR_BOARD);
	XFillRectangle(display, window, gc, 0, 0, WIDTH, HEIGHT);
	int y = 0, x;
	for (; y < LINE_SIZE; ++y)
		for (x = 0; x < LINE_SIZE; ++x)
			draw_tile(display, window, e_board[x + y * LINE_SIZE], x, y, e_win, e_lose);
	draw_final(display, window, e_win, e_lose);
}

static void key_press_event(Widget widget, _X_UNUSED XtPointer client, XKeyPressedEvent *event) {
	KeySym keysym = XtGetActionKeysym((XEvent *) event, NULL);
	if (keysym == XK_q)
		quit();
	else {
		e_key(keysym);
		event->type = Expose;
		XtDispatchEventToWidget(widget, (XEvent *) event);
	}
}

static void client_message_event(_X_UNUSED Widget widget, _X_UNUSED XtPointer client, XEvent *event) {
	if (event->type == ClientMessage && (Atom)event->xclient.data.l[0] == wm_delete_window)
		quit();
}

int main(int argc, char *argv[]) {
	e_init(XK_Escape, XK_Left, XK_Right, XK_Up, XK_Down);

	Arg box_args[2];
	Arg core_args[4];
	Widget top = XtAppInitialize(&context, "2048-Xaw", NULL, 0, &argc, argv, NULL, NULL, 0);
	Widget box = XtCreateManagedWidget("box", boxWidgetClass, top, NULL, 0);
	Widget drawing = XtCreateManagedWidget("core", coreWidgetClass, box, NULL, 0);

	int n = 0;
	XtSetArg(core_args[n], XtNwidth, WIDTH); n++;
	XtSetArg(core_args[n], XtNheight, HEIGHT); n++;
	XtSetArg(core_args[n], XtNborderWidth, 0); n++;
	XtSetArg(core_args[n], XtNbackground, COLOR_BOARD); n++;
	XtSetValues(drawing, core_args, n);
	int m = 0;
	XtSetArg(box_args[m], XtNhSpace, 0); m++;
	XtSetArg(box_args[m], XtNvSpace, 0); m++;
	XtSetValues(box, box_args, m);

	XtAddEventHandler(top, ClientMessage, TRUE, (void *) client_message_event, NULL);
	XtAddEventHandler(drawing, ExposureMask, FALSE, (void *) expose_event, NULL);
	XtAddEventHandler(drawing, KeyPressMask, FALSE, (void *) key_press_event, NULL);

	Display *display = XtDisplay(drawing);

	font_small = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--20-140-100-100-p-105-iso8859-1");
	font_middle = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--25-180-100-100-p-138-iso8859-1");
	font_normal = XLoadQueryFont(display, "-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
	font_large = XLoadQueryFont(display, "-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");

	XtRealizeWidget(top);

	XtSetKeyboardFocus(top, drawing);

	wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
	(void) XSetWMProtocols(display, XtWindow(top), &wm_delete_window, 1);

	gc = XCreateGC(display, XtWindow(drawing), 0, NULL);

	XtAppMainLoop(context);
	return 0;
}
