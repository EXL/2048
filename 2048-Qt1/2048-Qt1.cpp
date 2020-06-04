#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qkeycode.h>

#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>

struct Tile;

typedef unsigned short int u16;
typedef std::vector<Tile *> TileList;

const u16 HORIZONTAL = 4, VERTICAL = 4;
const u16 BOARD_SIZE = HORIZONTAL * VERTICAL;
const u16 END_GAME_TARGET = 2048;
const u16 TILE_SIZE = 48;
const u16 TILE_MARGIN = 5;

inline double DegreesToRadians(int angleDegrees) { return ((angleDegrees) * M_PI / 180.0); }
inline double MathRandom() { return rand() / static_cast<double>(RAND_MAX); }

struct Tile {
	u16 value;

	Tile(u16 value) { this->value = value; }
	bool empty() { return (value == 0); }
	const char *foreground() { return (value < 16) ? "#776E65" : "#F9F6F2"; }
	const char *background() {
		switch (value) {
			case    2: return "#EEE4DA";
			case    4: return "#EDE0C8";
			case    8: return "#F2B179";
			case   16: return "#F59563";
			case   32: return "#F67C5F";
			case   64: return "#F65E3B";
			case  128: return "#EDCF72";
			case  256: return "#EDCC61";
			case  512: return "#EDC850";
			case 1024: return "#EDC53F";
			case 2048: return "#EDC22E";
		}
		return "#CDC1B4";
	}
};

class Board : public QWidget {
	Q_OBJECT

	Tile *board[BOARD_SIZE];
	bool win, lose;
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
	u16 offsetCoords(u16 coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, Tile *const tile, u16 x, u16 y) {
		const u16 value = tile->value;
		const int xOffset = offsetCoords(x) + width() / 32, yOffset = offsetCoords(y);
		painter.setPen(NoPen);
		painter.setBrush(QColor(tile->background()));
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
		if (value) {
			const u16 size = (value < 100) ? 16 : (value < 1000) ? 10 : 8;
			const QString strValue = QString().setNum(value);
			painter.setPen(QColor(tile->foreground()));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).width(strValue), h = (value < 100) ? size : size + 4;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (win || lose) {
			painter.setBrush(QBrush("#888888", Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QColor("#800000"));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor("#776E65"));
		painter.setFont(QFont("Sans", 10, QFont::Normal));
		QString strScore = QString().sprintf("Score: %d", score);
		const int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	Board(QWidget *parent = 0) : QWidget(parent) { resetGame(true); }
	virtual ~Board() { deinitialize(); }
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		if (keyEvent->key() == Key_Escape)
			resetGame(false);
		if (!canMove())
			lose = true;
		if (!win && !lose)
			switch (keyEvent->key()) {
				case Key_Left: left(); break;
				case Key_Right: right(); break;
				case Key_Down: down(); break;
				case Key_Up: up(); break;
			}
		if (!win && !canMove())
			lose = true;
		repaint();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor("#BBADA0"));
		for (u16 y = 0; y < VERTICAL; ++y)
			for (u16 x = 0; x < HORIZONTAL; ++x)
				drawTile(painter, board[x + y * 4], x, y);
		drawFinal(painter);
	}
};

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	srand(static_cast<u16>(time(NULL)));
	Board boardWidget;
	application.setMainWidget(&boardWidget);
	boardWidget.resize(240, 260);
	boardWidget.show();
	return application.exec();
}

#include "2048-Qt1.moc"
