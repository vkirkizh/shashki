#include "tournament.h"

Tournament::Tournament(std::string _title, Player *_wp, Player *_bp, int _Num) {
	Cnt = 0;
	w = b = d = 0;
	Num = _Num;
	title = _title;
	wp = _wp;
	bp = _bp;
	startGame();
}

void Tournament::startGame() {
	game = new Game();
	connect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));
	game->init(wp, bp);
	game->start();
}

void Tournament::results() {
	qDebug() << "----------------------------------------";
	qDebug() << title.c_str();
	qDebug() << "White: " << w;
	qDebug() << "Black: " << b;
	qDebug() << "Draws: " << d;
	qDebug() << "----------------------------------------";
}

void Tournament::finishGame(GAMESTATE res_flag) {
	delete game;
	switch (res_flag) {
		case END_WHITE:
			w++;
		break;
		case END_BLACK:
			b++;
		break;
		default:
			d++;
		break;
	}
	if (Cnt % 100 == 0) qDebug() << title.c_str() << " :: " << Cnt << " (w: " << w << ", b: " << b << ", d: " << d << ")";
	if (++Cnt >= Num) {
		results();
	} else {
		startGame();
	}
}

bool is_numeric(char *s) {
	if (!s) return false;
	while (*s) {
		if (!isdigit(*s++)) return false;
	}
	return true;
}
