#ifndef _BOARD_H_
	#define _BOARD_H_

	#include <QtCore>

	enum COLOR {
		BLACK = -1,
		NONE  =  0,
		WHITE =  1
	};

	enum FIGURE {
		BLACK_KING = -2,
		BLACK_PAWN = -1,
		EMPTY      =  0,
		WHITE_PAWN =  1,
		WHITE_KING =  2
	};

	inline bool IS_WHITE(FIGURE type) {return type > 0 ? true : false;};
	inline bool IS_WHITE(COLOR type) {return type > 0 ? true : false;};
	inline bool IS_BLACK(FIGURE type) {return type < 0 ? true : false;};
	inline bool IS_BLACK(COLOR type) {return type < 0 ? true : false;};
	inline bool IS_EMPTY(FIGURE type) {return !type ? true : false;};
	inline bool IS_EMPTY(COLOR type) {return !type ? true : false;};
	inline bool IS_DRT(FIGURE type) {return abs(type) == 1 ? true : false;};
	inline bool IS_KNG(FIGURE type) {return abs(type) == 2 ? true : false;};

	COLOR getColor(FIGURE type);

	enum GAMESTATE {
		END_NONE,
		END_WHITE,
		END_BLACK,
		END_DRAW
	};

	class CELL {
		public: int x, y;
		explicit CELL(int _x = 0, int _y = 0): x(_x), y(_y) {};
		friend bool operator== (CELL a, CELL b);
		friend bool operator!= (CELL a, CELL b);
	};

	class MOVE {
		public: CELL from, to;
		MOVE() {};
		MOVE(CELL _from, CELL _to) {from = _from; to = _to;};
		friend bool operator== (MOVE m1, MOVE m2);
		friend bool operator!= (MOVE m1, MOVE m2);
	};

	class CANMOVE {
		public: FIGURE eat;
		public: COLOR king;
		public: CELL eat_c;
		CANMOVE(): eat(EMPTY), king(NONE) {};
	};

	class BOARD {
	public:
		const static unsigned int size = 8;
		const static unsigned int drawMoves = 32;
	protected:
		unsigned int b, w, bk, wk; // numbers of figures and kings
		FIGURE cells[size][size];  // [x][y]; x - col, y - row
		bool ufirst;               // flag, indicating first partial half-move
		bool ueaten;               // flag, indicating eating at last partial half-move
		COLOR utype;               // player type for current half-move
		CELL ublocked;             // blocked for current half-move figure
		unsigned int drawCount, drawFigures;
		bool drawFlag;
	public:
		BOARD();
		friend QDebug operator<< (QDebug qdbg, BOARD &board);
		void startMove(COLOR type);
		GAMESTATE isWin();
		bool scell(int x, int y, FIGURE type);
		bool scell(CELL figure, FIGURE type);
		bool scell(int x1, int y1, int x2, int y2);
		bool scell(CELL figure1, CELL figure2);
		FIGURE gcell(int x, int y);
		FIGURE gcell(CELL figure);
		unsigned int moves(CELL figure, CELL *arr = NULL);
		bool move(MOVE _move);
		bool move(CELL from, CELL to);
		bool move(int x1, int y1, int x2, int y2);
		int first() {return ufirst;}
		int white() {return w;}
		int black() {return b;}
		int whiteKing() {return wk;}
		int blackKing() {return bk;}
		int getCurrentColor() {return utype;}
		int figuresCount() {return w + b;}
		bool canMove();
		bool canMove(MOVE _move, CANMOVE *flags = NULL, COLOR _type = NONE);
		bool canMove(CELL from, CELL to, CANMOVE *flags = NULL, COLOR _type = NONE);
		bool canMove(int x1, int y1, int x2, int y2, CANMOVE *flags = NULL, COLOR _type = NONE);
	protected:
		unsigned int getSquareMoves(CELL figure, int dep, COLOR type = NONE, CELL *res = NULL, CANMOVE *flags = NULL);
		bool canEat(CELL figure);
		bool canEat(int x, int y);
		bool canMove(CELL figure);
};

#endif
