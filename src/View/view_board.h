#ifndef _VIEW_BOARD_H_
	#define _VIEW_BOARD_H_

	#include <QtGui>
	#include "Model/game.h"
	#include "View/view_main.h"

	class View_Board: public QWidget, public Player {
		Q_OBJECT
	protected:
		Game *game;
		BOARD *board;
		QWidget *window;
		int ready;
		bool read_flag;
		GAMESTATE end_flag;
	public:
		View_Board(QWidget *parent);
		void init(Game *_game);
		virtual PLAYER_TYPE type() {return HUMAN;};
		virtual void execMove(BOARD board);
	protected:
		bool isReady();
		bool eventFilter(QObject *target, QEvent *event);
		virtual void paintEvent(QPaintEvent *event);
	public slots:
		void finishGame(GAMESTATE res_flag);
		void updateBoard();
	};

#endif
