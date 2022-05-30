#include "2048.h"

#include "ui_2048-Qt4-Qtopia4.h"

#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>

#include <QSoftMenuBar>
#include <QtopiaApplication>

const int FIELD_OFFSET_SCALE  = 32;
const int TILE_SIZE           = 48;
const int TILE_MARGIN         = 5;

class GameMainWidget : public QWidget, public Ui_GameMainWidget {
	Q_OBJECT

	QPixmap *fb;
	QFont *font_large, *font_middle, *font_normal, *font_small;
	int ww, hh;
	int score;
	bool rounded;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x) + ww / FIELD_OFFSET_SCALE, yOffset = offsetCoords(y) - TILE_MARGIN + 2;
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(e_background(value)));
		if (rounded)
			painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 36, 36);
		else
			painter.drawRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE);
		if (value) {
			const int size = (value < 100) ? 18 : (value < 1000) ? 14 : 10;
			const QFont &font = *((value < 100) ? font_large : (value < 1000) ? font_middle : font_small);
			const QString strValue = QString("%1").arg(value);
			if (value > 64)
				painter.setPen(QColor(COLOR_TEXT));
			else
				painter.setPen(QColor(e_foreground(value)));
			painter.setFont(font);
			const int wo = (value < 100) ? 1 : (value < 1000) ? 0 : (-1), ho = (value > 1000) ? 0 : 3;
			const int w = QFontMetrics(font).width(strValue) - wo, h = size - ho;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (e_win || e_lose) {
			painter.fillRect(0, 0, ww, hh, QBrush(COLOR_OVERLAY, Qt::Dense6Pattern));
			painter.setPen(QColor(COLOR_FINAL));
			painter.setFont(*font_large);
			const QString center = (e_win) ? "You won!" : "Game Over!";
			const int w = QFontMetrics(*font_large).width(center);
			painter.drawText(ww / 2 - w / 2, hh / 2, center);
		}
		painter.setPen(QColor(COLOR_TEXT));
		painter.setFont(*font_normal);
		const QString strScore = QString("Score: %1").arg(e_score);
		const int w = QFontMetrics(*font_normal).width(strScore);
		painter.drawText(TILE_MARGIN, hh - 10, "Press '0' to Reset!");
		painter.drawText(ww - w - TILE_MARGIN, hh - 10, strScore);
	}

protected:
	virtual void paintEvent(QPaintEvent *) {
		ww = width(); hh = height();
		if (!fb)
			fb = new QPixmap(ww, hh);
		QPainter painter;
		painter.begin(fb);
		painter.fillRect(0, 0, ww, hh, QColor(COLOR_BOARD));
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				drawTile(painter, e_board[x + y * LINE_SIZE], x, y);
		drawFinal(painter);
		painter.end();
		
		QPainter painterScreen(this);
		painterScreen.drawPixmap(0, 0, *fb);
	}
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		QWidget::keyPressEvent(keyEvent);
		int key = keyEvent->key();
		switch (key) {
			case Qt::Key_4: key = Qt::Key_Left;  break;
			case Qt::Key_6: key = Qt::Key_Right; break;
			case Qt::Key_2: key = Qt::Key_Up;    break;
			case Qt::Key_8: key = Qt::Key_Down;  break;
		}
		e_key(key);
		update();
	}
	virtual void mousePressEvent(QMouseEvent *mouseEvent) {
		QWidget::mousePressEvent(mouseEvent);
		const int w4 = ww / 4, h4 = hh / 4;
		const QRect up(w4, 0, w4 * 2, h4);
		const QRect down(w4, h4 * 3, w4 * 2, h4);
		const QRect left(0, h4, w4, h4 * 2);
		const QRect right(w4 * 3, h4, w4, h4 * 2);
		const QPoint click(mouseEvent->pos().x(), mouseEvent->pos().y());
		if (up.contains(click))
			e_key(Qt::Key_Up);
		else if (down.contains(click))
			e_key(Qt::Key_Down);
		else if (left.contains(click))
			e_key(Qt::Key_Left);
		else if (right.contains(click))
			e_key(Qt::Key_Right);
		repaint();
	}

public:
	GameMainWidget(QWidget *parent = 0, Qt::WFlags flags = 0) : QWidget(parent, flags) {
		setupUi(this);

		e_init(Qt::Key_0, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down);
		fb = NULL; score = 0; rounded = true;
		font_large = new QFont("Sans", 10, QFont::Bold);
		font_middle = new QFont("Sans", 8, QFont::Bold);
		font_normal = new QFont("Sans", 6, QFont::Normal);
		font_small = new QFont("Sans", 6, QFont::Bold);
		setFocusPolicy(Qt::StrongFocus);

		QMenu *menu = QSoftMenuBar::menuFor(this);
		Q_UNUSED(menu);

		QSoftMenuBar::setHelpEnabled(this, true);
	}
	~GameMainWidget() { }
};

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, GameMainWidget)
QTOPIA_MAIN

#include "2048-Qt4-Qtopia4.moc"
