#include "test_board.h"

void Test_Board::test_moves_func() {
	BOARD board;
	CANMOVE cmFlag;
	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			board.scell(i, j, EMPTY);
		}
	}
	board.scell(2, 5, WHITE_PAWN);
	board.scell(5, 2, WHITE_PAWN);
	board.scell(1, 2, WHITE_KING);
	board.scell(6, 5, WHITE_KING);
	board.scell(1, 4, BLACK_PAWN);
	board.scell(3, 6, BLACK_KING);
	board.scell(5, 4, BLACK_PAWN);
	board.scell(3, 2, BLACK_KING);
	board.scell(3, 0, BLACK_PAWN);
	board.scell(7, 0, BLACK_KING);
	board.scell(5, 6, BLACK_PAWN);

	CELL m[16]; int n;

	board.startMove(WHITE);
	QVERIFY(board.canMove());
	QVERIFY(n = board.moves(CELL(2, 5), m));
	QVERIFY(n == 2);
	QVERIFY(m[0] == CELL(4, 7));
	QVERIFY(m[1] == CELL(0, 3));

	QVERIFY(!board.moves(CELL(5, 2), m));

	QVERIFY(n = board.moves(CELL(1, 2), m));
	QVERIFY(n == 1);
	QVERIFY(m[0] == CELL(6, 7));

	QVERIFY(n = board.moves(CELL(6, 5), m));
	QVERIFY(n == 2);
	QVERIFY(m[0] == CELL(4, 7));
	QVERIFY(m[1] == CELL(4, 3));

	board.startMove(BLACK);
	QVERIFY(board.canMove());
	QVERIFY(!board.moves(CELL(3, 0), m));

	QVERIFY(n = board.moves(CELL(7, 0), m));
	QVERIFY(n == 1);
	QVERIFY(m[0] == CELL(4, 3));

	QVERIFY(!board.moves(CELL(3, 2), m));

	QVERIFY(!board.moves(CELL(1, 4), m));

	QVERIFY(n = board.moves(CELL(5, 4), m));
	QVERIFY(n == 1);
	QVERIFY(m[0] == CELL(7, 6));

	QVERIFY(!board.moves(CELL(3, 6), m));

	QVERIFY(n = board.moves(CELL(5, 6), m));
	QVERIFY(n == 1);
	QVERIFY(m[0] == CELL(7, 4));
}

void Test_Board::test_king_moves() {
	BOARD board;
	CANMOVE cmFlag;
	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			board.scell(i, j, EMPTY);
		}
	}
	board.scell(1, 4, BLACK_PAWN);
	board.scell(2, 5, BLACK_PAWN);
	board.scell(5, 4, BLACK_PAWN);
	board.scell(6, 5, BLACK_PAWN);
	board.scell(1, 6, BLACK_KING);
	board.scell(5, 2, BLACK_KING);
	board.scell(4, 7, WHITE_KING);

	board.startMove(WHITE);
	QVERIFY(board.canMove());
	QVERIFY(!board.canMove(4, 7, 3, 6, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 2, 5, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 1, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 0, 3, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 2, 7, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 6, 7, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 5, 6, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 6, 5, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 4, 5, NULL, WHITE));
	QVERIFY(!board.canMove(4, 7, 4, 6, NULL, WHITE));
	QVERIFY(board.canMove(4, 7, 7, 4, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 5 && cmFlag.king == NONE);
	board.move(4, 7, 7, 4);
	QVERIFY(board.gcell(7, 4) == WHITE_KING);
	QVERIFY(board.gcell(6, 5) == EMPTY);
	QVERIFY(board.gcell(4, 7) == EMPTY);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(7, 4, 4, 1, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 5 && cmFlag.eat_c.y == 2 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(7, 4, 6, 3, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 7, 2, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 6, 5, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 5, 6, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 4, 7, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 3, 0, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 5, 0, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(7, 4, 4, 3, NULL, WHITE));
	board.move(7, 4, 4, 1);
	QVERIFY(board.gcell(4, 1) == WHITE_KING);
	QVERIFY(board.gcell(7, 4) == EMPTY);
	QVERIFY(board.gcell(5, 2) == EMPTY);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(4, 1, 0, 5, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 1 && cmFlag.eat_c.y == 4 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(4, 1, 5, 0, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 3, 0, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 7, 0, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 1, 0, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 4, 1, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 6, 3, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 7, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 7, 6, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 3, 2, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 2, 3, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 1, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 0, 3, NULL, WHITE));
	board.move(4, 1, 0, 5);
	QVERIFY(board.gcell(0, 5) == WHITE_KING);
	QVERIFY(board.gcell(4, 1) == EMPTY);
	QVERIFY(board.gcell(1, 4) == EMPTY);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(0, 5, 2, 7, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 1 && cmFlag.eat_c.y == 6 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(0, 5, 1, 6, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 0, 7, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 3, 6, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 4, 5, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 2, 5, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 1, 4, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 0, 3, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 2, 3, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 3, 2, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 4, 1, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 5, 0, NULL, WHITE));
	board.move(0, 5, 2, 7);
	QVERIFY(board.gcell(2, 7) == WHITE_KING);
	QVERIFY(board.gcell(0, 5) == EMPTY);
	QVERIFY(board.gcell(1, 6) == EMPTY);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(2, 7, 6, 3, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 5 && cmFlag.eat_c.y == 4 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(2, 7, 1, 6, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 0, 5, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 0, 7, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 4, 7, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 3, 6, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 4, 5, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 5, 4, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 7, 2, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 7, 4, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 7, 0, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 6, 1, NULL, WHITE));
	QVERIFY(!board.canMove(2, 7, 4, 3, NULL, WHITE));
	board.move(2, 7, 6, 3);
	QVERIFY(board.gcell(6, 3) == WHITE_KING);
	QVERIFY(board.gcell(2, 7) == EMPTY);
	QVERIFY(board.gcell(5, 4) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());
}

void Test_Board::test_difficult_moves() {
	BOARD board;
	CANMOVE cmFlag;
	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			board.scell(i, j, EMPTY);
		}
	}
	board.scell(4, 1, BLACK_PAWN);
	board.scell(6, 1, BLACK_PAWN);
	board.scell(4, 3, BLACK_KING);
	board.scell(6, 3, BLACK_KING);
	board.scell(6, 5, BLACK_PAWN);
	board.scell(2, 3, BLACK_PAWN);
	board.scell(2, 5, BLACK_PAWN);
	board.scell(4, 5, BLACK_PAWN);
	board.scell(5, 6, BLACK_PAWN);
	board.scell(1, 6, WHITE_PAWN);

	board.startMove(WHITE);
	QVERIFY(board.canMove());
	QVERIFY(!board.canMove(1, 6, 2, 5, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 0, 5, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 2, 7, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 0, 7, NULL, WHITE));
	QVERIFY(board.canMove(1, 6, 3, 4, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 2 && cmFlag.eat_c.y == 5 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(1, 6, 1, 4, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 3, 6, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 1, 2, NULL, WHITE));
	QVERIFY(!board.canMove(1, 6, 6, 7, NULL, WHITE));
	board.move(1, 6, 3, 4);
	QVERIFY(board.gcell(3, 4) == WHITE_PAWN);
	QVERIFY(board.gcell(1, 6) == EMPTY);
	QVERIFY(board.gcell(2, 5) == EMPTY);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(3, 4, 1, 2, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 2 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
	QVERIFY(board.canMove(3, 4, 5, 2, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 4 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(3, 4, 0, 1, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 2, 5, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 1, 6, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 4, 5, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 5, 6, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 6, 7, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 7, 4, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 7, 0, NULL, WHITE));
	QVERIFY(!board.canMove(3, 4, 3, 0, NULL, WHITE));
	board.move(3, 4, 5, 2);
	QVERIFY(board.gcell(5, 2) == WHITE_PAWN);
	QVERIFY(board.gcell(3, 4) == EMPTY);
	QVERIFY(board.gcell(4, 3) == EMPTY);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(5, 2, 3, 0, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 4 && cmFlag.eat_c.y == 1 && cmFlag.king == WHITE);
	QVERIFY(board.canMove(5, 2, 7, 0, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 1 && cmFlag.king == WHITE);
	QVERIFY(board.canMove(5, 2, 7, 4, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(5, 2, 4, 3, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 3, 4, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 4, 1, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 6, 3, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 6, 1, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 5, 0, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 7, 2, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 2, 5, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 1, 6, NULL, WHITE));
	QVERIFY(!board.canMove(5, 2, 0, 7, NULL, WHITE));
	board.move(5, 2, 3, 0);
	QVERIFY(board.gcell(3, 0) == WHITE_KING);
	QVERIFY(board.gcell(5, 2) == EMPTY);
	QVERIFY(board.gcell(4, 1) == EMPTY);
	QVERIFY(!board.canMove(3, 0, 2, 1, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 1, 2, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 0, 3, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 4, 1, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 6, 3, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 3, 1, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 7, 0, NULL, WHITE));
	QVERIFY(!board.canMove(3, 0, 6, 5, NULL, WHITE));
	QVERIFY(board.canMove(3, 0, 7, 4, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
	board.move(3, 0, 7, 4);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());
}

void Test_Board::test_simple_moves() {
	BOARD board;
	CANMOVE cmFlag;

	board.startMove(WHITE);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(0, 5, 1, 4, NULL, WHITE));
	QVERIFY(board.canMove(2, 5, 1, 4, NULL, WHITE));
	QVERIFY(board.canMove(2, 5, 3, 4, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 0, 5, NULL, WHITE));
	QVERIFY(!board.canMove(1, 2, 3, 4, NULL, WHITE));
	QVERIFY(!board.canMove(1, 2, 2, 3, NULL, WHITE));
	QVERIFY(!board.canMove(1, 2, 0, 3, NULL, WHITE));
	QVERIFY(!board.canMove(3, 2, 2, 3, NULL, WHITE));
	QVERIFY(!board.canMove(3, 2, 4, 3, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 0, 4, NULL, WHITE));
	QVERIFY(!board.canMove(0, 5, 1, 5, NULL, WHITE));
	QVERIFY(!board.canMove(0, 1, 0, 2, NULL, WHITE));
	QVERIFY(!board.canMove(0, 1, 1, 1, NULL, WHITE));
	board.move(6, 5, 5, 4);
	QVERIFY(board.gcell(5, 4) == WHITE_PAWN);
	QVERIFY(board.gcell(6, 5) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());

	board.startMove(BLACK);
	QVERIFY(board.canMove());
	QVERIFY(!board.canMove(1, 2, 3, 4, NULL, BLACK));
	QVERIFY(board.canMove(1, 2, 0, 3, NULL, BLACK));
	QVERIFY(board.canMove(1, 2, 2, 3, NULL, BLACK));
	QVERIFY(board.canMove(3, 2, 2, 3, NULL, BLACK));
	QVERIFY(board.canMove(3, 2, 4, 3, NULL, BLACK));
	QVERIFY(!board.canMove(5, 4, 6, 3, NULL, BLACK));
	QVERIFY(!board.canMove(5, 4, 4, 3, NULL, BLACK));
	QVERIFY(!board.canMove(2, 5, 1, 4, NULL, BLACK));
	QVERIFY(!board.canMove(2, 5, 3, 4, NULL, BLACK));
	QVERIFY(!board.canMove(5, 6, 6, 5, NULL, BLACK));
	QVERIFY(!board.canMove(5, 6, 7, 4, NULL, BLACK));
	QVERIFY(board.canMove(5, 2, 4, 3, NULL, BLACK));
	QVERIFY(board.canMove(5, 2, 6, 3, NULL, BLACK));
	QVERIFY(!board.canMove(5, 2, 3, 4, NULL, BLACK));
	QVERIFY(!board.canMove(5, 2, 7, 4, NULL, BLACK));
	board.move(5, 2, 4, 3);
	QVERIFY(board.gcell(4, 3) == BLACK_PAWN);
	QVERIFY(board.gcell(5, 2) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());

	board.startMove(WHITE);
	QVERIFY(board.canMove(5, 4, 6, 3, NULL, WHITE));
	QVERIFY(board.canMove(2, 5, 1, 4, NULL, WHITE));
	QVERIFY(!board.canMove(5, 4, 4, 3, NULL, WHITE));
	QVERIFY(!board.canMove(5, 4, 6, 5, NULL, WHITE));
	QVERIFY(!board.canMove(5, 4, 4, 5, NULL, WHITE));
	QVERIFY(!board.canMove(4, 3, 3, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 3, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(7, 2, 6, 3, NULL, WHITE));
	QVERIFY(!board.canMove(4, 3, 5, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 3, 6, 5, NULL, WHITE));
	QVERIFY(board.canMove());
	board.move(5, 4, 6, 3);
	QVERIFY(board.gcell(6, 3) == WHITE_PAWN);
	QVERIFY(board.gcell(5, 4) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());

	board.startMove(BLACK);
	QVERIFY(board.canMove(7, 2, 5, 4, &cmFlag, BLACK));
	QVERIFY(cmFlag.eat == WHITE_PAWN && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(7, 2, 6, 3, NULL, BLACK));
	QVERIFY(!board.canMove(7, 2, 7, 4, NULL, BLACK));
	QVERIFY(!board.canMove(7, 2, 5, 2, NULL, BLACK));
	QVERIFY(!board.canMove(5, 2, 6, 3, NULL, BLACK));
	QVERIFY(!board.canMove(5, 2, 4, 3, NULL, BLACK));
	QVERIFY(!board.canMove(3, 2, 4, 3, NULL, BLACK));
	QVERIFY(!board.canMove(3, 2, 5, 4, NULL, BLACK));
	QVERIFY(!board.canMove(3, 2, 1, 4, NULL, BLACK));
	QVERIFY(!board.canMove(1, 2, 6, 3, NULL, BLACK));
	QVERIFY(!board.canMove(1, 2, 1, 3, NULL, BLACK));
	QVERIFY(board.canMove());
	board.move(7, 2, 5, 4);
	QVERIFY(board.gcell(5, 4) == BLACK_PAWN);
	QVERIFY(board.gcell(7, 2) == EMPTY);
	QVERIFY(board.gcell(6, 3) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());

	board.startMove(WHITE);
	QVERIFY(board.canMove());
	QVERIFY(board.canMove(4, 5, 6, 3, &cmFlag, WHITE));
	QVERIFY(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 5 && cmFlag.eat_c.y == 4 && cmFlag.king == NONE);
	QVERIFY(!board.canMove(4, 5, 5, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 3, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 7, 2, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 2, 3, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 7, 4, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 6, 5, NULL, WHITE));
	QVERIFY(!board.canMove(4, 5, 1, 2, NULL, WHITE));
	QVERIFY(!board.canMove(6, 1, 7, 2, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 5, 2, NULL, WHITE));
	QVERIFY(!board.canMove(4, 1, 6, 3, NULL, WHITE));
	board.move(4, 5, 6, 3);
	QVERIFY(board.gcell(6, 3) == WHITE_PAWN);
	QVERIFY(board.gcell(4, 5) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());

	board.startMove(BLACK);
	QVERIFY(board.canMove(1, 2, 0, 3, NULL, BLACK));
	QVERIFY(board.canMove(1, 2, 2, 3, NULL, BLACK));
	QVERIFY(board.canMove(6, 1, 5, 2, NULL, BLACK));
	QVERIFY(board.canMove(6, 1, 7, 2, NULL, BLACK));
	QVERIFY(!board.canMove(7, 0, 5, 2, NULL, BLACK));
	QVERIFY(!board.canMove(5, 0, 6, 1, NULL, BLACK));
	QVERIFY(!board.canMove(5, 0, 7, 2, NULL, BLACK));
	QVERIFY(board.canMove(3, 2, 2, 3, NULL, BLACK));
	QVERIFY(!board.canMove(3, 2, 4, 3, NULL, BLACK));
	QVERIFY(!board.canMove(6, 3, 5, 2, NULL, BLACK));
	QVERIFY(!board.canMove(6, 3, 7, 2, NULL, BLACK));
	QVERIFY(!board.canMove(6, 3, 5, 4, NULL, BLACK));
	QVERIFY(!board.canMove(6, 3, 7, 4, NULL, BLACK));
	QVERIFY(!board.canMove(3, 6, 4, 3, NULL, BLACK));
	board.move(1, 2, 0, 3);
	QVERIFY(board.gcell(0, 3) == BLACK_PAWN);
	QVERIFY(board.gcell(1, 2) == EMPTY);
	QVERIFY(!board.canMove());
	QVERIFY(!board.isWin());
}

void Test_Board::test_set_get_cell() {
	BOARD board;
	QVERIFY(board.gcell(-1, -1) == EMPTY);
	QVERIFY(board.gcell(board.size, board.size) == EMPTY);

	QVERIFY(board.gcell(0, 0) == EMPTY);
	QVERIFY(board.gcell(7, 7) == EMPTY);

	QVERIFY(board.gcell(7, 0) == BLACK_PAWN);
	QVERIFY(board.gcell(7, 2) == BLACK_PAWN);
	QVERIFY(board.gcell(0, 7) == WHITE_PAWN);
	QVERIFY(board.gcell(0, 5) == WHITE_PAWN);

	QVERIFY(!board.scell(-1, -1, EMPTY));
	QVERIFY(!board.scell(board.size, board.size, EMPTY));

	QVERIFY(board.scell(1, 0, EMPTY));
	QVERIFY(board.gcell(1, 0) == EMPTY);
	QVERIFY(board.scell(2, 7, EMPTY));
	QVERIFY(board.gcell(2, 7) == EMPTY);

	QVERIFY(board.scell(1, 0, WHITE_PAWN));
	QVERIFY(board.gcell(1, 0) == WHITE_PAWN);
	QVERIFY(board.scell(2, 7, BLACK_PAWN));
	QVERIFY(board.gcell(2, 7) == BLACK_PAWN);
}

void Test_Board::test_getColor() {
	QVERIFY(getColor(BLACK_KING) == BLACK);
	QVERIFY(getColor(BLACK_PAWN) == BLACK);
	QVERIFY(getColor(EMPTY) == NONE);
	QVERIFY(getColor(WHITE_PAWN) == WHITE);
	QVERIFY(getColor(WHITE_KING) == WHITE);
}
