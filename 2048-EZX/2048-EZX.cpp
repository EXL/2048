#include "2048.h"

#include <ZApplication.h>
#include <ZMainWidget.h>
#include <ZMessageBox.h>
#if defined(EZX_E680)
#include <ZGlobal.h>
#endif

#include <ezxres.h>
#if defined(EZX_E680)
#include <ezxutilgraph.h>
#include <ezxutilpushbutton.h>
#elif defined(EZX_E680I) || defined(EZX_E6)
#include <ezxutilcst.h>
#endif

#include <qfileinfo.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qtextcodec.h>
#include <qtimer.h>

#include <ctime>

#if defined(EZX_E680)
#define EZX_MainWidget(titlebar, editmode, parent, name, flags) ZMainWidget(editmode, parent, name, flags)
#define EZX_MessageBox(p, button) ZMessageBox(p, NULL, QString::null, button, QString::null, QString::null)
#define EZX_ICON_Reader(iconName) RES_ICON_Reader().getIcon(iconName)
#elif defined(EZX_E680I)
#define EZX_MainWidget(titlebar, editmode, parent, name, flags) ZMainWidget(titlebar, editmode, parent, name, flags)
#define EZX_MessageBox(p, button) ZMessageBox(p, NULL, QString::null, button, QString::null, QString::null)
#define EZX_ICON_Reader(iconName) RES_ICON_Reader().getIcon(iconName)
#elif defined(EZX_E6)
#define EZX_MainWidget(titlebar, editmode, parent, name, flags) ZMainWidget(titlebar, editmode, parent, name, flags)
#define EZX_MessageBox(p, button) ZMessageBox(p, NULL, QString::null, button)
#define EZX_ICON_Reader(iconName) RES_ICON_Reader().getIcon(iconName, true)
#endif

#if defined(EZX_E680) || defined(EZX_E680I)
#define STR_ABOUT "<font size=\"2\"><b>About 2048-EZX</b></font><br><br><font size=\"1\">" \
	"2048 Game implementation especially for Motorola EZX platform.<br><br>Version: 1.0, %1<br>© EXL (exl@bk.ru)<br>" \
	"<u>https://github.com/EXL/2048</u></font>"
#define STR_SCR_OK "<h3>Saved!</h3><br><font size=\"1\"><b>Screenshot Saved!<br>Path:<br></b>%1</font>"
#define STR_SCR_ERR "<h3>Error!</h3><br><font size=\"1\"><b>Error: Cannot Save Screenshot!<br>Path:</b><br>%1</font>"
#define STR_SAV_OK "<font size=\"2\"><b>Game Saved!</b></font><br><br><font size=\"1\">State on:<br>%1</font>"
#define STR_SAV_ERR "<font size=\"2\"><b>Save Error!</b></font><br><br><font size=\"1\">" \
	"Cannot create save.dat file.</font>"
#define STR_LOAD_OK "<font size=\"2\"><b>Game Loaded!</b></font><br><br><font size=\"1\">State on:<br>%1</font>"
#define STR_LOAD_ERR "<font size=\"2\"><b>Load Error!</b></font><br><br><font size=\"1\">" \
	"Cannot find save.dat file.</font>"
#elif defined(EZX_E6)
#define STR_ABOUT "<h3>About 2048-EZX</h3><br><font size=\"2\">" \
	"2048 Game implementation especially for Motorola EZX platform.<br><br>Version: 1.0, %1<br>© EXL (exl@bk.ru)<br>" \
	"<u>https://github.com/EXL/2048</u></font>"
#define STR_SCR_OK "<h3>Saved!</h3><br>Screenshot Saved!<br>Path:<br><font size=\"2\">%1</font>"
#define STR_SCR_ERR "<h3>Error!</h3><br>Error: Cannot Save Screenshot!<br>Path:<br><font size=\"2\">%1</font>"
#define STR_SAV_OK "<h3>Game Saved!</h3><br>State on:\n%1"
#define STR_SAV_ERR "<h3>Save Error!</h3><br>Cannot create save.dat file."
#define STR_LOAD_OK "<h3>Game Loaded!</h3><br>State on:\n%1"
#define STR_LOAD_ERR "<h3>Load Error!</h3><br>Cannot find save.dat file."
#endif

#if defined(EZX_E680) || defined(EZX_E680I)
#define ICN_DLG_OK "Dialog_Complete.g"
#define ICN_DLG_ERR "Dialog_Error.g"
#define ICN_DLG_QUE "Dialog_Question_Mark.g"
#elif defined(EZX_E6)
#define ICN_DLG_OK "Dialog_Complete"
#define ICN_DLG_ERR "Dialog_Error"
#define ICN_DLG_QUE "Dialog_Exclamatory_Mark"
#endif

#if defined(EZX_E680)
#define KEY_RESET      Qt::Key_F7
#define KEY_RESET_ADD  Qt::Key_F8
#define KEY_LEFT       Qt::Key_Prior
#define KEY_RIGHT      Qt::Key_Next
#elif defined(EZX_E680I)
#define KEY_RESET      Qt::Key_F11
#define KEY_RESET_ADD  Qt::Key_F12
#define KEY_LEFT       Qt::Key_Left
#define KEY_RIGHT      Qt::Key_Right
#elif defined(EZX_E6)
#define KEY_RESET      Qt::Key_PageUp
#define KEY_RESET_ADD  Qt::Key_PageDown
#define KEY_LEFT       Qt::Key_Left
#define KEY_RIGHT      Qt::Key_Right
#endif
#define KEY_UP         Qt::Key_Up
#define KEY_DOWN       Qt::Key_Down

const int FIELD_OFFSET_SCALE  = 32;
const int TILE_SIZE           = 48;
const int TILE_MARGIN         = 5;

class Widget : public QWidget {
	Q_OBJECT

	QPixmap *fb;
	QFont *font_large, *font_middle, *font_small;
	int ww, hh;
	int score;
	bool rounded;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x) + ww / FIELD_OFFSET_SCALE, yOffset = offsetCoords(y) - TILE_MARGIN - 1;
		painter.setPen(QPen::NoPen);
		painter.setBrush(QColor(e_background(value)));
		if (rounded)
			painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 36, 36);
		else
			painter.drawRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE);
		if (value) {
			const int size = (value < 100) ? 18 : (value < 1000) ? 14 : 10;
			const QFont &font = *((value < 100) ? font_large : (value < 1000) ? font_middle : font_small);
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(e_foreground(value)));
			painter.setFont(font);
			const int wo = (value < 100) ? 1 : (value < 1000) ? 0 : (-1), ho = (value > 1000) ? 0 : 3;
			const int w = QFontMetrics(font).width(strValue) - wo, h = size - ho;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (e_win || e_lose) {
			painter.fillRect(0, 0, ww, hh, QBrush(COLOR_OVERLAY, Dense6Pattern));
			painter.setPen(QColor(COLOR_FINAL));
			painter.setFont(*font_large);
			const QString center = (e_win) ? "You won!" : "Game Over!";
			const int w = QFontMetrics(*font_large).width(center);
			painter.drawText(ww / 2 - w / 2, hh / 2, center);
		}
		if (score != e_score) {
			score = e_score;
			emit scoreChanged(score);
		}
	}
signals:
	void scoreChanged(int);
public:
	Widget(QWidget *parent = 0, const char *name = 0) : QWidget(parent, name, WRepaintNoErase | WResizeNoErase) {
		e_init(KEY_RESET, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);
		fb = NULL; score = 0; rounded = true;
		font_large = new QFont("Sans", 20, QFont::Bold);
		font_middle = new QFont("Sans", 18, QFont::Bold);
		font_small = new QFont("Sans", 16, QFont::Bold);
		QPixmap::setDefaultOptimization(QPixmap::NormalOptim);
		setBackgroundMode(NoBackground);
		setFocusPolicy(QWidget::StrongFocus);
	}
	~Widget() { delete fb; delete font_large; delete font_middle; delete font_small; }
	void setRounded(bool aRounded) {
		rounded = aRounded;
		update();
	}
public slots:
	void screenShotTimer() { QTimer::singleShot(500, this, SLOT(screenShot())); }
	void reset() {
		e_key(KEY_RESET);
		update();
	}
	void screenShot() {
		const QWidget *parent = static_cast<QWidget *>(this->parent());
		const int wp = parent->width(), hp = parent->height();
		QPixmap pixmap(wp, hp);
		bitBlt(&pixmap, 0, 0, parent, 0, 0, wp, hp, Qt::CopyROP, true);
		const QString path = QString("%1/%2.png").arg(QFileInfo(qApp->argv()[0]).dirPath(true)).arg(time(NULL));
		const QString pathReplaced = QString(path).replace(QString("/"), " / ");
		ZMessageBox *msgDlg = new EZX_MessageBox(this, "OK");
		if (pixmap.save(path, "PNG")) {
			msgDlg->setText(QString(STR_SCR_OK).arg(pathReplaced));
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_OK));
		} else {
			msgDlg->setText(QString(STR_SCR_ERR).arg(pathReplaced));
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_ERR));
		}
		msgDlg->exec();
		delete msgDlg;
	}
	void save() {
		ZMessageBox *msgDlg = new EZX_MessageBox(this, "OK");
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).dirPath(true)));
		if (save.open(IO_WriteOnly)) {
			QDateTime saveDateTime = QDateTime::currentDateTime();
			QDataStream dataStream(&save);
			dataStream << saveDateTime;
			for (int i = 0; i < BOARD_SIZE; ++i)
				dataStream << (Q_INT32) e_board[i];
			dataStream << e_score; dataStream << e_win; dataStream << e_lose;
			msgDlg->setText(QString(STR_SAV_OK).arg(saveDateTime.toString()));
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_OK));
		} else {
			msgDlg->setText(QString(STR_SAV_ERR));
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_ERR));
		}
		msgDlg->exec();
		delete msgDlg;
	}
	void load() {
		ZMessageBox *msgDlg = new EZX_MessageBox(this, "OK");
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).dirPath(true)));
		if (save.open(IO_ReadOnly)) {
			QDateTime loadDateTime;
			QDataStream dataStream(&save);
			dataStream >> loadDateTime;
			Q_INT32 value, score, win, lose;
			for (int i = 0; i < BOARD_SIZE; ++i) {
				dataStream >> value;
				e_board[i] = value;
			}
			dataStream >> score; dataStream >> win; dataStream >> lose;
			e_score = score; e_win = win; e_lose = lose;
			msgDlg->setText(QString(STR_LOAD_OK).arg(loadDateTime.toString()));
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_OK));
			update();
		} else {
			msgDlg->setText(QString(STR_LOAD_ERR));
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_ERR));
		}
		msgDlg->exec();
		delete msgDlg;
	}
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		QWidget::keyPressEvent(keyEvent);
		int key = keyEvent->key();
		if (key == KEY_RESET_ADD) // Side button "A" or Vol "-" button and side button "B" or Vol "+" button.
			e_key(KEY_RESET);
		else
			e_key(key);
		repaint();
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
			e_key(KEY_UP);
		else if (down.contains(click))
			e_key(KEY_DOWN);
		else if (left.contains(click))
			e_key(KEY_LEFT);
		else if (right.contains(click))
			e_key(KEY_RIGHT);
		repaint();
	}
	virtual void paintEvent(QPaintEvent *) {
		ww = width(); hh = height();
		if (!fb)
			fb = new QPixmap(ww, hh);
		QPainter painter;
		painter.begin(fb, this);
		painter.fillRect(0, 0, ww, hh, QColor(COLOR_BOARD));
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				drawTile(painter, e_board[x + y * LINE_SIZE], x, y);
		drawFinal(painter);
		painter.end();
		bitBlt(this, 0, 0, fb, 0, 0, ww, hh, Qt::CopyROP, true);
	}
};

class MainWidget : public ZMainWidget {
	Q_OBJECT

	enum Menu { M_SCREEN, M_SAVE, M_LOAD, M_RESET, M_SOUND, M_ROUNDED, M_RECTANGLE, M_TILES, M_ABOUT, M_EXIT };
	Widget *widget;
	QLabel *titleBar;
	QPopupMenu *menu, *tileMenu;
	bool sound;

public slots:
	void about() {
		ZMessageBox *msgDlg = new EZX_MessageBox(this, "Close");
		msgDlg->setText(QTextCodec::codecForName("UTF-8")->toUnicode(STR_ABOUT).arg(__DATE__));
		const QString iconPath = QString("%1/ezx_dia_50x50.png").arg(QFileInfo(qApp->argv()[0]).dirPath(true));
		if (QFile::exists(iconPath)) {
			QPixmap icon(50, 50);
			icon.load(iconPath);
			msgDlg->setIconPixmap(icon);
		} else
			msgDlg->setIconPixmap(EZX_ICON_Reader(ICN_DLG_QUE));
		msgDlg->exec();
		delete msgDlg;
	}
	void setTitleScore(int score) { titleBar->setText(QString(" 2048-EZX | Score: %1 ").arg(score)); }
	void roundedOn() {
		widget->setRounded(true);
		tileMenu->setItemChecked(M_ROUNDED, true);
		tileMenu->setItemChecked(M_RECTANGLE, false);
	}
	void roundedOff() {
		widget->setRounded(false);
		tileMenu->setItemChecked(M_ROUNDED, false);
		tileMenu->setItemChecked(M_RECTANGLE, true);
	}
	void soundOnOff() {
		sound = !sound;
		menu->setItemChecked(M_SOUND, sound);
		static_cast<ZApplication *>(qApp)->enableTouchSound(sound);
	}
public:
	MainWidget() : EZX_MainWidget(" 2048-EZX | Score: 0 ", false, NULL, NULL, 0), sound(true) {
		widget = new Widget(this, NULL);
		connect(widget, SIGNAL(scoreChanged(int)), this, SLOT(setTitleScore(int)));
		setContentWidget(widget);

		menu = new QPopupMenu(this);
		menu->insertItem("Take Screenshot", widget, SLOT(screenShotTimer()), 0, M_SCREEN);
		menu->insertSeparator();
		menu->insertItem("Save Game", widget, SLOT(save()), 0, M_SAVE);
		menu->insertItem("Load Game", widget, SLOT(load()), 0, M_LOAD);
		menu->insertItem("Reset Game", widget, SLOT(reset()), 0, M_RESET);
		menu->insertSeparator();
		menu->insertItem("Touch Sounds", this, SLOT(soundOnOff()), 0, M_SOUND);
		menu->setItemChecked(M_SOUND, true);
		tileMenu = new QPopupMenu(this);
		tileMenu->insertItem("Rounded", this, SLOT(roundedOn()), 0, M_ROUNDED);
		tileMenu->insertItem("Rectangle", this, SLOT(roundedOff()), 0, M_RECTANGLE);
		tileMenu->setItemChecked(M_ROUNDED, true);
		menu->insertItem("Tiles", tileMenu, 0, M_TILES);
		menu->insertSeparator();
		menu->insertItem("About...", this, SLOT(about()), 0, M_ABOUT);
		menu->insertItem("Exit", qApp, SLOT(quit()), 0, M_EXIT);

#if defined(EZX_E680I) || defined(EZX_E6)
		titleBar = static_cast<QLabel *>(getTitleBarWidget());

		UTIL_CST *cst = new UTIL_CST(this, "Reset");
		connect(cst->getMidBtn(), SIGNAL(clicked()), widget, SLOT(reset()));
		connect(cst->getRightBtn(), SIGNAL(clicked()), qApp, SLOT(quit()));
		cst->getLeftBtn()->setPopup(menu);
		setCSTWidget(cst);
#elif defined(EZX_E680)
		titleBar = new QLabel(" 2048-EZX | Score: 0 ", this);
		titleBar->setIndent(5);
		titleBar->setGeometry(ZGlobal::mapFromGlobalR(titleBar, ZGlobal::getStatusBarR()));
		titleBar->setFixedSize(ZGlobal::getStatusBarR().size());
		UTIL_Graph::makeTitle(titleBar, 0);
		QFont titleFont("Sans", 18, QFont::Normal);
		titleBar->setFont(titleFont);
		titleBar->show();

		QWidget *cst = (QWidget *) this->getCSTWidget();

		UTIL_PushButton *buttonExit = new UTIL_PushButton("CST_Exit", cst, 0, -1, -1);
		buttonExit->setFlags(UTIL_PushButton::JoinRight);
		buttonExit->setGeometry(ZGlobal::mapFromGlobalR(buttonExit, ZGlobal::getCst3_1R()));
		buttonExit->show();
		connect(buttonExit, SIGNAL(clicked()), qApp, SLOT(quit()));

		UTIL_PushButton *buttonReset = new UTIL_PushButton(NULL, cst, 0, -1, -1);
		buttonReset->setFlags(UTIL_PushButton::JoinRight | UTIL_PushButton::JoinLeft);
		buttonReset->setGeometry(ZGlobal::mapFromGlobalR(buttonReset, ZGlobal::getCst3_2R()));
		buttonReset->setText("Reset");
		buttonReset->show();
		connect(buttonReset, SIGNAL(clicked()), widget, SLOT(reset()));

		UTIL_PushButton *buttonMenu = new UTIL_PushButton("CST_Menu", cst, 0, -1, -1);
		buttonMenu->setFlags(UTIL_PushButton::JoinLeft);
		buttonMenu->setGeometry(ZGlobal::mapFromGlobalR(buttonMenu, ZGlobal::getCst3_3R()));
		buttonMenu->show();
		buttonMenu->setPopup(menu);

		QRect widgetRect = ZGlobal::getContentR();
		widgetRect.setY(widgetRect.y() + ZGlobal::getStatusBarR().height());
		widget->setGeometry(ZGlobal::mapFromGlobalR(widget, widgetRect));
#endif
	}
};

int main(int argc, char *argv[]) {
	ZApplication application(argc, argv);
	MainWidget mainWidget;
	application.showMainWidget(&mainWidget);
	return application.exec();
}

#include "2048-EZX.moc"
