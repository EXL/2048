#include "2048.h"

#include <ZApplication.h>
#include <ZMainWidget.h>
//#include <ZKbMainWidget.h>
//#include <ZHeader.h>
//#include <ZSoftKey.h>
//#include <ZKeyDef.h>
//#include <ZMessageDlg.h>
//#include <ZOptionsMenu.h>
#include <ZGlobal.h>
//#include <ZNoticeDlg.h>

#include <ezxres.h> // TODO: ???
#include <ezxutilcst.h>

#include <qfileinfo.h>
#include <qtextcodec.h>
#include <qtimer.h>
#include <qlabel.h>

#include <ctime>



//#if defined(EZX_Z6) || defined (EZX_V8)
//	#define KEYCODE_0                              EZX_KEY_0
//	#define KEYCODE_2                              EZX_KEY_2
//	#define KEYCODE_4                              EZX_KEY_4
//	#define KEYCODE_6                              EZX_KEY_6
//	#define KEYCODE_8                              EZX_KEY_8
	#define KEYCODE_UP                             Qt::Key_Up
	#define KEYCODE_DOWN                           Qt::Key_Down
	#define KEYCODE_LEFT                           Qt::Key_Left
	#define KEYCODE_RIGHT                          Qt::Key_Right
	#define KEYCODE_CLEAR                          1000
// TODO: Check keys!!!
//	#ifdef EZX_V8
//	#define MAINDISPLAY_HEADER                     TINY_TYPE
//	#define TypeOK                                 just_ok
//	#endif
//#endif

#if defined(EZX_EM30) || defined (EZX_E8)
const int TILE_SIZE = 40;
const int FIELD_OFFSET_SCALE = 5;
#else
const int TILE_SIZE = 48;
const int FIELD_OFFSET_SCALE = 32;
#endif
const int TILE_MARGIN = 5;

class Widget : public QWidget {
	Q_OBJECT

	QPixmap *fb;
	QFont *font_large, *font_middle, *font_normal, *font_small;
	int ww, hh;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x) + ww / FIELD_OFFSET_SCALE, yOffset = offsetCoords(y);
		painter.setPen(QPen::NoPen);
		painter.setBrush(QColor(e_background(value)));
#if defined(EZX_Z6W) || defined(EZX_ZN5) || defined(EZX_U9)
		// HACK: Emulating drawRoundRect() method in 6 calls.
		const int w = TILE_SIZE / 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
		painter.drawPie(xOffset, yOffset, rect, rect, -16*180, -16*90);
		painter.drawPie(xOffset + w + rad - 1, yOffset, rect, rect, 16*90, -16*90);
		painter.drawPie(xOffset, yOffset + w + rad, rect, rect, -16*90, -16*90);
		painter.drawPie(xOffset + w + rad - 1, yOffset + w + rad, rect, rect, 0, -16*90);
		painter.drawRect(xOffset, yOffset + qw, TILE_SIZE - 2, rw);
		painter.drawRect(xOffset + qw - 1, yOffset, rw + 1, TILE_SIZE - 1);
#else
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
#endif
		if (value) {
			const int size = (value < 100) ? 18 : (value < 1000) ? 14 : 10;
			const QFont &font = *((value < 100) ? font_large : (value < 1000) ? font_middle : font_small);
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(e_foreground(value)));
			painter.setFont(font);
			const int w = QFontMetrics(font).width(strValue), h = (value < 100) ? size - 4 : size - 3;
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
		painter.setPen(QColor(COLOR_TEXT));
		painter.setFont(*font_normal);
		const QString strScore = QString("Score: %1").arg(e_score);
		const int w = QFontMetrics(*font_normal).width(strScore);
		painter.drawText(TILE_MARGIN, hh - 10, "Press '0' to Reset!");
		painter.drawText(ww - w - TILE_MARGIN, hh - 10, strScore);
	}
public:
	Widget(QWidget *parent = 0, const char *name = 0) : QWidget(parent, name, WRepaintNoErase | WResizeNoErase) {
		e_init(KEYCODE_CLEAR, KEYCODE_LEFT, KEYCODE_RIGHT, KEYCODE_UP, KEYCODE_DOWN);
		fb = NULL;
		font_large = new QFont("Sans", 18, QFont::Bold);
		font_middle = new QFont("Sans", 14, QFont::Bold);
		font_normal = new QFont("Sans", 14, QFont::Normal);
		font_small = new QFont("Sans", 10, QFont::Bold);
		QPixmap::setDefaultOptimization(QPixmap::NormalOptim);
		setBackgroundMode(NoBackground);
		setFocusPolicy(QWidget::StrongFocus);
	}
	~Widget() { delete fb; delete font_large; delete font_middle; delete font_normal; delete font_small; }
public slots:
	void screenShotTimer() { QTimer::singleShot(500, this, SLOT(screenShot())); }
	void reset() {
		e_key(KEYCODE_CLEAR);
		update();
	}
	void screenShot() {
		/*
		QPixmap pixmap(ww, hh);
		bitBlt(&pixmap, 0, 0, this, 0, 0, ww, hh, Qt::CopyROP, true);
		const QString path = QString("%1/%2.png").arg(QFileInfo(qApp->argv()[0]).dirPath(true)).arg(time(NULL));
		ZMessageDlg *msgDlg = new ZMessageDlg("", NULL, ZMessageDlg::TypeOK, 10*60*100);
		if (pixmap.save(path, "PNG")) {
			msgDlg->setTitle("Saved!");
			msgDlg->setInstructText(QString("Screenshot Saved! Path:\n%1").arg(path));
		} else {
			msgDlg->setTitle("Error!");
			msgDlg->setInstructText(QString("Error: Cannot Save Screenshot! Path: %1").arg(path));
			msgDlg->setTitleIcon(RES_ICON_Reader().getIcon("error_pop", true));
		}
		msgDlg->exec();
		delete msgDlg;
		*/
	}
	void save() {
		/*
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).dirPath(true)));
		if (save.open(IO_WriteOnly)) {
			QDateTime saveDateTime = QDateTime::currentDateTime();
			QDataStream dataStream(&save);
			dataStream << saveDateTime;
			for (int i = 0; i < BOARD_SIZE; ++i)
				dataStream << (Q_INT32) e_board[i];
			dataStream << e_score; dataStream << e_win; dataStream << e_lose;
			ZNoticeDlg::information(QString("State on:\n%1").arg(saveDateTime.toString()), "Game Saved!",
				QString::null, "ok_pop");
		} else
			ZNoticeDlg::information("Cannot create save.dat file.", "Save Error!", QString::null, "error_pop");
		*/
	}
	void load() {
		/*
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
			ZNoticeDlg::information(QString("State on:\n%1").arg(loadDateTime.toString()), "Game Loaded!",
				QString::null, "ok_pop");
			update();
		} else
			ZNoticeDlg::information("Cannot find save.dat file.", "Load Error!", QString::null, "error_pop");
		*/
	}
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		QWidget::keyPressEvent(keyEvent);
		int key = keyEvent->key();
		/*if (key == KEYCODE_0)
			e_key(KEYCODE_CLEAR);
		else if (key == KEYCODE_4)
			e_key(KEYCODE_LEFT);
		else if (key == KEYCODE_6)
			e_key(KEYCODE_RIGHT);
		else if (key == KEYCODE_2)
			e_key(KEYCODE_UP);
		else if (key == KEYCODE_8)
			e_key(KEYCODE_DOWN);
		*/
//		TODO: clear
			e_key(key);

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

	void setIconPath(QString &src, const QString &dest) {
		if (src == QString::null)
			src = (QFile::exists(dest)) ? dest : QString::null;
	}
public slots:
	void about() {
		/*
		ZMessageDlg *msgDlg = new ZMessageDlg("About 2048", QTextCodec::codecForName("UTF-8")->toUnicode(
			"2048 Game implementation especially for MotoMAGX platform.\n\nVersion: 1.0, %1\nThanks to: Boxa, fill.sa, "
			"VINRARUS\n© EXL (exl@bk.ru), 2020\nSource code: https://github.com/EXL/2048").arg(__DATE__),
			ZMessageDlg::TypeOK, 10*60*100);
		QString iconPath = QString::null;
		setIconPath(iconPath, "/mmc/mmca1/mgxbox/2048/icon_usr.png");
		setIconPath(iconPath, "/mmc/mmca1/mpkgbox/2048/icon_usr.png");
		setIconPath(iconPath, "/ezxlocal/download/mystuff/mgxbox/icon_usr.png");
		setIconPath(iconPath, "/ezxlocal/download/mystuff/mpkgbox/icon_usr.png");
		setIconPath(iconPath, QString("%1/icon_usr.png").arg(QFileInfo(qApp->argv()[0]).dirPath(true)));
		setIconPath(iconPath, "./icon_usr.png");
		setIconPath(iconPath, "icon_usr.png");
		if (iconPath != QString::null) {
			QPixmap icon(48, 48);
			icon.load(iconPath);
			msgDlg->setTitleIcon(icon);
		}
		msgDlg->exec();
		delete msgDlg;
		*/
	}
public:
	MainWidget() : ZMainWidget(false, NULL, NULL, 0) {
		QLabel *titleBar = new QLabel("2048-EZX", this);
		titleBar->setScaledContents(true); // TODO: ??
		setTitleBarWidget(titleBar);

		UTIL_CST *cst = new UTIL_CST(this, "Reset");
		setCSTWidget(cst);
		ZPushButton *leftButton = cst->getLeftBtn();
		ZPushButton *middleButton = cst->getMidBtn();
		ZPushButton *rightButton = cst->getRightBtn();
		connect(rightButton, SIGNAL(clicked()), qApp, SLOT(quit()));

		Widget *widget = new Widget(this, NULL);
		setContentWidget(widget);


		/*
		setAppTitle(name);
		Widget *widget = new Widget(this, "widget");
		setContentWidget(widget);
		ZSoftKey *softKeys = new ZSoftKey("CST_2A", this, this);
		QRect menuRect = ZGlobal::getContentR();
		ZOptionsMenu *menu = new ZOptionsMenu(menuRect, this, NULL, 0);
		menu->insertItem("Take Screenshot", NULL, widget, SLOT(screenShotTimer()), true, false, false, 0, 0);
		menu->insertSeparator(1, 1);
		menu->insertItem("Save Game", NULL, widget, SLOT(save()), true, false, false, 2, 2);
		menu->insertItem("Load Game", NULL, widget, SLOT(load()), true, false, false, 3, 3);
		menu->insertItem("Reset Game", NULL, widget, SLOT(reset()), true, false, false, 4, 4);
		menu->insertSeparator(5, 5);
		menu->insertItem("About", NULL, this, SLOT(about()), true, false, false, 6, 6);
		menu->insertItem(tr("TXT_RID_SOFTKEY_EXIT", "Exit"), NULL, qApp, SLOT(quit()), true, false, false, 7, 7);
		softKeys->setOptMenu(ZSoftKey::LEFT, menu);
		softKeys->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
		softKeys->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"), tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
		softKeys->setText(ZSoftKey::LEFT, tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
		softKeys->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_EXIT", "Exit"));
		softKeys->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
		setSoftKey(softKeys);
		*/
	}
};

int main(int argc, char *argv[]) {
	ZApplication application(argc, argv);
	MainWidget mainWidget;
	application.showMainWidget(&mainWidget);
	// application.setMainWidget(&mainWidget);
	// mainWidget.show();
	return application.exec();
}

#include "2048-EZX.moc"