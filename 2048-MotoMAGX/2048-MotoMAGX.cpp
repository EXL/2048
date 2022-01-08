#include "2048.h"

#include <ZApplication.h>
#include <ZKbMainWidget.h>
#include <ZHeader.h>
#include <ZSoftKey.h>
#include <ZKeyDef.h>
#include <ZMessageDlg.h>
#include <ZOptionsMenu.h>
#include <ZGlobal.h>
#include <ZNoticeDlg.h>

#ifndef MOTODEV_STUDIO
#include <RES_ICON_Reader.h>
#endif

#include <qfileinfo.h>
#include <qtextcodec.h>
#include <qtimer.h>

#include <ctime>

#if defined(EZX_EM30) || defined (EZX_E8)
const int TILE_SIZE = 40;
const int FIELD_OFFSET_SCALE = 5;
#else
const int TILE_SIZE = 48;
const int FIELD_OFFSET_SCALE = 32;
#endif
const int TILE_MARGIN = 5;

#if !defined(EZX_E2)
#define ICON_ABOUT_NAME "icon_usr.png"
#define ICON_ABOUT_SIZE 48
#define TARGET_PLATFORM "MotoMAGX"
#else
#define ICON_ABOUT_NAME "ezx_dia_50x50.png"
#define ICON_ABOUT_SIZE 50
#define TARGET_PLATFORM "EZX"
#endif

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
			if (value > 64)
				painter.setPen(QColor(COLOR_TEXT));
			else
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
		e_init(KEYCODE_0, KEYCODE_LEFT, KEYCODE_RIGHT, KEYCODE_UP, KEYCODE_DOWN);
		fb = NULL;
		font_large = new QFont("Sans", 20, QFont::Bold);
		font_middle = new QFont("Sans", 16, QFont::Bold);
		font_normal = new QFont("Sans", 16, QFont::Normal);
		font_small = new QFont("Sans", 14, QFont::Bold);
		QPixmap::setDefaultOptimization(QPixmap::NormalOptim);
		setBackgroundMode(NoBackground);
		setFocusPolicy(QWidget::StrongFocus);
	}
	~Widget() { delete fb; delete font_large; delete font_middle; delete font_normal; delete font_small; }
public slots:
	void screenShotTimer() { QTimer::singleShot(500, this, SLOT(screenShot())); }
	void reset() {
		e_key(KEYCODE_0);
		update();
	}
	void screenShot() {
		QPixmap pixmap(ww, hh);
		bitBlt(&pixmap, 0, 0, this, 0, 0, ww, hh, Qt::CopyROP, true);
		const QString path = QString("%1/%2.png").arg(QFileInfo(qApp->argv()[0]).dirPath(true)).arg(time(NULL));
		ZMessageDlg *msgDlg = new ZMessageDlg("", NULL, ZMessageDlg::TypeOK, 60*1000);
		if (pixmap.save(path, "PNG")) {
			msgDlg->setTitle("Saved!");
			msgDlg->setInstructText(QString("Screenshot Saved! Path:\n%1").arg(path));
		} else {
			msgDlg->setTitle("Error!");
			msgDlg->setInstructText(QString("Error: Cannot Save Screenshot! Path: %1").arg(path));
#ifndef MOTODEV_STUDIO
			msgDlg->setTitleIcon(RES_ICON_Reader().getIcon("error_pop", true));
#endif
		}
		msgDlg->exec();
		delete msgDlg;
	}
	void save() {
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
	}
	void load() {
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
	}
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		QWidget::keyPressEvent(keyEvent);
		int key = keyEvent->key();
		if (key == KEYCODE_4)
			e_key(KEYCODE_LEFT);
		else if (key == KEYCODE_6)
			e_key(KEYCODE_RIGHT);
		else if (key == KEYCODE_2)
			e_key(KEYCODE_UP);
		else if (key == KEYCODE_8)
			e_key(KEYCODE_DOWN);
#if !defined(EZX_Z6)
		else if (key == KEYCODE_CLEAR)
			e_key(KEYCODE_0);
#endif
		else
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

class MainWidget : public ZKbMainWidget {
	Q_OBJECT

public slots:
	void about() {
		ZMessageDlg *msgDlg = new ZMessageDlg("About 2048", QTextCodec::codecForName("UTF-8")->toUnicode(
			"2048 Game implementation especially for %1 platform.\n\n"
			"Version: 1.0, %2\nThanks to: Boxa, fill.sa, VINRARUS, Unreal_man\n"
			"© EXL (exl@bk.ru), 2020\nSource code: https://github.com/EXL/2048").arg(TARGET_PLATFORM).arg(__DATE__),
			ZMessageDlg::TypeOK, 60*1000);
		QString iconPath = QString("%1/%2").arg(QFileInfo(qApp->argv()[0]).dirPath(true)).arg(ICON_ABOUT_NAME);
		if (QFile::exists(iconPath)) {
			QPixmap icon(ICON_ABOUT_SIZE, ICON_ABOUT_SIZE);
			icon.load(iconPath);
			msgDlg->setTitleIcon(icon);
		}
		msgDlg->exec();
		delete msgDlg;
	}
public:
	MainWidget(QWidget *parent = 0, const char *name = 0, WFlags flags = 0) :
		ZKbMainWidget(ZHeader::MAINDISPLAY_HEADER, parent, name, flags) {
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
#if !defined(EZX_E2)
		softKeys->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
#if !defined(EZX_EMU) && !defined(MOTODEV_STUDIO)
		softKeys->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"), tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
#endif
#endif
		softKeys->setText(ZSoftKey::LEFT, tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
		softKeys->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_EXIT", "Exit"));
		softKeys->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
		setSoftKey(softKeys);
	}
};

int main(int argc, char *argv[]) {
	ZApplication application(argc, argv);
	MainWidget mainWidget(NULL, "2048");
	application.setMainWidget(&mainWidget);
	mainWidget.show();
	return application.exec();
}

#if !defined(EZX_E2)
#include "2048-MotoMAGX.moc"
#else
#include "2048-EZX_E2.moc"
#endif
