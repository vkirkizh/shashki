#ifndef _VIEW_FINISHGAME_H_
	#define _VIEW_FINISHGAME_H_

	#include <QtGui>
	#include "Model/game.h"
	#include "View/view_main.h"

	class View_FinishGame: public QLabel {
		Q_OBJECT
	protected:
		QWidget *window;
	public:
		View_FinishGame(QWidget *parent);
		void showResult(GAMESTATE res_flag);
	};

#endif
