#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QPainter>

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
const u16 TILE_SIZE = 64;
const u16 TILE_MARGIN = 16;

inline double DegreesToRadians(int angleDegrees) { return ((angleDegrees) * M_PI / 180.0); }
inline double MathRandom() { return rand() / static_cast<double>(RAND_MAX); }

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

class Board : public QWidget {
	Q_OBJECT

	Tile *board[BOARD_SIZE];
	Tile *availableSpace[BOARD_SIZE];
	Tile *lineBackReg[HORIZONTAL];
	Tile *lineFrontReg[HORIZONTAL];
// u16 availableSpaceSize;
//	Tile *boardLine[HORIZONTAL];
//	Tile *middleLine[HORIZONTAL];
//	Tile *finalLine[HORIZONTAL];
	bool win, lose;
	int score;

	void initialize(bool reset) {
		for (u16 i = 0; i < BOARD_SIZE; ++i) {
			availableSpace[i] = NULL;
			if (!reset) board[i] = new Tile(0);
			else board[i]->value = 0;
		}
		resetStates(reset);
	}
	void resetStates(bool reset) {
		for (u16 i = 0; i < HORIZONTAL; ++i)
			if (!reset) {
				lineBackReg[i] = new Tile(0);
				lineFrontReg[i] = new Tile(0);
//				boardLine[i] = new Tile(0);
//				middleLine[i] = new Tile(0);
//				finalLine[i] = new Tile(0);
			} else
				lineBackReg[i]->value = lineFrontReg[i]->value = 0;
	}
	void resetLineBackReg() {
		for (u16 i = 0; i < HORIZONTAL; ++i)
			lineBackReg[i]->value = 0;
	}
//	void freeVectorPointers(Tile **list) {
//		//const size_t size = list.size();
//		for (u16 i = 0; i < HORIZONTAL; ++i)
//			if (list[i])
//				delete list[i];
//	}
	void deinitialize() {
		for (u16 i = 0; i < BOARD_SIZE; ++i)
			delete board[i];
		for (u16 i = 0; i < HORIZONTAL; ++i) {
			delete lineBackReg[i];
			delete lineFrontReg[i];
		}
	}
	void resetGame(bool init) {
		score = 0;
		win = lose = false;
		initialize(!init);
		addTile();
		addTile();
	}
	void addTile() {
		const u16 size = updateAvailableSpace();
		// const TileList spaces = availableSpace();
		// const size_t size = spaces.size();
		if (size)
			availableSpace[static_cast<size_t>((MathRandom() * size)) % size]->value = (MathRandom() < 0.9) ? 2 : 4;
	}
	u16 updateAvailableSpace() {
		u16 j = 0;
		for (u16 i = 0; i < BOARD_SIZE; ++i)
			if (board[i]->empty())
				availableSpace[j++] = board[i];
		return j;
		// availableSpaceSize = j;
	}
	bool canMove() {
		if (updateAvailableSpace())
			return true;
		for (u16 x = 0; x < HORIZONTAL; ++x)
			for (u16 y = 0; y < VERTICAL; ++y)
				if ((x < 3 && tileAt(x, y)->value == tileAt(x + 1, y)->value) ||
				    (y < 3 && tileAt(x, y)->value == tileAt(x, y + 1)->value))
					return true;
		return false;
	}
	Tile *tileAt(u16 x, u16 y) { return board[x + y * 4]; }
	Tile **getLine(u16 index, Tile **line) {
		//TileList line;
		for (u16 i = 0; i < HORIZONTAL; ++i)
			line[i]->value = tileAt(i, index)->value;
			// line.push_back(tileAt(i, index));
		return line;
		// return boardLine;
	}
	void copyTileLine(Tile **newLine, Tile **oldLine) {
		// const size_t size = oldLine.size();
		for (u16 i = 0; i < HORIZONTAL; ++i)
			newLine[i]->value = oldLine[i]->value;
			//newLine.push_back(new Tile(oldLine[i]->value));
	}
	Tile **mergeLine(Tile **oldLine) {
		/// TileList newLine;
		resetLineBackReg();
		u16 j = 0;
		for (u16 i = 0; i < HORIZONTAL && !oldLine[i]->empty(); ++i) {
			u16 value = oldLine[i]->value;
			if (i < 3 && oldLine[i]->value == oldLine[i + 1]->value) {
				value *= 2;
				score += value;
				if (value == END_GAME_TARGET)
					win = true;
				++i;
			}
			lineBackReg[j++]->value = value;
			// newLine.push_back(new Tile(value));
		}
		if (!j) {
			copyTileLine(lineBackReg, oldLine);
			//freeVectorPointers(oldLine);
			//return finalLine;
		} else {
			//ensureLineSize(finalLine, HORIZONTAL);
			//freeVectorPointers(oldLine);
			//return finalLine;
		}
		return lineBackReg;
	}
//	void ensureLineSize(Tile **line, size_t size) {
//		for (u16 i = 0; i < size; ++i)
//			if (line[i])
//				line[i] = new Tile(0);
//		//while (line.size() != size)
//		//	line.push_back(new Tile(0));
//	}
	Tile **moveLine(Tile **oldLine) {
		// TileList newLine;
		u16 j = 0;
		for (u16 i = 0; i < HORIZONTAL; ++i)
			if (!oldLine[i]->empty())
				lineFrontReg[j++]->value = oldLine[i]->value;
				//newLine.push_back(new Tile(oldLine[i]->value));
		if (!j) {
			copyTileLine(lineFrontReg, oldLine);
			// return middleLine;
		} else {
			// ensureLineSize(middleLine, HORIZONTAL);
			// return middleLine;
		}
		return lineFrontReg;
	}
	void setLine(u16 index, Tile **line) {
		for (u16 i = 0; i < HORIZONTAL; ++i)
			board[index * 4 + i]->value = line[i]->value;
	}
	bool compare(Tile **lineFirst, Tile**lineSecond) {
//		if (lineFirst.size() != lineSecond.size())
//			return false;
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
			resetStates(true);
			Tile **line = getLine(i, lineBackReg), **merged = mergeLine(moveLine(line));
			//getLine(i, lineBackReg);
			//moveLine(lineBackReg);
			//mergeLine(lineFrontReg);
			line = getLine(i, lineFrontReg);
			//Tile **line = getLine(i), **merged = mergeLine(moveLine(line));
			bool result = compare(line, merged);
			setLine(i, merged);
			if (!needAddTile && !result)
				needAddTile = true;
			//freeVectorPointers(merged);
		}
		if (needAddTile)
			addTile();
	}
	void right() { rotate(180); left(); rotate(180); }
	void up() { rotate(270); left(); rotate(90); }
	void down() { rotate(90); left(); rotate(270); }
	u16 offsetCoords(u16 coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
	void drawTile(QPainter &painter, Tile *const tile, u16 x, u16 y) {
		const u16 value = tile->value;
		const u16 xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(QRgb(tile->background())));
		painter.drawRoundedRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6, 6);
		if (value) {
			const u16 size = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(QRgb(tile->foreground())));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).horizontalAdvance(strValue), h = size + 4;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (win || lose) {
			painter.setBrush(QBrush(0x888888, Qt::Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QColor(0x800000));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			const int w = QFontMetrics(painter.font()).horizontalAdvance(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(0x776E65));
		painter.setFont(QFont("Sans", 14, QFont::Normal));
		const QString strScore = QString("Score: %1").arg(score);
		const int w = QFontMetrics(painter.font()).horizontalAdvance(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	explicit Board(QWidget *parent = nullptr) : QWidget(parent) { resetGame(true); }
	virtual ~Board() { deinitialize(); }
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		if (keyEvent->key() == Qt::Key_Escape)
			resetGame(false);
		if (!canMove())
			lose = true;
		if (!win && !lose)
			switch (keyEvent->key()) {
				case Qt::Key_Left: left(); break;
				case Qt::Key_Right: right(); break;
				case Qt::Key_Down: down(); break;
				case Qt::Key_Up: up(); break;
			}
		if (!win && !canMove())
			lose = true;
		update();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(0xBBADA0));
		for (u16 y = 0; y < VERTICAL; ++y)
			for (u16 x = 0; x < HORIZONTAL; ++x)
				drawTile(painter, board[x + y * 4], x, y);
		drawFinal(painter);
	}
};

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	srand(static_cast<u16>(time(nullptr)));
	Board boardWidget;
	boardWidget.resize(340, 400);
	boardWidget.show();
	return application.exec();
}

#include "2048-Qt5.moc"
