#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QPainter>

#include "2048.h"

const int TILE_SIZE = 64;
const int TILE_MARGIN = 16;

class Widget : public QWidget {
	Q_OBJECT

	int *board;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(e_background(value)));
		painter.drawRoundedRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6, 6);
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
		const bool win = e_win(), lose = e_lose();
		if (win || lose) {
			painter.setBrush(QBrush(0x888888, Qt::Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QColor(0x800000));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(0x776E65));
		painter.setFont(QFont("Sans", 14, QFont::Normal));
		const QString strScore = QString("Score: %1").arg(e_score());
		const int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	explicit Widget(QWidget *parent = NULL) : QWidget(parent) {
		board = e_init_board(Qt::Key_Escape, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down);
	}
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		e_key_event(keyEvent->key());
		update();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(0xBBADA0));
		for (int y = 0; y < VERTICAL; ++y)
			for (int x = 0; x < HORIZONTAL; ++x)
				drawTile(painter, board[x + y * 4], x, y);
		drawFinal(painter);
	}
};

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	Widget widget;
	widget.resize(340, 400);
	widget.show();
	return application.exec();
}

#include "2048-Qt4.moc"
