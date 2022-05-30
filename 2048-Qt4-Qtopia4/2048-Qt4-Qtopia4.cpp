#include "ui_2048-Qt4-Qtopia4.h"

#include <qtopiaapplication.h>

class GameWindow : public QWidget, public Ui_ExampleBase {
	Q_OBJECT
public:
	GameWindow(QWidget *parent = 0, Qt::WFlags f = 0) {
	
	}
	~GameWindow() {
	
	}
};

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, GameWindow)
QTOPIA_MAIN

#include "2048-Qt4-Qtopia4.moc"
