#include "2048.h"

#include "ui_2048-Qt4-Qtopia4.h"

#include <qwidget.h>
#include <qsoftmenubar.h>

#include <qtopiaapplication.h>

class GameMainWidget : public QWidget, public Ui_GameMainWidget {
	Q_OBJECT
public:
	GameMainWidget(QWidget *parent = 0, Qt::WFlags flags = 0) : QWidget(parent, flags) {
		setupUi(this);

		QMenu *menu = QSoftMenuBar::menuFor(this);
		Q_UNUSED(menu);

		QSoftMenuBar::setHelpEnabled(this, true);
	}
	~GameMainWidget() { }
};

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, GameMainWidget)
QTOPIA_MAIN

#include "2048-Qt4-Qtopia4.moc"
