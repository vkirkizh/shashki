#ifndef _VIEW_INFO_H_
	#define _VIEW_INFO_H_

	#include <QtGui>
	#include "Model/game.h"
	#include "View/view_main.h"

	class View_Info: public QFrame {
		Q_OBJECT
	protected:
		Game *game;
		QWidget *window;
	public:
		View_Info(QWidget *parent);
		void init(Game *_game);
	};

#endif
