#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

protected:
    void keyPressEvent(QKeyEvent *keyEvent);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mouseEvent);

private:
    void drawFinal(QPainter &painter);
    inline int offsetCoords(int coord);
    void drawTile(QPainter &painter, int value, int x, int y);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
