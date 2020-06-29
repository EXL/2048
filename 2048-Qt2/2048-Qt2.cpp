#include "2048.h"

#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>

static const int TILE_SIZE = 64;
static const int TILE_MARGIN = 16;

class Widget : public QWidget {
	Q_OBJECT

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		painter.setPen(QPen::NoPen);
		painter.setBrush(QColor(e_background(value)));
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
		if (value) {
			const int size = (value < 100) ? 24 : (value < 1000) ? 18 : 14;
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(e_foreground(value)));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).width(strValue), h = size + 4;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (e_win || e_lose) {
			painter.setBrush(QBrush(COLOR_OVERLAY, Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QColor(COLOR_FINAL));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = (e_win) ? "You won!" : "Game Over!";
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(COLOR_TEXT));
		painter.setFont(QFont("Sans", 14, QFont::Normal));
		const QString strScore = QString("Score: %1").arg(e_score);
		const int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	Widget(QWidget *parent = 0) : QWidget(parent) { e_init(Key_Escape, Key_Left, Key_Right, Key_Up, Key_Down); }
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		e_key(keyEvent->key());
		update();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(COLOR_BOARD));
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

#include "2048-Qt2.moc"
