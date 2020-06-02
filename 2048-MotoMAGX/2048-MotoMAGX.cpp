#include <ZApplication.h>
#include <ZKbMainWidget.h>
#include <ZHeader.h>
#include <ZSoftKey.h>
#include <ZKeyDef.h>

#include <vector>

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ctime>

#if defined(EZX_Z6) || defined (EZX_V8)
	#define KEYCODE_0                              EZX_KEY_0
	#define KEYCODE_2                              EZX_KEY_2
	#define KEYCODE_4                              EZX_KEY_4
	#define KEYCODE_6                              EZX_KEY_6
	#define KEYCODE_8                              EZX_KEY_8
	#define KEYCODE_UP                             EZX_KEY_UP
	#define KEYCODE_DOWN                           EZX_KEY_DOWN
	#define KEYCODE_LEFT                           EZX_KEY_LEFT
	#define KEYCODE_RIGHT                          EZX_KEY_RIGHT
	#define KEYCODE_CLEAR                          EZX_KEY_CLEAR
	#ifdef EZX_V8
	#define MAINDISPLAY_HEADER                     TINY_TYPE
	#endif
#endif

struct Tile;

typedef unsigned short int u16;
typedef std::vector<Tile *> TileList;

const u16 HORIZONTAL = 4, VERTICAL = 4;
const u16 BOARD_SIZE = HORIZONTAL * VERTICAL;
const u16 END_GAME_TARGET = 2048;
const u16 TILE_SIZE = 32;
#if defined(EZX_EM30) || defined (EZX_E8)
const u16 TILE_MARGIN = 5;
#else
const u16 TILE_MARGIN = 16;
#endif

inline double DegreesToRadians(int angleDegrees) { return ((angleDegrees) * M_PI / 180.0); }
inline double MathRandom() { return rand() / static_cast<double>(RAND_MAX); }

struct Tile {
	u16 value;

	Tile(u16 value) { this->value = value; }
	bool empty() { return (value == 0); }
	unsigned foreground() { return (value < 16) ? 0xFF776E65 : 0xFFF9F6F2; }
	unsigned background() {
		switch (value) {
			case    2: return 0xFFEEE4DA;
			case    4: return 0xFFEDE0C8;
			case    8: return 0xFFF2B179;
			case   16: return 0xFFF59563;
			case   32: return 0xFFF67C5F;
			case   64: return 0xFFF65E3B;
			case  128: return 0xFFEDCF72;
			case  256: return 0xFFEDCC61;
			case  512: return 0xFFEDC850;
			case 1024: return 0xFFEDC53F;
			case 2048: return 0xFFEDC22E;
		}
		return 0xFFCDC1B4;
	}
};

class Board : public QWidget {
	Q_OBJECT

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
	u16 offsetCoords(u16 coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, Tile *const tile, u16 x, u16 y) {
		const u16 value = tile->value;
#if defined(EZX_EM30) || defined(EZX_E8)
		const int xOffset = offsetCoords(x) + width() / 4, yOffset = offsetCoords(y);
#else
		const u16 xOffset = offsetCoords(x), yOffset = offsetCoords(y);
#endif
		painter.setPen(QPen::NoPen);
		painter.setBrush(QColor(tile->background()));
#if defined(EZX_Z6W) || defined(EZX_ZN5) || defined(EZX_U9)
		// HACK: Emulating drawRoundRect() method in 9 calls.
		const u16 w = TILE_SIZE / 2, dw = w * 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
		painter.drawPie(xOffset, yOffset, rect, rect, -16*180, -16*90);
		painter.drawPie(xOffset + w + rad, yOffset, rect, rect, 16*90, -16*90);
		painter.drawPie(xOffset, yOffset + w + rad, rect, rect, -16*90, -16*90);
		painter.drawPie(xOffset + w + rad, yOffset + w + rad, rect, rect, 0, -16*90);
		painter.drawRect(xOffset + qw, yOffset + qw, TILE_SIZE - rad, TILE_SIZE - rad);
		painter.drawRect(xOffset, yOffset + qw, qw, rw);
		painter.drawRect(xOffset + dw - qw, yOffset + qw, qw, rw);
		painter.drawRect(xOffset + qw, yOffset, rw, qw);
		painter.drawRect(xOffset + qw, yOffset + dw - qw, rw, qw);
#else
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
#endif
		if (value) {
			const u16 size = (value < 100) ? 18 : (value < 1000) ? 14 : 10;
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(tile->foreground()));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).width(strValue), h = (value < 100) ? size - 4 : size - 3;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (win || lose) {
			painter.setBrush(QBrush(0xFF888888, Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QColor(0xFF800000));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(0xFF776E65));
		painter.setFont(QFont("Sans", 14, QFont::Normal));
		const QString strScore = QString("Score: %1").arg(score);
		const int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "Press '0' to Reset!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	Board(QWidget *parent = 0, const char *name = 0) : QWidget(parent, name, /* WFlags */ 0) {
		setFocusPolicy(QWidget::StrongFocus);
		resetGame(true);
	}
	virtual ~Board() { deinitialize(); Q_UNUSED(paddingByte0) Q_UNUSED(paddingByte1) }
public slots:
	void reset() {
		resetGame(false);
		update();
	}
	void screenShot() {
		QPixmap pixmap(width(), height());
		bitBlt(&pixmap, 0, 0, this, 0, 0, width(), height(), Qt::CopyROP, true);
		pixmap.save(QString("%1.png").arg(time(NULL)), "PNG");
	}
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		QWidget::keyPressEvent(keyEvent);
		int key = keyEvent->key();
		if (key == KEYCODE_0 || key == KEYCODE_CLEAR)
			resetGame(false);
		if (!canMove())
			lose = true;
		if (!win && !lose)
			switch (key) {
				case KEYCODE_UP: case KEYCODE_2: up(); break;
				case KEYCODE_DOWN: case KEYCODE_8: down(); break;
				case KEYCODE_LEFT: case KEYCODE_4: left(); break;
				case KEYCODE_RIGHT: case KEYCODE_6: right(); break;
			}
		if (!win && !canMove())
			lose = true;
		update();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(0xFFBBADA0));
		for (u16 y = 0; y < VERTICAL; ++y)
			for (u16 x = 0; x < HORIZONTAL; ++x)
				drawTile(painter, board[x + y * 4], x, y);
		drawFinal(painter);
	}
};

class MainWidget : public ZKbMainWidget {
	Q_OBJECT

	Board *board;
public:
	MainWidget(QWidget *parent = 0, const char *name = 0, WFlags flags = 0) :
		ZKbMainWidget(ZHeader::MAINDISPLAY_HEADER, parent, name, flags) {
		setAppTitle(tr(name));

		board = new Board(this, "board");
		setContentWidget(board);

		ZSoftKey *softKeys = new ZSoftKey("CST_2", this, this);
		softKeys->setText(ZSoftKey::RIGHT, "Exit");
		softKeys->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
		softKeys->setText(ZSoftKey::LEFT, "Reset");
		softKeys->setClickedSlot(ZSoftKey::LEFT, board, SLOT(reset()));
		setSoftKey(softKeys);
	}
};

int main(int argc, char *argv[]) {
	ZApplication application(argc, argv);
	srand(static_cast<u16>(time(NULL)));
	MainWidget mainWidget(NULL, "2048");
	application.setMainWidget(&mainWidget);
	mainWidget.show();
	return application.exec();
}

#include "2048-MotoMAGX.moc"