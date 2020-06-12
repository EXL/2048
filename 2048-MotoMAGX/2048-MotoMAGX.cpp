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

#include <RES_ICON_Reader.h>

#include <qfileinfo.h>
#include <qtextcodec.h>

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
	#define TypeOK                                 just_ok
	#endif
#endif

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

	int *board;
	ZOptionsMenu *menu;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN * 2; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x) + width() / FIELD_OFFSET_SCALE, yOffset = offsetCoords(y);
		painter.setPen(QPen::NoPen);
		painter.setBrush(QColor(e_background(value)));
#if defined(EZX_Z6W) || defined(EZX_ZN5) || defined(EZX_U9)
		// HACK: Emulating drawRoundRect() method in 9 calls.
		const int w = TILE_SIZE / 2, dw = w * 2, qw = w / 4, rad = qw * 2, rw = rad * 3, rect = w - rad;
		painter.drawPie(xOffset, yOffset, rect, rect, -16*180, -16*90);
		painter.drawPie(xOffset + w + rad - 1, yOffset, rect, rect, 16*90, -16*90);
		painter.drawPie(xOffset, yOffset + w + rad, rect, rect, -16*90, -16*90);
		painter.drawPie(xOffset + w + rad - 1, yOffset + w + rad, rect, rect, 0, -16*90);
		painter.drawRect(xOffset + qw, yOffset + qw, TILE_SIZE - rad, TILE_SIZE - rad);
		painter.drawRect(xOffset, yOffset + qw, qw, rw);
		painter.drawRect(xOffset + dw - qw - 2, yOffset + qw, qw, rw);
		painter.drawRect(xOffset + qw - 1, yOffset, rw + 1, qw);
		painter.drawRect(xOffset + qw, yOffset + dw - qw - 1, rw + 1, qw);
#else
		painter.drawRoundRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 20, 20);
#endif
		if (value) {
			const int size = (value < 100) ? 18 : (value < 1000) ? 14 : 10;
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(e_foreground(value)));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).width(strValue), h = (value < 100) ? size - 4 : size - 3;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 - 2, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		const bool win = e_win(), lose = e_lose();
		if (win || lose) {
			painter.setBrush(QBrush(COLOR_OVERLAY, Dense6Pattern));
			painter.drawRect(0, 0, width(), height());
			painter.setPen(QColor(COLOR_FINAL));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = ((win) ? "You won!" : (lose) ? "Game Over!" : "");
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(COLOR_TEXT));
		painter.setFont(QFont("Sans", 14, QFont::Normal));
		const QString strScore = QString("Score: %1").arg(e_score());
		const int w = QFontMetrics(painter.font()).width(strScore);
		painter.drawText(TILE_MARGIN, height() - 10, "Press '0' to Reset!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
public:
	Widget(ZOptionsMenu *menu, QWidget *parent = 0, const char *name = 0) : QWidget(parent, name, /* WFlags */ 0) {
		this->menu = menu;
		board = e_init_board(KEYCODE_CLEAR, KEYCODE_LEFT, KEYCODE_RIGHT, KEYCODE_UP, KEYCODE_DOWN);
		setFocusPolicy(QWidget::StrongFocus);
	}
public slots:
	void reset() {
		e_key_event(KEYCODE_CLEAR);
		update();
	}
	void screenShot() {
		menu->hide();
		QPixmap pixmap(width(), height());
		bitBlt(&pixmap, 0, 0, this, 0, 0, width(), height(), Qt::CopyROP, true);
		const QString path = QString("%1/%2.png").arg(QFileInfo(qApp->argv()[0]).dirPath(true)).arg(time(NULL));
		ZMessageDlg *msgDlg = new ZMessageDlg("", NULL, ZMessageDlg::TypeOK, 10*60*100);
		if (pixmap.save(path, "PNG")) {
			msgDlg->setTitle("Saved!");
			msgDlg->setInstructText(QString("Screenshot Saved! Path: %1").arg(path));
		} else {
			msgDlg->setTitle("Error!");
			msgDlg->setInstructText(QString("Error: Cannot Save Screenshot! Path: %1").arg(path));
			msgDlg->setTitleIcon(RES_ICON_Reader().getIcon("error_pop", true));
		}
		msgDlg->exec();
		delete msgDlg;
	}
	void save() {
		QFile save("save.dat");
		if (save.open(IO_WriteOnly)) {
			QDataStream dataStream(&save);
			dataStream << QDateTime::currentDateTime();
			for (int i = 0; i < BOARD_SIZE; ++i)
				dataStream << (Q_INT32) board[i];
			ZNoticeDlg::information("Game Saved!");
		} else
			ZNoticeDlg::information("Cannot create save.dat file.", "Save Error!", QString::null, "error_pop");
	}
	void load() {
		QFile save("save.dat");
		if (save.open(IO_ReadOnly)) {
			QDateTime loadDateTime;
			QDataStream dataStream(&save);
			dataStream >> loadDateTime;
			Q_INT32 value;
			for (int i = 0; i < BOARD_SIZE; ++i) {
				dataStream >> value;
				board[i] = value;
			}
			ZNoticeDlg::information(QString("Game loaded!\n\nState on: %1.").arg(loadDateTime.toString()));
		} else
			ZNoticeDlg::information("Cannot load save.dat file.", "Load Error!", QString::null, "error_pop");
	}
protected:
	virtual void keyPressEvent(QKeyEvent *keyEvent) {
		QWidget::keyPressEvent(keyEvent);
		int key = keyEvent->key();
		if (key == KEYCODE_0)
			e_key_event(KEYCODE_CLEAR);
		else if (key == KEYCODE_4)
			e_key_event(KEYCODE_LEFT);
		else if (key == KEYCODE_6)
			e_key_event(KEYCODE_RIGHT);
		else if (key == KEYCODE_2)
			e_key_event(KEYCODE_UP);
		else if (key == KEYCODE_8)
			e_key_event(KEYCODE_DOWN);
		else
			e_key_event(key);
		update();
	}
	virtual void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(COLOR_BOARD));
		int y = 0;
		for (; y < VERTICAL; ++y) {
			int x = 0;
			for (; x < HORIZONTAL; ++x)
				drawTile(painter, board[x + y * 4], x, y);
		}
		drawFinal(painter);
	}
};

class MainWidget : public ZKbMainWidget {
	Q_OBJECT
public slots:
	void about() {
		ZMessageDlg *msgDlg = new ZMessageDlg("About 2048", QTextCodec::codecForName("UTF-8")->toUnicode(
			"2048 Game implementation especially for MotoMAGX platform.\n\nVersion: 1.0, %1\nThx: Boxa, fill.sa, "
			"VINRARUS\n© EXL (exl@bk.ru), 2020").arg(__DATE__), ZMessageDlg::TypeOK, 10*60*100);
		if (QFile("icon.png").exists()) {
			QPixmap icon(48, 48);
			icon.load("icon.png");
			msgDlg->setTitleIcon(icon);
		}
		msgDlg->exec();
		delete msgDlg;
	}
public:
	MainWidget(QWidget *parent = 0, const char *name = 0, WFlags flags = 0) :
		ZKbMainWidget(ZHeader::MAINDISPLAY_HEADER, parent, name, flags) {
		setAppTitle(name);
		ZSoftKey *softKeys = new ZSoftKey("CST_2A", this, this);
		QRect menuRect = ZGlobal::getContentR();
		ZOptionsMenu *menu = new ZOptionsMenu(menuRect, this, NULL, 0);
		menu->insertItem("Take Screenshot", NULL, widget, SLOT(screenShot()), true, false, false, 0, 0);
		menu->insertItem("Save Game", NULL, widget, SLOT(save()), true, false, false, 1, 1);
		menu->insertItem("Load Game", NULL, widget, SLOT(load()), true, false, false, 2, 2);
		menu->insertItem("Reset Game", NULL, widget, SLOT(reset()), true, false, false, 3, 3);
		menu->insertItem("About", NULL, this, SLOT(about()), true, false, false, 4, 4);
		menu->insertSeparator(5, 5);
		menu->insertItem(tr("TXT_RID_SOFTKEY_EXIT", "Exit"), NULL, qApp, SLOT(quit()), true, false, false, 6, 6);
		softKeys->setOptMenu(ZSoftKey::LEFT, menu);
		softKeys->setTextForOptMenuHide(tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
		softKeys->setTextForOptMenuShow(tr("TXT_RID_SOFTKEY_SELECT", "Select"), tr("TXT_RID_SOFTKEY_CANCEL", "Cancel"));
		softKeys->setText(ZSoftKey::LEFT, tr("TXT_RID_SOFTKEY_OPTIONS", "Options"));
		softKeys->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_EXIT", "Exit"));
		softKeys->setClickedSlot(ZSoftKey::RIGHT, qApp, SLOT(quit()));
		setSoftKey(softKeys);
		Widget *widget = new Widget(menu, this, "widget");
		setContentWidget(widget);
	}
};

int main(int argc, char *argv[]) {
	ZApplication application(argc, argv);
	MainWidget mainWidget(NULL, "2048");
	application.setMainWidget(&mainWidget);
	mainWidget.show();
	return application.exec();
}

#include "2048-MotoMAGX.moc"
