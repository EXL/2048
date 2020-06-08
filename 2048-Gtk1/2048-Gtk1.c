#include "2048.h"

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <string.h>

static int* board = NULL;

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static inline int offset_coords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
static inline guint fade_color(guint rgb) { return rgb - 0x222222; }

static void draw_tile(GtkWidget *widget, GdkGC *gc, int value, int x, int y, int win, int lose) {
	const unsigned bkg = e_background(value), frg = e_foreground(value);
	const int xOffset = offset_coords(x), yOffset = offset_coords(y);
	GdkColor tileColor;
	tileColor.pixel = (win || lose) ? fade_color(bkg) : bkg;
	gdk_gc_set_foreground(gc, &tileColor);
	// HACK: Emulating gdk_draw_ronded_rectangle() method in 9 calls.
	const int w = TILE_SIZE / 2, dw = w * 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
	gdk_draw_arc(widget->window, gc, TRUE, xOffset, yOffset, rect, rect, -64*180, -64*90);
	gdk_draw_arc(widget->window, gc, TRUE, xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90);
	gdk_draw_arc(widget->window, gc, TRUE, xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
	gdk_draw_arc(widget->window, gc, TRUE, xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
	gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + qw, yOffset + qw, TILE_SIZE - rad + 1, TILE_SIZE - rad + 1);
	gdk_draw_rectangle(widget->window, gc, TRUE, xOffset, yOffset + qw, qw, rw);
	gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + dw - qw + 1, yOffset + qw, qw, rw);
	gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + qw, yOffset, rw, qw);
	gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + qw, yOffset + dw - qw + 1, rw, qw);
	if (value) {
		GdkFont *font = (value < 100) ?
			gdk_font_load("-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1") :
			(value < 1000) ?
				gdk_font_load("-adobe-helvetica-bold-r-normal--25-180-100-100-p-138-iso8859-1") :
				gdk_font_load("-adobe-helvetica-bold-r-normal--20-140-100-100-p-105-iso8859-1");
		if (!font)
			font = widget->style->font;
		gchar *strValue = g_strdup_printf("%d", value);
		int w = gdk_string_width(font, strValue) - 3, h = gdk_string_height(font, strValue) + 2;
		GdkColor tileColor;
		tileColor.pixel = (win || lose) ? fade_color(frg) : frg;
		gdk_gc_set_foreground(gc, &tileColor);
		gdk_draw_text(widget->window, font, gc, xOffset + (TILE_SIZE - w) / 2,
			yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue, strlen(strValue));
		g_free(strValue);
	}
}

static void draw_final(GtkWidget *widget, GdkGC *gc, int win, int lose) {
	if (win || lose) {
		GdkColor foregroundColor;
		foregroundColor.pixel = 0x800000;
		gdk_gc_set_foreground(gc, &foregroundColor);
		GdkFont *font = gdk_font_load("-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1");
		if (!font)
			font = widget->style->font;
		const gchar *center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
		gdk_draw_text(widget->window, font, gc,
			widget->allocation.width / 2 - (gdk_string_width(font, center) - 3) / 2,
			widget->allocation.height / 2, center, strlen(center));
	}
	GdkFont *font = gdk_font_load("-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
	if (!font)
		font = widget->style->font;
	GdkColor textColor;
	textColor.pixel = (win || lose) ? fade_color(0x776E65) : 0x776E65;
	gdk_gc_set_foreground(gc, &textColor);
	const gchar *strReset = "ESC to Restart!";
	gdk_draw_text(widget->window, font, gc, TILE_MARGIN,
		widget->allocation.height - gdk_string_height(font, strReset),
		strReset, strlen(strReset));
	gchar *strScore = g_strdup_printf("Score: %d", e_score());
	gdk_draw_text(widget->window, font, gc,
		widget->allocation.width - (gdk_string_width(font, strScore) - 3) - TILE_MARGIN,
		widget->allocation.height - gdk_string_height(font, strScore),
		strScore, strlen(strScore));
	g_free(strScore);
}

static gboolean on_expose_event(GtkWidget *widget, G_GNUC_UNUSED GdkEventExpose *event) {
	GdkGC *gc = gdk_gc_new(widget->window);
	const int win = e_win(), lose = e_lose();
	GdkColor background_color;
	background_color.pixel = (win || lose) ? fade_color(0xBBADA0) : 0xBBADA0;
	gdk_gc_set_foreground(gc, &background_color);
	gdk_draw_rectangle(widget->window, gc, 1, 0, 0, widget->allocation.width, widget->allocation.height);
	int y = 0;
	for (; y < VERTICAL; ++y) {
		int x = 0;
		for (; x < HORIZONTAL; ++x)
			draw_tile(widget, gc, board[x + y * 4], x, y, win, lose);
	}
	draw_final(widget, gc, win, lose);
	gdk_gc_destroy(gc);
	return FALSE;
}

static gboolean on_key_press_event(GtkWidget *widget, GdkEventKey *event, G_GNUC_UNUSED gpointer data) {
	if (!GTK_IS_BIN(widget))
		return FALSE;
	e_key_event(event->keyval);
	gtk_widget_queue_draw(GTK_BIN(widget)->child);
	return TRUE;
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	board = e_init_board(GDK_Escape, GDK_Left, GDK_Right, GDK_Up, GDK_Down);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_usize(GTK_WIDGET(window), 340, 400);
	GtkWidget *drawing = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), drawing);
	gtk_signal_connect(GTK_OBJECT(drawing), "expose-event", GTK_SIGNAL_FUNC(on_expose_event), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "key-press-event", GTK_SIGNAL_FUNC(on_key_press_event), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
