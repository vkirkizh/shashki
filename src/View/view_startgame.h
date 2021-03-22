#ifndef _VIEW_STARTGAME_H_
	#define _VIEW_STARTGAME_H_

	#include <QtGui>
	#include "View/view_main.h"
	#include "Players/player.h"
	#include "Players/ai_player.h"

	class View_StartGame: public QObject {
		Q_OBJECT
	protected:
		QWidget *window;
		QFrame *greeting;
		QFrame *settings;
		QPushButton *next_btn;
		Ai_Player *AiPlr;
		PLAYER_TYPE wPlr, bPlr;
		Player *wp, *bp;
		COLOR curColor;
	public:
		View_StartGame(QWidget *parent);
		void show();
		void hide();
		void setupPlayerBegin(COLOR color);
		~View_StartGame();
		void setupAi();
		void setupAiShowLevel();
		void setupAiEnd();
	signals:
		void createGame(Player *wp, Player *bp);
		void setupPlayerEndSignal(Player *p);
	protected slots:
		void startGame();
		void setupPlayerEndSlot(Player *p);
		void setupAiGetLevel();
	};

#endif
