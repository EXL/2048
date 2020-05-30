#include <qwidget.h>
#include <qevent.h>
#include <qpainter.h>
#include <qapplication.h>
//#include <qvector.h>
//#include <qlist.h>
#include <qfont.h>
#include <qfontmetrics.h>

#include <algorithm>
#include <vector>

#include <cstdlib>
#include <cmath>

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

const int vertical = 4;
const int horizontal = 4;
const int boardSize = vertical * horizontal;
const int ourTarget = 2048;

const int BG_COLOR = 0xBBADA0;
//const int BG_COLOR = 0xFF0000;
const int TILE_SIZE = 32;
const int TILES_MARGIN = 16;

double mathRandom() {
	return rand() / (double) RAND_MAX;
}

struct Tile {
	int value;

	Tile(int value) {
		this->value = value;
	}
	~Tile() {
		qDebug("Deleted!");
	}
	bool isEmpty() {
		return (value == 0);
	}
	int getForeground() {
		return (value < 16) ? 0x776E65 : 0xF9F6F2;
	}
	int getBackground() {
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

	//Tile *myTiles[boardSize];

	// TODO:
	//QVector<Tile> myTiles;
	Tile *myTiles[boardSize];

	bool myWin;
	bool myLose;
	int myScore;

	void resetGame() {
		myScore = 0;
		myWin = false;
		myLose = false;
		// myTiles.resize(boardSize);
		for (uint i = 0; i < boardSize; i++) {
			myTiles[i] = new Tile(0);
			// myTiles.insert(i, new Tile(0));
		}
		addTile();
		addTile();
	}
	void addTile() {
		std::vector<Tile *> vector = availableSpace();
		if (!vector.empty()) {
			uint index = (uint) (mathRandom() * vector.size()) % vector.size();
			Tile *emptyTile = vector[index];
			emptyTile->value = (mathRandom() < 0.9) ? 2 : 4;
		}
	}
	std::vector<Tile *> availableSpace() {
		std::vector<Tile *> vector;
		for (uint i = 0; i < boardSize; ++i) {
			if (myTiles[i]->isEmpty()) {
				vector.push_back(myTiles[i]);
			}
		}
		return vector;
	}
	bool canMove() {
		if (!isFull()) {
			return true;
		}
		for (uint x = 0; x < horizontal; x++) {
			for (uint y = 0; y < vertical; y++) {
				Tile *t = tileAt(x, y);
				if ((x < 3 && t->value == tileAt(x + 1, y)->value) ||
				   ((y < 3) && t->value == tileAt(x, y + 1)->value)) {
					return true;
				}
			}
		}
		return false;
	}
	Tile *tileAt(uint x, uint y) {
		return myTiles[x + y * 4];
	}
	bool isFull() {
		return availableSpace().size() == 0;
	}
	std::vector<Tile *> getLine(uint index) {
		std::vector<Tile *> result;
		for (uint i = 0; i < horizontal; i++) {
			result.push_back(tileAt(i, index));
		}
		return result;
	}
	std::vector<Tile *> mergeLine(std::vector<Tile *> oldLine) {
		// QList<Tile> list;
		std::vector<Tile *> vector;
		for (int i = 0; i < horizontal && !oldLine[i]->isEmpty(); i++) {
			int num = oldLine.at(i)->value;
			if (i < 3 && oldLine.at(i)->value == oldLine.at(i + 1)->value) {
				num *= 2;
				myScore += num;
				if (num == ourTarget) {
					myWin = true;
				}
				i++;
			}
			vector.push_back(new Tile(num));
		}
		if (vector.size() == 0) {
			return oldLine;
		} else {
			// QVector<Tile> vector(horizontal);
			ensureSize(vector, horizontal);
			//for (int i = 0; i < horizontal; ++i) {
			//	vector.insert(i, list.at(i));
			//}
			// list.toVector(&vector);
			return vector;
		}
	}
	void ensureSize(std::vector<Tile *> &v, uint s) {
		while (v.size() != s) {
			v.push_back(new Tile(0));
		}
	}
	std::vector<Tile *> moveLine(std::vector<Tile *> oldLine) {
		std::vector<Tile *> vector;
		//QList<Tile> l;
		for (uint i = 0; i < horizontal; i++) {
			if (!oldLine[i]->isEmpty()) {
				vector.push_back(oldLine[i]);
			}
		}
		///////////// ??????????????????????????????????????????????
//		QList<Tile> l;
//		uint reversedCnt = reversed.count();
//		for (int i = reversed.count() - 1; i >= 0; --i) {
//			l.append(reversed.at(i));
//		}
		if (vector.size() == 0) {
			return oldLine;
		} else {
			// QVector<Tile> newLine(horizontal);
			ensureSize(vector, horizontal);
			// for (uint i = 0; i < horizontal; ++i) {
				/// ????????????????????????????????????????????????????????
				/// newLine[i] = l.removeFirst();
				///
				//newLine.insert(i, l.at(i));
				//l.removeFirst();
			//	newLine.insert(i, l.at(i));
			//}
			return vector;
		}
	}
	void setLine(uint index, std::vector<Tile *> re) {
		for (uint i = 0; i < horizontal; ++i) {
			myTiles[index * 4 + i] = re[i];
		}
		/// System.arraycopy(re, 0, myTiles, index * 4, 4); ???
	}
	bool compare(std::vector<Tile *> line1, std::vector<Tile *> line2) {
		/// ???????????????
		/*if (&line1 == &line2) {
			return true;
		} else
		*/
		if (line1.size() != line2.size()) {
			return false;
		}

		for (uint i = 0; i < line1.size(); ++i) {
			if (line1[i]->value != line2[i]->value) {
				return false;
			}
		}

		return true;
	}
	/*QVector<Tile>*/ void rotate(int angle) {
		Tile *newTiles[boardSize];
		// QVector<Tile> newTiles(boardSize);
		int offsetX = 3, offsetY = 3;
		if (angle == 90) {
			offsetY = 0;
		} else if (angle == 270) {
			offsetX = 0;
		}

		double rad = degreesToRadians(angle);
		////////////////// ?????
		int cos = (int) ::cos(rad);
		int sin = (int) ::sin(rad);
		for (int x = 0; x < horizontal; x++) {
			for (int y = 0; y < vertical; y++ ) {
				int newX = (x * cos) - (y * sin) + offsetX;
				int newY = (x * sin) + (y * cos) + offsetY;
				newTiles[(newX) + (newY) * 4] = tileAt(x, y);
			}
		}
		for (int i = 0; i < boardSize; ++i) {
			myTiles[i] = newTiles[i];
		}
	}
	void left() {
		bool needAddTile = false;
		for (int i = 0; i < horizontal; i++) {
			std::vector<Tile *> line = getLine(i);
			std::vector<Tile *> merged = mergeLine(moveLine(line));
			setLine(i, merged);
			if (!needAddTile && !compare(line, merged)) {
				needAddTile = true;
			}
		}
		if (needAddTile) {
			addTile();
		}
	}
	void right() {
		rotate(180);
		left();
		rotate(180);
	}
	void up() {
		rotate(270);
		left();
		rotate(90);
	}
	void down() {
		rotate(90);
		left();
		rotate(270);
	}
	void drawTile(QPainter &painter, Tile *tile, int x, int y) {
		int value = tile->value;
		int xOffset = offsetCoords(x);
		int yOffset = offsetCoords(y);
		painter.setPen(QPen::NoPen);
		painter.setBrush(QBrush(QColor(tile->getBackground())));
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
		painter.setPen(QPen(QColor(tile->getForeground())));
		const int size = (value < 100) ? 16 : (value < 1000) ? 10 : 8;
		painter.setFont(QFont("Sans", size, QFont::Bold));

		QString s = QString("%1").arg(value);

		int w = QFontMetrics(painter.font()).width(s);
		//int h = QFontMetrics(sans).height() - ((value < 100) ? 6 : 2);
		int h = (value < 100) ? size : size + 4;

		if (value != 0) {
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, s);
		}
	}
	int offsetCoords(int arg) {
		return arg * (TILES_MARGIN + TILE_SIZE) + TILES_MARGIN * 2;
	}
public:
	Board(QWidget *parent = 0) : QWidget(parent) {
		resize(240, 240);
		resetGame();
	}
	virtual ~Board() { }
protected:
	virtual void keyPressEvent(QKeyEvent *kEvent) {
		if (kEvent->key() == Key_Escape) {
			resetGame();
		}
		if (!canMove()) {
			myLose = true;
		}
		if (!myWin && !myLose) {
			switch (kEvent->key()) {
				case Key_Left: left(); break;
				case Key_Right: right(); break;
				case Key_Down: down(); break;
				case Key_Up: up(); break;
				case Key_W: myWin = true; break;
			}
		}
		if (!myWin && !canMove()) {
			myLose = true;
		}
		if (kEvent->key() == Key_Q) {
			myLose = true;
		}
		update(); // or repaint?
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QBrush(QColor(BG_COLOR)));
		for (int y = 0; y < vertical; y++) {
			for (int x = 0; x < horizontal; x++) {
				drawTile(painter, myTiles[x + y * 4], x, y);
			}
		}
		if (myWin || myLose) {
			painter.setBrush(QBrush(0x888888, Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QPen(QColor(0x4E8BCA)));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			QString center = ((myWin) ? "You won!" : (myLose) ? "Game Over!" : "");
			int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(0x776E65));
		painter.setFont(QFont("Sans", 10, QFont::Normal));
		QString score = QString("Score: %1").arg(myScore);
		int sW = QFontMetrics(painter.font()).width(score);
		painter.drawText(TILES_MARGIN, height() - 10, "ESC to restart!");
		painter.drawText(width() - sW - TILES_MARGIN, height() - 10, score);
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Board board;
	app.setMainWidget(&board);
	board.show();
	return app.exec();
}

#include "2048-Qt2.moc"
