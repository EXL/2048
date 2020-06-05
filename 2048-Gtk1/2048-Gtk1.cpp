#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

//#include <cairo.h>

#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <cstring>

struct Tile;
class Board;

typedef unsigned short int u16;
typedef std::vector<Tile *> TileList;

static Board *board = NULL;

const u16 HORIZONTAL = 4, VERTICAL = 4;
const u16 BOARD_SIZE = HORIZONTAL * VERTICAL;
const u16 END_GAME_TARGET = 2048;
const u16 TILE_SIZE = 64;
const u16 TILE_MARGIN = 16;

inline double DegreesToRadians(int angleDegrees) { return ((angleDegrees) * M_PI / 180.0); }
inline double MathRandom() { return rand() / static_cast<double>(RAND_MAX); }
inline gushort R(int rgb) { return (rgb >> 16) & 0xFF; }
inline gushort G(int rgb) { return (rgb >> 8) & 0xFF; }
inline gushort B(int rgb) { return (rgb >> 0) & 0xFF; }

// Source: https://www.cairographics.org/samples/rounded_rectangle/
//static void draw_rounded_rectangle(cairo_t *cairo, double x, double y, double width, double height, double radius) {
//	const double degrees = M_PI / 180.0;
//	cairo_new_sub_path(cairo);
//	cairo_arc(cairo, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
//	cairo_arc(cairo, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
//	cairo_arc(cairo, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
//	cairo_arc(cairo, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
//	cairo_close_path(cairo);
//	cairo_fill(cairo);
//}

static void draw_rounded_rectangle(GtkWidget *widget, GdkGC *gc, gushort x, gushort y,
								   gushort width, gushort height, gushort radius) {
	const int degrees = int(M_PI / 180);
	gdk_draw_arc(widget->window, gc, TRUE, x + width - radius, y + radius, radius, radius, 0, 360 * degrees);
	gdk_draw_arc(widget->window, gc, TRUE, x + width - radius, y + height - radius, radius, radius, 0 * degrees, 90 * degrees);
	gdk_draw_arc(widget->window, gc, TRUE, x + radius, y + height - radius, radius, radius, 90 * degrees, 180 * degrees);
	gdk_draw_arc(widget->window, gc, TRUE, x + radius, y + radius, radius, radius, 180 * degrees, 270 * degrees);

//	cairo_new_sub_path(cairo);
//	cairo_arc(cairo, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
//	cairo_arc(cairo, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
//	cairo_arc(cairo, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
//	cairo_arc(cairo, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
//	cairo_close_path(cairo);
//	cairo_fill(cairo);
}

struct Tile {
	u16 value;

	Tile(u16 value) { this->value = value; }
	bool empty() { return (value == 0); }
	int foreground() { return (value < 16) ? 0x776E65 : 0xF9F6F2; }
	int background() {
		switch (value) {
			case    2: return 0xEEE4DA;
			case    4: return 0xEDE0C8;
			case    8: return 0xF2B179;
			case   16: return 0xF59563;
			case   32: return 0xF67C5F;
			case   64: return 0xF65E3B;
			case  128: return 0xEDCF72;
			case  256: return 0xEDCC61;
			case  512: return 0xEDC850;
			case 1024: return 0xEDC53F;
			case 2048: return 0xEDC22E;
		}
		return 0xCDC1B4;
	}
};

class Board {
	Tile *board[BOARD_SIZE];
	bool win, lose, paddingByte0, paddingByte1;
	int score;

	void initialize(bool reset) {
		for (u16 i = 0; i < BOARD_SIZE; ++i)
			if (!reset) board[i] = new Tile(0);
			else board[i]->value = 0;
	}
	void freeVectorPointers(const TileList &list) {
		const size_t size = list.size();
		for (size_t i = 0; i < size; ++i)
			delete list[i];
	}
	void deinitialize() {
		for (u16 i = 0; i < BOARD_SIZE; ++i)
			delete board[i];
	}
	void resetGame(bool init) {
		score = 0;
		win = lose = false;
		initialize(!init);
		addTile();
		addTile();
	}
	void addTile() {
		const TileList spaces = availableSpace();
		const size_t size = spaces.size();
		if (!spaces.empty())
			spaces[static_cast<size_t>((MathRandom() * size)) % size]->value = (MathRandom() < 0.9) ? 2 : 4;
	}
	const TileList availableSpace() {
		TileList spaces;
		for (u16 i = 0; i < BOARD_SIZE; ++i)
			if (board[i]->empty())
				spaces.push_back(board[i]);
		return spaces;
	}
	bool canMove() {
		if (!availableSpace().empty())
			return true;
		for (u16 x = 0; x < HORIZONTAL; ++x)
			for (u16 y = 0; y < VERTICAL; ++y)
				if ((x < 3 && tileAt(x, y)->value == tileAt(x + 1, y)->value) ||
				    (y < 3 && tileAt(x, y)->value == tileAt(x, y + 1)->value))
					return true;
		return false;
	}
	Tile * tileAt(u16 x, u16 y) { return board[x + y * 4]; }
	TileList getLine(u16 index) {
		TileList line;
		for (u16 i = 0; i < HORIZONTAL; ++i)
			line.push_back(tileAt(i, index));
		return line;
	}
	void copyTileLine(TileList &newLine, const TileList &oldLine) {
		const size_t size = oldLine.size();
		for (size_t i = 0; i < size; ++i)
			newLine.push_back(new Tile(oldLine[i]->value));
	}
	TileList mergeLine(const TileList &oldLine) {
		TileList newLine;
		for (u16 i = 0; i < HORIZONTAL && !oldLine[i]->empty(); ++i) {
			u16 value = oldLine[i]->value;
			if (i < 3 && oldLine[i]->value == oldLine[i + 1]->value) {
				value *= 2;
				score += value;
				if (value == END_GAME_TARGET)
					win = true;
				++i;
			}
			newLine.push_back(new Tile(value));
		}
		if (newLine.empty()) {
			copyTileLine(newLine, oldLine);
			freeVectorPointers(oldLine);
			return newLine;
		} else {
			ensureLineSize(newLine, HORIZONTAL);
			freeVectorPointers(oldLine);
			return newLine;
		}
	}
	void ensureLineSize(TileList &line, size_t size) {
		while (line.size() != size)
			line.push_back(new Tile(0));
	}
	TileList moveLine(const TileList &oldLine) {
		TileList newLine;
		for (u16 i = 0; i < HORIZONTAL; ++i)
			if (!oldLine[i]->empty())
				newLine.push_back(new Tile(oldLine[i]->value));
		if (newLine.empty()) {
			copyTileLine(newLine, oldLine);
			return newLine;
		} else {
			ensureLineSize(newLine, HORIZONTAL);
			return newLine;
		}
	}
	void setLine(u16 index, const TileList &line) {
		for (u16 i = 0; i < HORIZONTAL; ++i)
			board[index * 4 + i]->value = line[i]->value;
	}
	bool compare(const TileList &lineFirst, const TileList &lineSecond) {
		if (lineFirst.size() != lineSecond.size())
			return false;
		for (u16 i = 0; i < HORIZONTAL; ++i)
			if (lineFirst[i]->value != lineSecond[i]->value)
				return false;
		return true;
	}
	void rotate(int angle) {
		Tile *newBoard[BOARD_SIZE];
		u16 offsetX = 3, offsetY = 3;
		if (angle == 90)
			offsetY = 0;
		else if (angle == 270)
			offsetX = 0;
		const double rad = DegreesToRadians(angle);
		const short cos = static_cast<short>(::cos(rad)), sin = static_cast<short>(::sin(rad));
		for (u16 x = 0; x < HORIZONTAL; ++x)
			for (u16 y = 0; y < VERTICAL; ++y) {
				short newX = (x * cos) - (y * sin) + offsetX, newY = (x * sin) + (y * cos) + offsetY;
				newBoard[newX + newY * 4] = tileAt(x, y);
			}
		for (u16 i = 0; i < BOARD_SIZE; ++i)
			board[i] = newBoard[i];
	}
	void left() {
		bool needAddTile = false;
		for (u16 i = 0; i < HORIZONTAL; ++i) {
			const TileList line = getLine(i), merged = mergeLine(moveLine(line));
			bool result = compare(line, merged);
			setLine(i, merged);
			if (!needAddTile && !result)
				needAddTile = true;
			freeVectorPointers(merged);
		}
		if (needAddTile)
			addTile();
	}
	void right() { rotate(180); left(); rotate(180); }
	void up() { rotate(270); left(); rotate(90); }
	void down() { rotate(90); left(); rotate(270); }
	u16 offsetCoords(u16 coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
	void drawTile(GtkWidget *widget, GdkGC *gc, Tile *const tile, u16 x, u16 y) {
		const u16 value = tile->value;
		const u16 xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		GdkColor tileColor;
		tileColor.pixel = (gulong) tile->background();
		gdk_gc_set_foreground(gc, &tileColor);
		//gdk_draw_rectangle(widget->window, gc, 1, xOffset, yOffset, TILE_SIZE, TILE_SIZE);
		//draw_rounded_rectangle(widget, gc, xOffset, yOffset, TILE_SIZE, TILE_SIZE, 1000);

		//int radius = 24;
		//gdk_draw_arc(widget->window, gc, TRUE, xOffset + TILE_SIZE - radius,
	//				 yOffset + radius, radius, radius, 0, 360 * 9);

//		gdk_draw_arc(widget->window, gc, TRUE,
//					   0, 0,
//					   100, 50,
//					   0, 180*64);

		// HACK: Emulating drawRoundRect() method in 9 calls.
		const u16 w = TILE_SIZE / 2, dw = w * 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
		gdk_draw_arc(widget->window, gc, TRUE, xOffset, yOffset, rect, rect, -64*180, -64*90);
		gdk_draw_arc(widget->window, gc, TRUE, xOffset + w + rad, yOffset, rect, rect, 64*90, -64*90);
		gdk_draw_arc(widget->window, gc, TRUE, xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
		gdk_draw_arc(widget->window, gc, TRUE, xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
		gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + qw, yOffset + qw, TILE_SIZE - rad + 1, TILE_SIZE - rad + 1);
		gdk_draw_rectangle(widget->window, gc, TRUE, xOffset, yOffset + qw, qw, rw);
		gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + dw - qw + 1, yOffset + qw, qw, rw);
		gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + qw, yOffset, rw, qw);
		gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + qw, yOffset + dw - qw + 1, rw, qw);


		//gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + rad, yOffset + rad, TILE_SIZE - rad * 2, TILE_SIZE - rad * 2);
		//gdk_draw_rectangle(widget->window, gc, TRUE, xOffset, yOffset + rad, rad, rw);
		//gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + dw - rad, yOffset + rad, rad, rw);
		//gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + rad, yOffset, rw, rad);
		//gdk_draw_rectangle(widget->window, gc, TRUE, xOffset + rad, yOffset + dw - rad, rw, rad);

		//const u16 w = TILE_SIZE / 2, dw = w * 2, rad = w / 4, rw = rad * 6, rect = w - rad;
//		gdk_draw_arc(widget->window, gc, TRUE, xOffset, yOffset, rect, rect, -180*64, -64*90);
//		gdk_draw_arc(widget->window, gc, TRUE, xOffset + w + rad, yOffset, rect, rect, 90, -64*90);
//		gdk_draw_arc(widget->window, gc, TRUE, xOffset, yOffset + w + rad, rect, rect, -64*90, -64*90);
//		gdk_draw_arc(widget->window, gc, TRUE, xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -64*90);
//		painter.drawRect(xOffset + rad, yOffset + rad, TILE_SIZE - rad * 2, TILE_SIZE - rad * 2);
//		painter.drawRect(xOffset, yOffset + rad, rad, rw);
//		painter.drawRect(xOffset + dw - rad, yOffset + rad, rad, rw);
//		painter.drawRect(xOffset + rad, yOffset, rw, rad);
//		painter.drawRect(xOffset + rad, yOffset + dw - rad, rw, rad);


		if (value) {
			const u16 size = (value < 100) ? 26 : (value < 1000) ? 22 : 16;
			gchar *strFont = g_strdup_printf("-adobe-helvetica-bold-r-normal--*-%d0-*-*-*-*-*-*", size);
			GdkFont *font = gdk_font_load("-adobe-helvetica-bold-r-normal--*-180-*-*-*-*-*-*");
			g_free(strFont);
			gchar *strValue = g_strdup_printf("%d", value);
			int w = 10, h = 14;
			GdkColor tileColor;
			tileColor.pixel = (gulong) tile->foreground();
			gdk_gc_set_foreground(gc, &tileColor);
			gdk_draw_text(widget->window, font, gc,
						  xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue, strlen(strValue));
			g_free(strValue);

		}

		// cairo_set_source_rgb(cairo, R(tile->background()), G(tile->background()), B(tile->background()));
		// draw_rounded_rectangle(cairo, xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6);


//		cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
//		if (value) {
//			const u16 size = (value < 100) ? 26 : (value < 1000) ? 22 : 16;
//			gchar *strValue = g_strdup_printf("%d", value);
//			cairo_set_source_rgb(cairo, R(tile->foreground()), G(tile->foreground()), B(tile->foreground()));
//			cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
//			cairo_set_font_size(cairo, size);
//			cairo_text_extents_t extents;
//			cairo_text_extents(cairo, strValue, &extents);
//			const int w = static_cast<int>(extents.width) + 2, h = size;
//			cairo_move_to(cairo, xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2);
//			cairo_show_text(cairo, strValue);
//			g_free(strValue);
//		}
	}
	void drawFinal(GtkWidget *widget, GdkGC *gc) {
		// GtkAllocation allocation;
		// gtk_widget_get_allocation(widget, &allocation);
//		int width = widget->allocation.width, height = widget->allocation.height;
//		u16 size = 26;
//		if (win || lose) {
//			cairo_set_source_rgba(cairo, R(0x888888), G(0x888888), B(0x888888), 0.5);
//			cairo_paint(cairo);
//			cairo_set_source_rgb(cairo, R(0x800000), G(0x800000), B(0x800000));
//			cairo_set_font_size(cairo, size);
//			const gchar *center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
//			cairo_text_extents_t extents;
//			cairo_text_extents(cairo, center, &extents);
//			cairo_move_to(cairo, width / 2 - static_cast<int>(extents.width) / 2, height / 2);
//			cairo_show_text(cairo, center);
//		}
//		size = 18;
//		cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
//		cairo_set_source_rgb(cairo, R(0x776E65), G(0x776E65), B(0x776E65));
//		cairo_set_font_size(cairo, size);
//		gchar *strScore = g_strdup_printf("Score: %d", score);
//		cairo_text_extents_t extents;
//		cairo_text_extents(cairo, strScore, &extents);
//		cairo_move_to(cairo, TILE_MARGIN, height - size);
//		cairo_show_text(cairo, "ESC to Restart!");
//		cairo_move_to(cairo, width - static_cast<int>(extents.width) - TILE_MARGIN, height - size);
//		cairo_show_text(cairo, strScore);
//		g_free(strScore);
	}
public:
	explicit Board() { resetGame(true); }
	~Board() { deinitialize(); paddingByte0 = paddingByte1 = false; }
	void keyPressEvent(GtkWidget *widget, guint keyval) {
		if (keyval == GDK_Escape)
			resetGame(false);
		if (!canMove())
			lose = true;
		if (!win && !lose)
			switch (keyval) {
				case GDK_Left: left(); break;
				case GDK_Right: right(); break;
				case GDK_Down: down(); break;
				case GDK_Up: up(); break;
			}
		if (!win && !canMove())
			lose = true;
		gtk_widget_queue_draw(widget);
	}
	void paintEvent(GtkWidget *widget, GdkGC *gc) {
		GdkColor background;
		background.pixel = 0xBBADA0;
		gdk_gc_set_foreground(gc, &background);
		gdk_draw_rectangle(widget->window, gc, 1, 0, 0, widget->allocation.width, widget->allocation.height);
		for (u16 y = 0; y < VERTICAL; ++y)
			for (u16 x = 0; x < HORIZONTAL; ++x)
				drawTile(widget, gc, board[x + y * 4], x, y);
		drawFinal(widget, gc);
	}
};

static gboolean on_key_press_event(GtkWidget *widget, GdkEventKey *event, gpointer /*data*/) {
	if (!GTK_IS_BIN(widget))
		return FALSE;
	//gtk_bin_get_type()
	board->keyPressEvent(GTK_BIN(widget)->child, event->keyval);
	return TRUE;
}

static GdkColor* color(GtkWidget *widget, gushort red, gushort green, gushort blue) {
	GdkColor *color = (GdkColor *) malloc(sizeof(GdkColor));
	color->red = red * (65535 / 255);
	color->green = green * (65535 / 255);
	color->blue = blue * (65535 / 255);
	color->pixel = (gulong)(red * 65536 + green * 256 + blue);
	//gdk_color_alloc(gtk_widget_get_colormap(widget), color);
	return color;
}

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose /**event*/) {
	GdkGC *gc = gdk_gc_new(widget->window);
	//cairo_surface_t *surface = cairo_cr
	//cairo_t *cairo = cairo_create(surface);
	//gdk_cair
	//board->paintEvent(widget, cairo);
	//cairo_destroy(cairo);

//	int width, height;

//	gdk_window_get_size(widget->window, &width, &height);

//	GdkColor *y = color(widget, 0xFF, 0xFF, 0x00);

//	gdk_gc_set_foreground(gc, y);

//	gdk_draw_rectangle(widget->window, gc, 1, 0, 0, width, height);
//	free(y);

//	GdkColor *r = color(widget, 0xFF, 0x00, 0x00);

//	gdk_gc_set_foreground(gc, r);

//	//GdkFont font;
//	gdk_draw_text(widget->window, widget->style->font, gc, 20, 20, "test", 4);
//	free(r);

//	//gdk_color_free(r);

	board->paintEvent(widget, gc);

	gdk_gc_destroy(gc);

	return FALSE;
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	srand(static_cast<u16>(time(NULL)));
	board = new Board();
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_usize(GTK_WIDGET(window), 340, 400);
	// gtk_widget_set_size_request(GTK_WIDGET(window), 340, 400);
	//gtk_widget_set
	GtkWidget *drawing = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), drawing);
	gtk_signal_connect(GTK_OBJECT(drawing), "expose-event", GTK_SIGNAL_FUNC(on_expose_event), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "key-press-event", GTK_SIGNAL_FUNC(on_key_press_event), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	delete board;
	return 0;
}
