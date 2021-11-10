#include "control.h"

Control::Control(int &argc, char** argv):QApplication(argc, argv) {
	qDebug() << "run Qt Application";

	game = 0;

	main_ui = new View_Main;
	start_ui = new View_StartGame(main_ui);
	board_ui = new View_Board(main_ui);
	info_ui = new View_Info(main_ui);
	finish_ui = new View_FinishGame(main_ui);
	qDebug() << "all views created";

	main_ui->show();
	qDebug() << "main UI showed";

	connect(this, SIGNAL(newGameSignal()), this, SLOT(newGame()));
	connect(main_ui, SIGNAL(newGameSignal()), this, SLOT(newGame()));

	emit newGameSignal();

	qDebug() << "Application has been run";
}

void Control::newGame() {
	qDebug() << "try to start new game";

	if (game) emit finishGame(END_DRAW);

	connect(start_ui, SIGNAL(createGame(Player*, Player*)), this, SLOT(createGame(Player*, Player*)));

	connect(main_ui, SIGNAL(quit()), this, SLOT(quit()));

	board_ui->hide();
	info_ui->hide();
	finish_ui->hide();
	start_ui->hide();

	start_ui->show();

	qDebug() << "new game started";
}

void Control::createGame(Player *wp, Player *bp) {
	qDebug() << "try to create new game";

	disconnect(start_ui, SIGNAL(createGame(Player*, Player*)), this, SLOT(createGame(Player*, Player*)));

	game = new Game;
	qDebug() << "game created";

	connect(game, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));
	connect(main_ui, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));

	if (wp == NULL) wp = board_ui;
	if (bp == NULL) bp = board_ui;
	qDebug() << "players initialized";

	game->init(wp, bp);
	qDebug() << "game initialized";

	board_ui->init(game);
	info_ui->init(game);
	qDebug() << "views initialized";

	qDebug() << "game->start();";
	game->start();
}

void Control::finishGame(GAMESTATE res_flag) {
	qDebug() << "try to finish current game";

	if (!game) {
		qDebug() << "can not finish current game (game has been already finished)";
		return;
	}

	disconnect(game, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));
	disconnect(main_ui, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));

	info_ui->hide();

	finish_ui->showResult(res_flag);

	delete game;
	game = 0;
	qDebug() << "game destroyed";
}

Control::~Control() {
	qDebug() << "Control::~Control() -> BEGIN";

	delete main_ui;

	qDebug() << "Control::~Control() -> END";
}
