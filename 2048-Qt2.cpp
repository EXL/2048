#include <qwidget.h>
#include <qevent.h>
#include <qpainter.h>
#include <qapplication.h>

class Board : public QWidget {
	Q_OBJECT
public:
	Board(QWidget *parent = 0) : QWidget(parent) {
		resize(240, 240);
	}
	virtual ~Board() { }
protected:
	virtual void paintEvent(QPaintEvent *paintEvent) {
		QPainter painter(this);
		painter.setBrush( colorGroup().foreground() );
		//painter.save();
		painter.drawText(20, 50, "AAAAAAAAAAAAAa");
		//painter.restore();
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Board board;
	app.setMainWidget(&board);
	board.show();
	return app.exec();
}

#include "2048-Qt2.moc"
