#ifndef _CONTROL_H_
	#define _CONTROL_H_

	#include <QtGui>
	#include "Model/game.h"
	#include "View/view_main.h"
	#include "View/view_startgame.h"
	#include "View/view_board.h"
	#include "View/view_info.h"
	#include "View/view_finishgame.h"

	class Control: public QApplication {
		Q_OBJECT
	protected:
		Game *game;
		View_Main *main_ui;
		View_StartGame *start_ui;
		View_FinishGame *finish_ui;
		View_Board *board_ui;
		View_Info *info_ui;
	public:
		Control(int &argc, char** argv);
		~Control();
	signals:
		void newGameSignal();
		void startGameSignal();
	public slots:
		void newGame();
		void createGame(Player *wp, Player *bp);
		void finishGame(GAMESTATE);
	};

#endif
