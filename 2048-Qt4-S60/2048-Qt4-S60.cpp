#include "2048.h"

#include "ui_2048-Qt4-S60.h"

#include <QApplication>
#include <QEvent>
#include <QFile>
#include <QFileInfo>
#include <QGesture>
#include <QGestureEvent>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QSwipeGesture>
#include <QWidget>

static const int TILE_SIZE   = 70;
static const int TILE_MARGIN = 16;

namespace Ui {
	class GameMainWindow;
}

class GameWindow : public QMainWindow {
	Q_OBJECT

	Ui::GameMainWindow *ui;

	int startX;
	int startY;

	inline int offsetCoords(int coord) { return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN; }
	void drawTile(QPainter &painter, int value, int x, int y) {
		const int xOffset = offsetCoords(x), yOffset = offsetCoords(y);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(e_background(value)));
		painter.drawRoundedRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6, 6);
		if (value) {
			const int size = (value < 100) ? 15 : (value < 1000) ? 11 : 6;
			const QString strValue = QString("%1").arg(value);
			painter.setPen(QColor(e_foreground(value)));
			painter.setFont(QFont("Sans", size, QFont::Bold));
			const int w = QFontMetrics(painter.font()).width(strValue), h = size + 4;
			painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 + 4, strValue);
		}
	}
	void drawFinal(QPainter &painter) {
		if (e_win || e_lose) {
			painter.fillRect(0, 0, width(), height(), QBrush(COLOR_OVERLAY, Qt::Dense6Pattern));
			painter.setPen(QColor(COLOR_FINAL));
			painter.setFont(QFont("Sans", 24, QFont::Bold));
			const QString center = (e_win) ? "You won!" : "Game Over!";
			const int w = QFontMetrics(painter.font()).width(center);
			painter.drawText(width() / 2 - w / 2, height() / 2, center);
		}
		painter.setPen(QColor(COLOR_TEXT));
		painter.setFont(QFont("Sans", 8, QFont::Normal));
		const QString strScore = QString("Score: %1").arg(e_score);
		const int w = QFontMetrics(painter.font()).width(strScore);
		// painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
		painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
	}
	bool gestureEvent(QGestureEvent *event) {
		if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
			swipeTriggered(static_cast<QSwipeGesture *>(swipe));
		return true;
	}
	void swipeTriggered(QSwipeGesture *gesture) {
		if (gesture->state() == Qt::GestureFinished) {
			if (gesture->horizontalDirection()) {
				if (QSwipeGesture::Left)
					e_key(Qt::Key_Left);
				else
					e_key(Qt::Key_Right);
			} else {
				if (QSwipeGesture::Up)
					e_key(Qt::Key_Up);
				else
					e_key(Qt::Key_Down);
			}
			repaint();
		}
	}

public:
	enum ScreenOrientation {
		ScreenOrientationLockPortrait,
		ScreenOrientationLockLandscape,
		ScreenOrientationAuto
	};
	explicit GameWindow(QWidget *parent = 0) :
		QMainWindow(parent), ui(new Ui::GameMainWindow), startX(0), startY(0) {
		e_init(Qt::Key_Escape, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down);
		ui->setupUi(this);
		// this->setOrientation(ScreenOrientationLockPortrait);
		setAttribute(Qt::WA_AcceptTouchEvents);
		grabGesture(Qt::SwipeGesture);
	}
	virtual ~GameWindow() {
		delete ui;
		ungrabGesture(Qt::SwipeGesture);
	}
	// Note that this will only have an effect on Symbian and Fremantle.
	void setOrientation(ScreenOrientation orientation) {
#if defined(Q_OS_SYMBIAN)
		// If the version of Qt on the device is < 4.7.2, that attribute won't work
		if (orientation != ScreenOrientationAuto) {
			const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
			if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
				qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
				return;
			}
		}
#endif // Q_OS_SYMBIAN
		Qt::WidgetAttribute attribute;
		switch (orientation) {
#if QT_VERSION < 0x040702
		// Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
		case ScreenOrientationLockPortrait:
			attribute = static_cast<Qt::WidgetAttribute>(128);
			break;
		case ScreenOrientationLockLandscape:
			attribute = static_cast<Qt::WidgetAttribute>(129);
			break;
		default:
		case ScreenOrientationAuto:
			attribute = static_cast<Qt::WidgetAttribute>(130);
			break;
#else // QT_VERSION < 0x040702
		case ScreenOrientationLockPortrait:
			attribute = Qt::WA_LockPortraitOrientation;
			break;
		case ScreenOrientationLockLandscape:
			attribute = Qt::WA_LockLandscapeOrientation;
			break;
		default:
		case ScreenOrientationAuto:
			attribute = Qt::WA_AutoOrientation;
			break;
#endif // QT_VERSION < 0x040702
		};
		setAttribute(attribute, true);
	}
	void showExpanded() {
#ifdef Q_OS_SYMBIAN
		showFullScreen();
#elif defined(Q_WS_MAEMO_5)
		showMaximized();
#else
		show();
#endif
	}

protected:
	void keyPressEvent(QKeyEvent *keyEvent) {
		e_key(keyEvent->key());
		update();
	}
	void paintEvent(QPaintEvent *) {
		QPainter painter(this);
		painter.fillRect(0, 0, width(), height(), QColor(COLOR_BOARD));
		for (int y = 0; y < LINE_SIZE; ++y)
			for (int x = 0; x < LINE_SIZE; ++x)
				drawTile(painter, e_board[x + y * LINE_SIZE], x, y);
		drawFinal(painter);
	}
#if 0
	void mousePressEvent(QMouseEvent *mouseEvent) {
		QWidget::mousePressEvent(mouseEvent);
		const int w4 = width() / 4, h4 = height() / 4;
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
#endif
	void mousePressEvent(QMouseEvent *mouseEvent) {
		QWidget::mousePressEvent(mouseEvent);
		startX = mouseEvent->pos().x();
		startY = mouseEvent->pos().y();
	}
	void mouseReleaseEvent(QMouseEvent *mouseEvent) {
		QWidget::mousePressEvent(mouseEvent);
		int stopX = mouseEvent->pos().x();
		int stopY = mouseEvent->pos().y();
		if (abs(startX - stopX) > 50 || abs(startY - stopY) > 50) {
			if (abs(startX - stopX) < abs(startY - stopY)) {
				if (startY > stopY)
					e_key(Qt::Key_Up);
				else
					e_key(Qt::Key_Down);
			} else {
				if (startX > stopX)
					e_key(Qt::Key_Left);
				else
					e_key(Qt::Key_Right);
			}
		}
		repaint();
	}
	bool event(QEvent *event) {
		if (event->type() == QEvent::Gesture)
			return gestureEvent(static_cast<QGestureEvent*>(event));
		return QWidget::event(event);
	}

private slots:
	void on_actionNew_Game_triggered() {
		e_key(Qt::Key_Escape);
		repaint();
	}
	void on_actionSave_triggered() {
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).path()));
		if (save.open(QIODevice::WriteOnly)) {
			QDateTime saveDateTime = QDateTime::currentDateTime();
			QDataStream dataStream(&save);
			dataStream << saveDateTime;
			for (int i = 0; i < BOARD_SIZE; ++i)
				dataStream << (qint32)e_board[i];
			dataStream << e_score; dataStream << e_win; dataStream << e_lose;
			QMessageBox::information(this, QString("State on:\n%1").arg(saveDateTime.toString()),
				"Game Saved!", QMessageBox::Ok);
		}
		else
			QMessageBox::information(this, "Cannot create \"save.dat\" file.", "Save Error!", QMessageBox::Ok);
	}
	void on_actionLoad_triggered() {
		QFile save(QString("%1/save.dat").arg(QFileInfo(qApp->argv()[0]).path()));
		if (save.open(QIODevice::ReadOnly)) {
			QDateTime loadDateTime;
			QDataStream dataStream(&save);
			dataStream >> loadDateTime;
			qint32 value, score, win, lose;
			for (int i = 0; i < BOARD_SIZE; ++i) {
				dataStream >> value;
				e_board[i] = value;
			}
			dataStream >> score; dataStream >> win; dataStream >> lose;
			e_score = score; e_win = win; e_lose = lose;
			QMessageBox::information(this, QString("State on:\n%1").arg(loadDateTime.toString()),
				"Game Loaded!", QMessageBox::Ok);
			repaint();
		}
		else
			QMessageBox::information(this, "Cannot find \"save.dat\" file.", "Load Error!", QMessageBox::Ok);
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	GameWindow gameWindow;
	Qt::WindowFlags flags;
	flags |= Qt::WindowSoftkeysVisibleHint;
	flags &= ~Qt::WindowSoftkeysRespondHint;
	gameWindow.setWindowFlags(flags);
	gameWindow.showFullScreen();
	return app.exec();
}

#include "2048-Qt4-S60.moc"
