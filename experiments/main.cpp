#include <QtCore>
#include "experiment.h"

int main(int argc, char** argv) {

	BOARD board1;

	BOARD board2;
	board2.scell(0, 5, EMPTY);
	board2.scell(3, 6, EMPTY);
	board2.scell(6, 5, EMPTY);
	board2.scell(7, 6, EMPTY);
	board2.scell(1, 0, EMPTY);
	board2.scell(3, 0, EMPTY);
	board2.scell(3, 2, EMPTY);
	board2.scell(7, 2, EMPTY);
	board2.scell(6, 1, BLACK_KING);

	Experiment exp1(board1, WHITE, 5, 5, 0.1, 8, 11, "Experiment 1");
	exp1.run(new Ai_Player_NegaScout(), "NegaScout");
	exp1.run(new Ai_Player_AlphaBeta(), "AlphaBeta");

	Experiment exp2(board2, WHITE, 5, 5, 0.1, 8, 11, "Experiment 2");
	exp2.run(new Ai_Player_NegaScout(), "NegaScout");
	exp2.run(new Ai_Player_AlphaBeta(), "AlphaBeta");

	Experiment exp3(board2, BLACK, 5, 5, 0.1, 8, 11, "Experiment 3");
	exp3.run(new Ai_Player_NegaScout(), "NegaScout");
	exp3.run(new Ai_Player_AlphaBeta(), "AlphaBeta");

	return 0;
}
