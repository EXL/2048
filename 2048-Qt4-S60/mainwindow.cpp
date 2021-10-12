#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "2048.h"

#include <QtCore/QCoreApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>

static const int TILE_SIZE = 70;
static const int TILE_MARGIN = 16;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setOrientation(ScreenOrientationLockPortrait);

    e_init(Qt::Key_Escape, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
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

void MainWindow::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}

inline int MainWindow::offsetCoords(int coord)
{
    return coord * (TILE_MARGIN + TILE_SIZE) + TILE_MARGIN;
}

void MainWindow::drawTile(QPainter &painter, int value, int x, int y)
{
    const int xOffset = offsetCoords(x), yOffset = offsetCoords(y);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(e_background(value)));
    painter.drawRoundedRect(xOffset, yOffset, TILE_SIZE, TILE_SIZE, 6, 6);
    if (value)
    {
        const int size = (value < 100) ? 15 : (value < 1000) ? 10 : 6;
        const QString strValue = QString("%1").arg(value);
        painter.setPen(QColor(e_foreground(value)));
        painter.setFont(QFont("Sans", size, QFont::Bold));
        const int w = QFontMetrics(painter.font()).width(strValue), h = size + 4;
        painter.drawText(xOffset + (TILE_SIZE - w) / 2, yOffset + TILE_SIZE - (TILE_SIZE - h) / 2 + 4, strValue);
     }
}

void MainWindow::drawFinal(QPainter &painter)
{
    if (e_win || e_lose)
    {
        painter.fillRect(0, 0, width(), height(), QBrush(COLOR_OVERLAY, Qt::Dense6Pattern));
        painter.setPen(QColor(COLOR_FINAL));
        painter.setFont(QFont("Sans", 24, QFont::Bold));
        const QString center = (e_win) ? "You won!" : "Game Over!";
        const int w = QFontMetrics(painter.font()).width(center);
        painter.drawText(width() / 2 - w / 2, height() / 2, center);
    }

    painter.setPen(QColor(COLOR_TEXT));
    painter.setFont(QFont("Sans", 20, QFont::Normal));
    const QString strScore = QString("Score: %1").arg(e_score);
    const int w = QFontMetrics(painter.font()).width(strScore);
    //painter.drawText(TILE_MARGIN, height() - 10, "ESC to Restart!");
    painter.drawText(width() - w - TILE_MARGIN, height() - 10, strScore);
}


void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    e_key(keyEvent->key());
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), QColor(COLOR_BOARD));
    for (int y = 0; y < LINE_SIZE; ++y)
        for (int x = 0; x < LINE_SIZE; ++x)
            drawTile(painter, e_board[x + y * LINE_SIZE], x, y);
    drawFinal(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
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
