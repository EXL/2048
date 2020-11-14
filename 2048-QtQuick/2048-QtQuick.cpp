#include "2048.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class GameEngine: public QObject {
	Q_OBJECT
public:
	GameEngine() { e_init(Qt::Key_Escape, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down); }
public slots:
	int lineSize() const { return LINE_SIZE; }
	int boardSize() const { return BOARD_SIZE; }
};

int main(int argc, char *argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	const QUrl url(QStringLiteral("qrc:/2048-QtQuick.qml"));

	GameEngine gameEngine;
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("gameEngine", &gameEngine);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}

#include "2048-QtQuick.moc"
