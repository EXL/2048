#include "2048.h"

#include "ui_2048-Qt4-Qtopia4.h"

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QTextCodec>
#include <QTimer>

#include <QSoftMenuBar>

#include <QtopiaStyle>
#include <QtopiaApplication>

#include <ctime>

const int FIELD_OFFSET_SCALE  = 32;
const int TILE_SIZE           = 48;
const int TILE_MARGIN         = 5;

class GameMainWidget : public QWidget, public Ui_GameMainWidget {
	Q_OBJECT

	int ww, hh;
	int score;
	bool rounded;
	QPixmap *fb;
	QFont *font_large, *font_middle, *font_normal, *font_small;
	QAction *actionRounded, *actionRectangle;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x) + ww / FIELD_OFFSET_SCALE, yOffset = offsetCoords(y) - TILE_MARGIN + 2;
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(e_background(value)));
		if (rounded)
			QtopiaStyle::drawRoundRect(&painter, QRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE), 20, 20);
			// painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 36, 36);
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
			const int wo = (value < 100) ? 1 : (value < 1000) ? 0 : (-1), ho = (value > 1000) ? 2 : 3;
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
	void updateActions(bool isRounded) {
		rounded = isRounded;
		actionRounded->setChecked(rounded);
		actionRectangle->setChecked(!rounded);
		update();
	}

private slots:
	void slotScreenshot() { QTimer::singleShot(500, this, SLOT(slotMakeScreenshot())); }
	void slotMakeScreenshot() {
		QPixmap fullScreenPixmap = QPixmap::grabWindow(QtopiaApplication::desktop()->winId());
		const QString path = QString("%1/%2.png").arg(QFileInfo(qApp->argv()[0]).dir().absolutePath()).arg(time(NULL));
		if (fullScreenPixmap.save(path, "PNG")) {
			QMessageBox::information(
				this,
				tr("Saved!"),
				tr("Screenshot Saved!<br><br>Path:<br><font size=\"2\">%1</font>").arg(path)
			);
		} else {
			QMessageBox::critical(
				this,
				tr("Error!"),
				tr("Error: Cannot Save Screenshot!<br>Path:<br><font size=\"2\">%1</font>").arg(path)
			);
		}
	}
	void slotSave() {
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).dir().absolutePath()));
		if (save.open(QIODevice::WriteOnly)) {
			QDateTime saveDateTime = QDateTime::currentDateTime();
			QDataStream dataStream(&save);
			dataStream << saveDateTime;
			for (int i = 0; i < BOARD_SIZE; ++i)
				dataStream << e_board[i];
			dataStream << e_score; dataStream << e_win; dataStream << e_lose;
			QMessageBox::information(
				this,
				tr("Game Saved!"),
				tr("Game Saved!<br>State on:<br><font size=\"2\">%1</font>").arg(saveDateTime.toString())
			);
		} else
			QMessageBox::critical(this, tr("Save Error!"), tr("Save Error!<br>Cannot create save.dat file."));
	}
	void slotLoad() {
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).dir().absolutePath()));
		if (save.open(QIODevice::ReadOnly)) {
			QDateTime loadDateTime;
			QDataStream dataStream(&save);
			dataStream >> loadDateTime;
			int value, score, win, lose;
			for (int i = 0; i < BOARD_SIZE; ++i) {
				dataStream >> value;
				e_board[i] = value;
			}
			dataStream >> score; dataStream >> win; dataStream >> lose;
			e_score = score; e_win = win; e_lose = lose;
			QMessageBox::information(
				this,
				tr("Game Loaded!"),
				tr("Game Loaded!<br>State on:<br><font size=\"2\">%1</font>").arg(loadDateTime.toString())
			);
			update();
		} else
			QMessageBox::critical(this, tr("Load Error!"), tr("Load Error!<br>Cannot find save.dat file."));
	}
	void slotReset() {
		e_key(Qt::Key_0);
		update();
	}
	void slotRounded() { updateActions(true); }
	void slotRectangle() { updateActions(false); }
	void slotAbout() {
		QString aboutStr = tr("2048-Qt4-Qtopia4<br><br>");
		aboutStr += "<font size=\"2\">";
		aboutStr += tr("A 2048 puzzle game for Qtopia 4 platform using Qt 4 framework.<br><br>");
		aboutStr += tr("Version: 1.0, %1<br>").arg(__DATE__);
		aboutStr += QTextCodec::codecForName("UTF-8")->toUnicode("© EXL (exl@bk.ru)<br>");
		aboutStr += "1. <a href=\"https://exlmoto.ru\">exlmoto.ru</a><br>";
		aboutStr += "2. <a href=\"https://github.com/EXL/2048\">github.com/EXL/2048</a>";
		aboutStr += "</font>";
		QMessageBox::about(this, tr("About 2048"), aboutStr);
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

		QAction *actionScreenshot = new QAction(tr("Take Screenshot"), this);
		connect(actionScreenshot, SIGNAL(triggered()), this, SLOT(slotScreenshot()));
		QAction *actionSave = new QAction(tr("Save Game"), this);
		connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSave()));
		QAction *actionLoad = new QAction(tr("Load Game"), this);
		connect(actionLoad, SIGNAL(triggered()), this, SLOT(slotLoad()));
		QAction *actionReset = new QAction(tr("Reset Game"), this);
		connect(actionReset, SIGNAL(triggered()), this, SLOT(slotReset()));
		actionRounded = new QAction(tr("Rounded"), this);
		actionRounded->setCheckable(true);
		actionRounded->setChecked(true);
		connect(actionRounded, SIGNAL(triggered()), this, SLOT(slotRounded()));
		actionRectangle = new QAction(tr("Rectangle"), this);
		actionRectangle->setCheckable(true);
		connect(actionRectangle, SIGNAL(triggered()), this, SLOT(slotRectangle()));
		QAction *actionAbout = new QAction(QIcon(":icon/2048_qt4_qtopia4"), tr("About..."), this);
		connect(actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
		QAction *actionAboutQt = new QAction(tr("About Qt..."), this);
		connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

		QMenu *tilesMenu = new QMenu(tr("Tiles"), this);
		tilesMenu->addAction(actionRounded);
		tilesMenu->addAction(actionRectangle);

		QMenu *aboutMenu = new QMenu(tr("About"), this);
		aboutMenu->addAction(actionAbout);
		aboutMenu->addAction(actionAboutQt);

		QMenu *mainMenu = QSoftMenuBar::menuFor(this);
		mainMenu->addAction(actionScreenshot);
		mainMenu->addSeparator();
		mainMenu->addAction(actionSave);
		mainMenu->addAction(actionLoad);
		mainMenu->addAction(actionReset);
		mainMenu->addSeparator();
		mainMenu->addMenu(tilesMenu);
		mainMenu->addMenu(aboutMenu);

		QSoftMenuBar::setLabel(this, Qt::Key_Select, QSoftMenuBar::NoLabel);
		QSoftMenuBar::setHelpEnabled(this, true);

		QtopiaApplication::setInputMethodHint(this, QtopiaApplication::AlwaysOff);

		setWindowIcon(QIcon(":icon/2048_qt4_qtopia4"));

		// HACK: Don't use long game name in window title on Smart and Classic themes.
		QSettings gConfig("Trolltech", "qpe");
		gConfig.beginGroup("Appearance");
		const QString activeTheme = gConfig.value("Theme", "qtopia.conf").toString();
		if (activeTheme == "smart.conf" || activeTheme == "classic.conf")
			setWindowTitle("2048");
		gConfig.endGroup();
	}
	~GameMainWidget() { }
};

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, GameMainWidget)
QTOPIA_MAIN

#include "2048-Qt4-Qtopia4.moc"
