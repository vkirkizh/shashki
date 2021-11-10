#ifndef _VIEW_MAIN_H_
	#define _VIEW_MAIN_H_

	#include <QtGui>
	#include "Model/game.h"

	class View_Main: public QMainWindow {
		Q_OBJECT
	public:
		View_Main();
		~View_Main();
	signals:
		void newGameSignal();
		void quit();
	protected slots:
		void menuNewgame();
		void menuQuit();
	};

#endif
