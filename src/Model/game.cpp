#include "Model/game.h"

Game::Game() {
	//qDebug() << "Game::Game()";

	wp = NULL;
	bp = NULL;
	thread = NULL;
}

Game::~Game() {
	//qDebug() << "Game::~Game()";
}

void Game::init(Player *_wp, Player *_bp) {
	//qDebug() << "Game::init(Player *_wp, Player *_bp)";

	if (!_wp || !_bp) exit(1);

	wp = _wp;
	bp = _bp;
}

void Game::start() {
	//qDebug() << "Game::start()";

	setCurrentPlayer(WHITE);

	move();
}

void Game::setCurrentPlayer(COLOR color) {
	current = color == WHITE ? wp : bp;
	current->setColor(color);
	board.startMove(color);
	emit currentPlayer(color);
}

void Game::move() {
	thread = new getMoveThread;
	thread->setData(current, board);
	connect(thread, SIGNAL(finished()), SLOT(recieveMove()));
	thread->start(QThread::NormalPriority);
}

void getMoveThread::run() {
	current->execMove(*board);
}

void Game::finish(GAMESTATE res_flag) {
	//qDebug() << "Game::finish(GAMESTATE res_flag)";

	emit finishGame(res_flag);
}

void Game::recieveMove() {
	GAMESTATE res_flag;
	MOVE mv = current->getMove();
	delete thread;
	if (!board.move(mv)) {
		//qDebug() << "(!) wrong move: " << mv.from.x+1 << "," << mv.from.y+1 << " >> " << mv.to.x+1 << "," << mv.to.y+1;
		move();
		return;
	}
	emit updateBoard();
	if (res_flag = board.isWin()) {
		finish(res_flag);
		return;
	}
	if (!board.canMove()) {
		setCurrentPlayer(current->getColor() == WHITE ? BLACK : WHITE);
	}
	move();
}
