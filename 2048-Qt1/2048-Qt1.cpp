#include "2048.h"

#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qkeycode.h>

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

static inline unsigned R(unsigned rgb) { return (rgb >> 16) & 0xFF; }
static inline unsigned G(unsigned rgb) { return (rgb >> 8) & 0xFF; }
static inline unsigned B(unsigned rgb) { return (rgb >> 0) & 0xFF; }

class Widget : public QWidget {
	Q_OBJECT

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const unsigned bkg = e_background(value), frg = e_foreground(value);
		const int xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		painter.setPen(NoPen);
		painter.setBrush(QColor(R(bkg), G(bkg), B(bkg)));
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
		if (value) {
			const int size = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
			const QString strValue = QString().setNum(value);
			painter.setPen(QColor(R(frg), G(frg), B(frg)));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).width(strValue), h = size + 4;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (e_win || e_lose) {
			painter.fillRect(0, 0, width(), height(),
				QBrush(QColor(R(COLOR_OVERLAY), G(COLOR_OVERLAY), B(COLOR_OVERLAY)), Dense6Pattern));
			painter.setPen(QColor(R(COLOR_FINAL), G(COLOR_FINAL), B(COLOR_FINAL)));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = (e_win) ? "You won!" : "Game Over!";
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(R(COLOR_TEXT), G(COLOR_TEXT), B(COLOR_TEXT)));
		painter.setFont(QFont("Sans", 14, QFont::Normal));
		QString strScore = QString().sprintf("Score: %d", e_score);
		const int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	Widget(QWidget *parent = 0) : QWidget(parent) { e_init(Key_Escape, Key_Left, Key_Right, Key_Up, Key_Down); }
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		e_key(keyEvent->key());
		repaint();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(R(COLOR_BOARD), G(COLOR_BOARD), B(COLOR_BOARD)));
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				drawTile(painter, e_board[x + y * LINE_SIZE], x, y);
		drawFinal(painter);
	}
};

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	Widget widget;
	application.setMainWidget(&widget);
	widget.setFixedSize(340, 400);
	widget.show();
	return application.exec();
}

#include "2048-Qt1.moc"
