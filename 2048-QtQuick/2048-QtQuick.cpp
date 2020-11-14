#include "2048.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QColor>
#include <QVariant>

// TODO: Delete this
#include <QDebug>

class GameEngineWrapper: public QObject {
	Q_OBJECT

	QQmlContext *context;
	QVariantList gameBoard;
public:
	GameEngineWrapper(QQmlContext *rootContext) {
		context = rootContext;
		e_init(Qt::Key_Escape, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down);
		gameBoard.reserve(BOARD_SIZE);
		updateGameBoard();
	}
public slots:
	int lineSize() const { return LINE_SIZE; }
	void keyEvent(int keyCode) { e_key(keyCode); }
	QColor textColor(int value) { return QColor(e_foreground(value)); }
	QColor rectColor(int value) { return QColor(e_background(value)); }
	void updateGameBoard() {
		gameBoard.clear();
		for (int i = 0; i < BOARD_SIZE; ++i)
			gameBoard.push_back(e_board[i]);
		context->setContextProperty("gameBoard", QVariant::fromValue(gameBoard));
	}
};

int main(int argc, char *argv[]) {
	const QUrl url(QStringLiteral("qrc:/2048-QtQuick.qml"));

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	GameEngineWrapper wrapper(engine.rootContext());
	engine.rootContext()->setContextProperty("gameEngine", &wrapper);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}

#include "2048-QtQuick.moc"
