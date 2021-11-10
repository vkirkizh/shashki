#include "View/view_main.h"

View_Main::View_Main() {
	qDebug() << "View_Main::View_Main() -> BEGIN";

	setWindowFlags(Qt::Window);
	setWindowTitle("Draughts (shashki)");

	QAction *newgameBtn = new QAction("New game", this);
	connect(newgameBtn, SIGNAL(triggered()), SLOT(menuNewgame()));
	QAction *quitBtn = new QAction("Quit", this);
	connect(quitBtn, SIGNAL(triggered()), SLOT(menuQuit()));
	menuBar()->addAction(newgameBtn);
	menuBar()->addAction(quitBtn);

	qDebug() << "View_Main::View_Main() -> END";
}

View_Main::~View_Main() {
	qDebug() << "View_Main::~View_Main()";
}

void View_Main::menuNewgame() {
	qDebug() << "View_Main::menuNewgame";
	emit newGameSignal();
}

void View_Main::menuQuit() {
	qDebug() << "View_Main::menuQuit";
	emit quit();
}
