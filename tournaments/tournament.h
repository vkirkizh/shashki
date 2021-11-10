#ifndef _TOURNAMENT_H_
	#define _TOURNAMENT_H_

	#include <QtCore>
	#include <string>
	#include <ctype.h>
	#include "Model/board.h"
	#include "Model/game.h"
	#include "Players/player.h"

	class Tournament: public QObject {
		Q_OBJECT
	protected:
		Game *game;
		Player *wp, *bp;
		std::string title;
		int Num;
		int Cnt, w, b, d;
	public:
		Tournament(std::string _title, Player *_wp, Player *_bp, int _Num);
	protected:
		void startGame();
		void results();
	public slots:
		void finishGame(GAMESTATE);
	};

	bool is_numeric(char *s);

#endif
