#include <gtk/gtk.h>

#include <cstdio>

static cairo_surface_t *surface = NULL;

static void clear_surface(void) {
	cairo_t *cairo = cairo_create(surface);
	cairo_set_source_rgb(cairo, 1.0, 1.0, 1.0);
	cairo_paint(cairo);
	cairo_destroy(cairo);
}

static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
	if (surface)
		cairo_surface_destroy(surface);
	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
	                                            CAIRO_CONTENT_COLOR,
	                                            gtk_widget_get_allocated_width(widget),
	                                            gtk_widget_get_allocated_height(widget));
	clear_surface();
	return TRUE;
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cairo, gpointer data) {
	cairo_set_source_surface(cairo, surface, 0, 0);
	cairo_paint(cairo);
	return FALSE;
}

static void draw_brush(GtkWidget *widget, gdouble x, gdouble y) {
	cairo_t *cairo = cairo_create(surface);
	cairo_rectangle(cairo, x - 3, y - 3, 6, 6);
	cairo_fill(cairo);
	cairo_destroy(cairo);
}

static gboolean key_press_event_cb(GtkWidget *widget, GdkEventKey *event, gpointer data) {
	if (surface == NULL)
		return FALSE;
	fprintf(stderr, "%d\n", event->keyval);
	switch (event->keyval) {
		case GDK_KEY_Left: draw_brush(widget, 100.0, 10.0); fprintf(stderr, "left\n", event->keyval); break;
		case GDK_KEY_Right: clear_surface(); break;
		default: draw_brush(widget, 10.0, 10.0); break;
	}
	gtk_widget_queue_draw(widget);
	return TRUE;
}

static void close_window(void) {
	if (surface)
		cairo_surface_destroy(surface);
}

static void activate(GtkApplication *application, gpointer user_data) {
	GtkWidget *window = gtk_application_window_new(application);
	GtkWidget *drawing_area = gtk_drawing_area_new();
	gtk_window_set_title(GTK_WINDOW(window), "2048-Gtk3");
	gtk_widget_set_size_request(GTK_WIDGET(drawing_area), 340, 400);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);
	g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);
	g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), NULL);
	g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event_cb), NULL);
	g_signal_connect(window, "key-press-event", G_CALLBACK(key_press_event_cb), NULL);
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
	GtkApplication *application = gtk_application_new("ru.exlmoto.game2048", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(application), argc, argv);
	g_object_unref(application);
	return status;
}
