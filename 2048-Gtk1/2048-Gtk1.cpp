#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

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
inline guint FadeColor(guint rgb) {	return rgb - 0x222222; }

struct Tile {
	u16 value;

	Tile(u16 value) { this->value = value; }
	bool empty() { return (value == 0); }
	guint foreground() { return (value < 16) ? 0x776E65 : 0xF9F6F2; }
	guint background() {
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
		tileColor.pixel = (win || lose) ? FadeColor(tile->background()) : tile->background();
		gdk_gc_set_foreground(gc, &tileColor);
		// HACK: Emulating gdk_draw_ronded_rectangle() method in 9 calls.
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
			tileColor.pixel = (win || lose) ? FadeColor(tile->foreground()) : tile->foreground();
			gdk_gc_set_foreground(gc, &tileColor);
			gdk_draw_text(widget->window, font, gc, xOffset + (TILE_SIZE - w) / 2,
				yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue,  static_cast<gint>(strlen(strValue)));
			g_free(strValue);
		}
	}
	void drawFinal(GtkWidget *widget, GdkGC *gc) {
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
				widget->allocation.height / 2, center, static_cast<gint>(strlen(center)));
		}
		GdkFont *font = gdk_font_load("-adobe-helvetica-medium-r-normal--20-140-100-100-p-100-iso8859-1");
		if (!font)
			font = widget->style->font;
		GdkColor textColor;
		textColor.pixel = (win || lose) ? FadeColor(0x776E65) : 0x776E65;
		gdk_gc_set_foreground(gc, &textColor);
		const gchar *strReset = "ESC to Restart!";
		gdk_draw_text(widget->window, font, gc, TILE_MARGIN,
			widget->allocation.height - gdk_string_height(font, strReset),
			strReset, static_cast<gint>(strlen(strReset)));
		gchar *strScore = g_strdup_printf("Score: %d", score);
		gdk_draw_text(widget->window, font, gc,
			widget->allocation.width - (gdk_string_width(font, strScore) - 3) - TILE_MARGIN,
			widget->allocation.height - gdk_string_height(font, strScore),
			strScore, static_cast<gint>(strlen(strScore)));
		g_free(strScore);
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
		GdkColor backgroundColor;
		backgroundColor.pixel = (win || lose) ? FadeColor(0xBBADA0) : 0xBBADA0;
		gdk_gc_set_foreground(gc, &backgroundColor);
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
	board->keyPressEvent(GTK_BIN(widget)->child, event->keyval);
	return TRUE;
}

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose /**event*/) {
	GdkGC *gc = gdk_gc_new(widget->window);
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
