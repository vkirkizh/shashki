#include "View/view_finishgame.h"

View_FinishGame::View_FinishGame(QWidget *parent):QLabel(parent) {
	qDebug() << "View_FinishGame::View_FinishGame(QWidget *parent):QWidget(parent)";

	window = parent;
}

void View_FinishGame::showResult(GAMESTATE res_flag) {
	qDebug() << "View_FinishGame::showResult(GAMESTATE res_flag) -> BEGIN";

	setGeometry(480, 110, 300, 200);
	setFrameStyle(QFrame::Box | QFrame::Plain);
	setLineWidth(3);
	switch (res_flag) {
		case END_WHITE:
			setText("White has won! (1:0)");
		break;
		case END_BLACK:
			setText("Black has won! (0:1)");
		break;
		case END_DRAW:
			setText("Draw! (0:0)");
		break;
	}

	show();

	qDebug() << "View_FinishGame::showResult(GAMESTATE res_flag) -> END";
}
