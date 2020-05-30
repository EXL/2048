#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>

#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdlib>

// Найти .at()
// Найти uint
// Найти std::vector
// Найти i++, x++,y++,t++
// Инфа про virtual
// Инфа про static_cast
// Ссылки и указатели
// Const везде
// update или repaint?

struct Tile;
typedef std::vector<Tile *> TileList;
///typedef unsigned short uint8_t;

const int HORIZONTAL = 4, VERTICAL = 4;
const int BOARD_SIZE = HORIZONTAL * VERTICAL;
const int END_GAME_TARGET = 2048;
const int TILE_SIZE = 32;
const int TILE_MARGIN = 16;

inline double DegreesToRadians(int angleDegrees) { return ((angleDegrees) * M_PI / 180.0); }
inline double MathRandom() { return rand() / static_cast<double>(RAND_MAX); }

struct Tile {
	size_t value;

	Tile(size_t value) { this->value = value; }
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

class Board : public QWidget {
	Q_OBJECT

	Tile *board[BOARD_SIZE];
	bool win, lose;
	int score;

	void initialize(bool reset) {
		for (size_t i = 0; i < BOARD_SIZE; ++i)
			if (!reset) board[i] = new Tile(0);
			else board[i]->value = 0;
	}
	void freeVectorPointers(const TileList &list) {
		size_t size = list.size();
		for (size_t i = 0; i < size; ++i)
			delete list[i];
	}
	void deinitialize() {
		for (size_t i = 0; i < BOARD_SIZE; ++i)
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
	TileList availableSpace() {
		TileList spaces;
		for (size_t i = 0; i < BOARD_SIZE; ++i)
			if (board[i]->empty())
				spaces.push_back(board[i]);
		return spaces;
	}
	bool canMove() {
		if (!isFull())
			return true;
		for (size_t x = 0; x < HORIZONTAL; ++x)
			for (size_t y = 0; y < VERTICAL; ++y)
				if ((x < 3 && tileAt(x, y)->value == tileAt(x + 1, y)->value) ||
				    (y < 3 && tileAt(x, y)->value == tileAt(x, y + 1)->value))
					return true;
		return false;
	}
	Tile *tileAt(size_t x, size_t y) { return board[x + y * 4]; }
	bool isFull() { return (availableSpace().size() == 0); }
	TileList getLine(size_t index) {
		TileList line;
		for (size_t i = 0; i < HORIZONTAL; ++i)
			line.push_back(tileAt(i, index));
		return line;
	}
	void copyTileLine(TileList &newLine, TileList &oldLine) {
		size_t size = oldLine.size();
		for (size_t i = 0; i < size; ++i)
			newLine.push_back(new Tile(oldLine[i]->value));
	}
	TileList mergeLine(TileList oldLine) {
		TileList newLine;
		for (size_t i = 0; i < HORIZONTAL && !oldLine[i]->empty(); ++i) {
			size_t value = oldLine[i]->value;
			if (i < 3 && oldLine[i]->value == oldLine[i + 1]->value) {
				value *= 2;
				score += value;
				if (value == END_GAME_TARGET)
					win = true;
				i++;
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
	TileList moveLine(TileList oldLine) {
		TileList newLine;
		for (size_t i = 0; i < HORIZONTAL; ++i)
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
	void setLineAndFreeOldPointers(size_t index, TileList line) {
		for (size_t i = 0; i < HORIZONTAL; ++i) {
			delete board[index * 4 + i];
			board[index * 4 + i] = line[i];
		}
	}
	bool compare(TileList lineFirst, TileList lineSecond) {
		if (lineFirst.size() != lineSecond.size())
			return false;
		for (size_t i = 0; i < HORIZONTAL; ++i)								/// TODO: ??? lineFirst.size()
			if (lineFirst[i]->value != lineSecond[i]->value)
				return false;
		return true;
	}
	void rotate(int angle) {
		Tile *newBoard[BOARD_SIZE];
		size_t offsetX = 3, offsetY = 3;
		if (angle == 90)
			offsetY = 0;
		else if (angle == 270)
			offsetX = 0;
		const double rad = DegreesToRadians(angle);
		const size_t cos = static_cast<size_t>(::cos(rad)), sin = static_cast<size_t>(::sin(rad));
		for (size_t x = 0; x < HORIZONTAL; ++x)
			for (size_t y = 0; y < VERTICAL; ++y) {
				size_t newX = (x * cos) - (y * sin) + offsetX, newY = (x * sin) + (y * cos) + offsetY;
				newBoard[newX + newY * 4] = tileAt(x, y);
			}
		for (size_t i = 0; i < BOARD_SIZE; ++i)
			board[i] = newBoard[i];
	}
	void left() {
		bool needAddTile = false;
		for (size_t i = 0; i < HORIZONTAL; ++i) {
			TileList line = getLine(i), merged = mergeLine(moveLine(line));
			setLineAndFreeOldPointers(i, merged);
			if (!needAddTile && !compare(line, merged))
				needAddTile = true;
		}
		if (needAddTile)
			addTile();
	}
	void right() { rotate(180); left(); rotate(180); }
	void up() { rotate(270); left(); rotate(90); }
	void down() { rotate(90); left(); rotate(270); }
	int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, Tile *tile, int x, int y) {
		const size_t value = tile->value;
		const int xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		painter.setPen(QPen::NoPen);
		painter.setBrush(QBrush(QColor(QRgb(tile->background()))));
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
		if (value) {
			const int size = (value < 100) ? 16 : (value < 1000) ? 10 : 8;
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QPen(QColor(QRgb(tile->foreground()))));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			int w = QFontMetrics(painter.font()).width(strValue), h = (value < 100) ? size : size + 4;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (win || lose) {
			painter.setBrush(QBrush(0x888888, Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QPen(QColor(0x4E8BCA)));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			QString center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(0x776E65));
		painter.setFont(QFont("Sans", 10, QFont::Normal));
		QString strScore = QString("Score: %1").arg(score);
		int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	Board(QWidget *parent = 0) : QWidget(parent) {	resetGame(true); }
	virtual ~Board() { deinitialize(); }
protected:
	virtual void keyPressEvent(QKeyEvent *kEvent) {
		if (kEvent->key() == Key_Escape)
			resetGame(false);
		if (!canMove())
			lose = true;
		if (!win && !lose)
			switch (kEvent->key()) {
				case Key_Left: left(); break;
				case Key_Right: right(); break;
				case Key_Down: down(); break;
				case Key_Up: up(); break;
			}
		if (!win && !canMove())
			lose = true;
		update(); // or repaint?
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QBrush(QColor(0xBBADA0)));
		for (int y = 0; y < VERTICAL; y++)
			for (int x = 0; x < HORIZONTAL; x++)
				drawTile(painter, board[x + y * 4], x, y);
		drawFinal(painter);
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Board board;
	app.setMainWidget(&board);
	board.resize(240, 240);
	board.show();
	return app.exec();
}

#include "2048-Qt2.moc"
