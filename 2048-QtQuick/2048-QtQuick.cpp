#include "2048.h"

#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QColor>
#include <QVariant>
#include <QVariantList>

class GameEngineWrapper: public QObject {
	Q_OBJECT

	QQmlContext *context;
	QVariantList gameBoard;

	void sync() {
		gameBoard.clear();
		for (int i = 0; i < BOARD_SIZE; ++i)
			gameBoard.push_back(e_board[i]);
		context->setContextProperty("gameBoard", QVariant::fromValue(gameBoard));
		context->setContextProperty("gameScore", e_score);
		context->setContextProperty("gameWin", e_win);
		context->setContextProperty("gameLose", e_lose);
	}
public:
	GameEngineWrapper(QQmlContext *rootContext) {
		context = rootContext;
		e_init(Qt::Key_Escape, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down);
		gameBoard.reserve(BOARD_SIZE);
		sync();
	}
public slots:
	int lineSize() const { return LINE_SIZE; }
	void keyEvent(int keyCode) { e_key(keyCode); sync(); }
	QColor foregroundColor(int value) { return QColor(e_foreground(value)); }
	QColor backgroundColor(int value) { return QColor(e_background(value)); }
	QColor boardColor() { return QColor(COLOR_BOARD); }
	QColor textColor() { return QColor(COLOR_TEXT); }
	QColor overlayColor() { return QColor(COLOR_OVERLAY); }
	QColor finalColor() { return QColor(COLOR_FINAL); }
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
