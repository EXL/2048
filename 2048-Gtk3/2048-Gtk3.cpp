#include <gtk/gtk.h>

#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>

struct Tile;
class Board;

typedef unsigned short int u16;
typedef std::vector<Tile *> TileList;

static cairo_surface_t *surface = NULL;
static Board *board = nullptr;

const u16 HORIZONTAL = 4, VERTICAL = 4;
const u16 BOARD_SIZE = HORIZONTAL * VERTICAL;
const u16 END_GAME_TARGET = 2048;
const u16 TILE_SIZE = 64;
const u16 TILE_MARGIN = 16;

inline double DegreesToRadians(int angleDegrees) { return ((angleDegrees) * M_PI / 180.0); }
inline double MathRandom() { return rand() / static_cast<double>(RAND_MAX); }
inline double R(int rgb) { return ((rgb >> 16) & 0xFF) / 255.0; }
inline double G(int rgb) { return ((rgb >> 8) & 0xFF) / 255.0; }
inline double B(int rgb) { return ((rgb >> 0) & 0xFF) / 255.0; }

// Source: https://www.cairographics.org/samples/rounded_rectangle/
static void draw_rounded_rectangle(cairo_t *cairo, double x, double y, double width, double height, double radius) {
	double degrees = M_PI / 180.0;
	cairo_new_sub_path(cairo);
	cairo_arc(cairo, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
	cairo_arc(cairo, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
	cairo_arc(cairo, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
	cairo_arc(cairo, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cairo);
	cairo_fill(cairo);
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
			spaces[static_cast<size_t>((MathRandom() * size)) % size]->value = (MathRandom() < 0.9) ? 128 : 4;
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
	void drawTile(cairo_t *cairo, Tile *const tile, u16 x, u16 y) {
		const u16 value = tile->value;
		const u16 xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		cairo_set_source_rgb(cairo, R(tile->background()), G(tile->background()), B(tile->background()));
		draw_rounded_rectangle(cairo, xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6);
		cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		if (value) {
			const u16 size = (value < 100) ? 26 : (value < 1000) ? 22 : 16;
			gchar *strValue = g_strdup_printf("%d", value);
			cairo_set_source_rgb(cairo, R(tile->foreground()), G(tile->foreground()), B(tile->foreground()));
			cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
			cairo_set_font_size(cairo, size);
			cairo_text_extents_t extents;
			cairo_text_extents(cairo, strValue, &extents);
			const int w = static_cast<int>(extents.width) + 2, h = size;
			cairo_move_to(cairo, xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2);
			cairo_show_text(cairo, strValue);
			g_free(strValue);
		}
	}
	void drawFinal(GtkWidget *widget, cairo_t *cairo) {
		int width = gtk_widget_get_allocated_width(widget), height = gtk_widget_get_allocated_height(widget);
		u16 size = 26;
		if (win || lose) {
			cairo_set_source_rgba(cairo, R(0x888888), G(0x888888), B(0x888888), 0.5);
			cairo_paint(cairo);
			cairo_set_source_rgb(cairo, R(0x800000), G(0x800000), B(0x800000));
			cairo_set_font_size(cairo, size);
			const gchar *center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			cairo_text_extents_t extents;
			cairo_text_extents(cairo, center, &extents);
			cairo_move_to(cairo, width / 2 - static_cast<int>(extents.width) / 2, height / 2);
			cairo_show_text(cairo, center);
		}
		size = 18;
		cairo_select_font_face(cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
		cairo_set_source_rgb(cairo, R(0x776E65), G(0x776E65), B(0x776E65));
		cairo_set_font_size(cairo, size);
		gchar *strScore = g_strdup_printf("Score: %d", score);
		cairo_text_extents_t extents;
		cairo_text_extents(cairo, strScore, &extents);
		cairo_move_to(cairo, TILE_MARGIN, height - size);
		cairo_show_text(cairo, "ESC to Restart!");
		cairo_move_to(cairo, width - static_cast<int>(extents.width) - TILE_MARGIN, height - size);
		cairo_show_text(cairo, strScore);
		g_free(strScore);
	}
public:
	explicit Board() { resetGame(true); }
	~Board() { deinitialize(); paddingByte0 = paddingByte1 = false; }
	void keyPressEvent(GtkWidget *widget, guint keyval) {
		if (keyval == GDK_KEY_Escape)
			resetGame(false);
		if (!canMove())
			lose = true;
		if (!win && !lose)
			switch (keyval) {
				case GDK_KEY_Left: left(); break;
				case GDK_KEY_Right: right(); break;
				case GDK_KEY_Down: down(); break;
				case GDK_KEY_Up: up(); break;
			}
		if (!win && !canMove())
			lose = true;
		paintEvent(widget);
		gtk_widget_queue_draw(widget);
	}
	void paintEvent(GtkWidget *widget) {
		cairo_t *cairo = cairo_create(surface);
		cairo_set_source_rgb(cairo, R(0xBBADA0), G(0xBBADA0), B(0xBBADA0));
		cairo_paint(cairo);
		for (u16 y = 0; y < VERTICAL; ++y)
			for (u16 x = 0; x < HORIZONTAL; ++x)
				drawTile(cairo, board[x + y * 4], x, y);
		drawFinal(widget, cairo);
		cairo_destroy(cairo);
	}
};

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
	if (surface == NULL || !GTK_IS_BIN(widget))
		return FALSE;
	GtkWidget *child = gtk_bin_get_child(GTK_BIN(widget));
	//child
	board->keyPressEvent(child, event->keyval);
	return TRUE;
}

static void close_window(void) {
	if (surface)
		cairo_surface_destroy(surface);
}

static void activate(GtkApplication *application, gpointer user_data) {
	board = new Board();
	GtkWidget *window = gtk_application_window_new(application);
	GtkWidget *drawing_area = gtk_drawing_area_new();
	gtk_window_set_title(GTK_WINDOW(window), "2048-Gtk3");
	gtk_widget_set_size_request(GTK_WIDGET(window), 340, 400);
	//gtk_window_set_default_size(GTK_WINDOW(window), 340, 400);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);
	g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);
	g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), NULL);
	g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event_cb), NULL);
	g_signal_connect(window, "key-press-event", G_CALLBACK(key_press_event_cb), NULL);
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
	GtkApplication *application = gtk_application_new("ru.exlmoto.game2048", G_APPLICATION_FLAGS_NONE);
	srand(static_cast<u16>(time(nullptr)));
	g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(application), argc, argv);
	g_object_unref(application);
	delete board;
	board = nullptr;
	return status;
}
