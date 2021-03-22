#include "Model/board.h"

COLOR getColor(FIGURE type) {
	switch (type) {
		case WHITE_PAWN:
		case WHITE_KING:
			return WHITE;
		case BLACK_PAWN:
		case BLACK_KING:
			return BLACK;
		default:
			return NONE;
	}
}

BOARD::BOARD() {
	b = w = bk = wk = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			scell(i, j, EMPTY);
	for (int i = 0; i < size; i += 2) {
		scell(i+1, 0, BLACK_PAWN);
		scell(i,   1, BLACK_PAWN);
		scell(i+1, 2, BLACK_PAWN);
		b += 3;
		scell(i,   5, WHITE_PAWN);
		scell(i+1, 6, WHITE_PAWN);
		scell(i,   7, WHITE_PAWN);
		w += 3;
	}
	drawCount = 0;
	drawFlag = false;
	drawFigures = figuresCount();
}

bool BOARD::scell(int x, int y, FIGURE type) {
	if (x < 0 || y < 0 || x >= size || y >= size) {
		return false;
	}
	cells[x][y] = type;
	return true;
}
bool BOARD::scell(CELL figure, FIGURE type) {return scell(figure.x, figure.y, type);}
bool BOARD::scell(int x1, int y1, int x2, int y2) {return scell(x1, y1, gcell(x2, y2));}
bool BOARD::scell(CELL figure1, CELL figure2) {return scell(figure1, gcell(figure2));}

FIGURE BOARD::gcell(int x, int y) {
	if (x < 0 || y < 0 || x >= size || y >= size) {
		return EMPTY;
	}
	return cells[x][y];
}
FIGURE BOARD::gcell(CELL figure) {return gcell(figure.x, figure.y);}

bool operator== (CELL a, CELL b) {
	return (a.x == b.x && a.y == b.y);
}
bool operator!= (CELL a, CELL b) {
	return !(a == b);
}

bool operator== (MOVE m1, MOVE m2) {
	return (m1.from == m2.from && m1.to == m2.to);
}
bool operator!= (MOVE m1, MOVE m2) {
	return !(m1 == m2);
}

void BOARD::startMove(COLOR type) {
	utype = type;
	ufirst = true;
	ueaten = false;
}

GAMESTATE BOARD::isWin() {
	int tb = 0, tw = 0;
	if (!b) return END_WHITE;
	if (!w) return END_BLACK;
	if (drawCount >= drawMoves) return END_DRAW;
	drawCount++;
	if (drawFigures != figuresCount()) drawCount = 0;
	drawFigures = figuresCount();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 1; k < size; k++) {
				if (getSquareMoves(CELL(i, j), k)) {
					if (IS_WHITE(gcell(i, j))) tw++;
					if (IS_BLACK(gcell(i, j))) tb++;
				}
			}
		}
	}
	if ( tw && !tb) return END_WHITE;
	if (!tw &&  tb) return END_BLACK;
	if (!tw && !tb) return END_DRAW;
	return END_NONE;
}

bool BOARD::canMove(CELL from, CELL to, CANMOVE *flags, COLOR _type) {
	if (from.x < 0 || from.y < 0 || from.x >= size || from.y >= size) return false;
	if (to.x < 0   || to.y < 0   || to.x >= size   || to.y >= size)   return false;
	FIGURE type = gcell(from);
	if (!type) return false;
	if (_type && getColor(type) != _type) return false;
	if (gcell(to)) return false;
	if (flags != NULL && IS_DRT(type)) {
		if (IS_WHITE(type) && to.y == 0) flags->king = WHITE;
		else if (IS_BLACK(type) && to.y == size - 1) flags->king = BLACK;
		else flags->king = NONE;
	}
	if (IS_DRT(type)) {
		FIGURE eaten;
		int x, y;
		if (IS_WHITE(type)) {
			if (0
				|| (((from.x - to.x) ==  2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x-1, y = from.y-1)) < 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x+1, y = from.y-1)) < 0)
				|| (((from.x - to.x) ==  2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x-1, y = from.y+1)) < 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x+1, y = from.y+1)) < 0)
			) {
				if (flags != NULL) {flags->eat = eaten; flags->eat_c = CELL(x, y);}
				return true;
			}
			if (abs(to.x - from.x) == 1 && (from.y - to.y) == 1) {
				if (from.x - 2 > 0 && from.y - 2 > 0 && gcell(from.x-1, from.y-1) < 0 && gcell(from.x-2, from.y-2) == 0) return false;
				if (from.x + 2 < size && from.y - 2 > 0 && gcell(from.x+1, from.y-1) < 0 && gcell(from.x+2, from.y-2) == 0) return false;
				return true;
			}
		}
		if (IS_BLACK(type)) {
			if (0
				|| (((from.x - to.x) ==  2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x-1, y = from.y-1)) > 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) ==  2) && (eaten = gcell(x = from.x+1, y = from.y-1)) > 0)
				|| (((from.x - to.x) ==  2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x-1, y = from.y+1)) > 0)
				|| (((from.x - to.x) == -2 && (from.y - to.y) == -2) && (eaten = gcell(x = from.x+1, y = from.y+1)) > 0)
			) {
				if (flags != NULL) {flags->eat = eaten; flags->eat_c = CELL(x, y);}
				return true;
			}
			if (abs(to.x - from.x) == 1 && (to.y - from.y) == 1) {
				if (from.x - 2 > 0 && from.y + 2 < 0 && gcell(from.x-1, from.y+1) > 0 && gcell(from.x-2, from.y+2) == 0) return false;
				if (from.x + 2 < size && from.y + 2 < 0 && gcell(from.x+1, from.y+1) > 0 && gcell(from.x+2, from.y+2) == 0) return false;
				return true;
			}
		}
	}
	if (IS_KNG(type)) {
		bool can_eat = false;

		if (abs(to.x - from.x) != abs(to.y - from.y)) return false;

		for (int i = from.x - 1, j = from.y - 1, met_enemy = 0; i >= 0 && j >= 0; i--, j--) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break;
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true;
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i+1, j+1); flags->eat_c = CELL(i+1, j+1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		for (int i = from.x + 1, j = from.y - 1, met_enemy = 0; i < size && j >= 0; i++, j--) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break;
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true;
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i-1, j+1); flags->eat_c = CELL(i-1, j+1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		for (int i = from.x - 1, j = from.y + 1, met_enemy = 0; i >= 0 && j < size; i--, j++) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break;
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true;
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i+1, j-1); flags->eat_c = CELL(i+1, j-1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		for (int i = from.x + 1, j = from.y + 1, met_enemy = 0; i < size && j < size; i++, j++) {
			if ((IS_WHITE(type) && IS_WHITE(gcell(i, j))) || (IS_BLACK(type) && IS_BLACK(gcell(i, j)))) break;
			if (met_enemy) {
				if (IS_EMPTY(gcell(i, j))) {
					can_eat = true;
					if (i == to.x && j == to.y) {
						if (flags != NULL) {flags->eat = gcell(i-1, j-1); flags->eat_c = CELL(i-1, j-1);}
						return true;
					}
				}
				break;
			}
			if ((IS_WHITE(type) && IS_BLACK(gcell(i, j))) || (IS_BLACK(type) && IS_WHITE(gcell(i, j)))) met_enemy++;
		}
		if (can_eat) return false;
		if (to.x < from.x && to.y < from.y) {
			for (int i = from.x - 1, j = from.y - 1; i >= to.x && j >= to.y; i--, j--) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		if (to.x > from.x && to.y < from.y) {
			for (int i = from.x + 1, j = from.y - 1; i <= to.x && j >= to.y; i++, j--) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		if (to.x < from.x && to.y > from.y) {
			for (int i = from.x - 1, j = from.y + 1; i >= to.x && j <= to.y; i--, j++) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}
		if (to.x > from.x && to.y > from.y) {
			for (int i = from.x + 1, j = from.y + 1; i <= to.x && j <= to.y; i++, j++) {
				if (!IS_EMPTY(gcell(i, j))) return false;
			}
		}

		return true;
	}

	return false;
}
bool BOARD::canMove(MOVE _move, CANMOVE *flags, COLOR _type) {return canMove(_move.from, _move.to, flags, _type);}
bool BOARD::canMove(int x1, int y1, int x2, int y2, CANMOVE *flags, COLOR _type) {return canMove(CELL(x1, y1), CELL(x2, y2), flags, _type);};

unsigned int BOARD::getSquareMoves(CELL figure, int dep, COLOR type, CELL *res, CANMOVE *flags) {
	unsigned int k = 0;
	if (dep <= 0) return 0;
	if (canMove(figure, CELL(figure.x+dep, figure.y+dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x+dep, figure.y+dep); else k++;
	if (canMove(figure, CELL(figure.x-dep, figure.y+dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x-dep, figure.y+dep); else k++;
	if (canMove(figure, CELL(figure.x+dep, figure.y-dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x+dep, figure.y-dep); else k++;
	if (canMove(figure, CELL(figure.x-dep, figure.y-dep), flags, type)) if (res != NULL) res[k++] = CELL(figure.x-dep, figure.y-dep); else k++;
	return k;
}

bool BOARD::canEat(CELL figure) {
	FIGURE type = gcell(figure);
	if (IS_DRT(type)) {
		return (getSquareMoves(figure, 2, getColor(type))) ? true : false;
	}
	if (IS_KNG(type)) {
		CANMOVE flags;
		for (int k = 2; k <= size; k++) {
			getSquareMoves(figure, k, getColor(type), NULL, &flags);
			if (flags.eat) return true;
		}
		return false;
	}

	return false;
}
bool BOARD::canEat(int x, int y) {return canEat(CELL(x, y));}

bool BOARD::canMove(CELL figure) {
	if (ufirst) {
		bool flag = false;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (getColor(gcell(i, j)) == utype && canEat(CELL(i, j))) {
					flag = true;
					if (i == figure.x && j == figure.y) return true;
				}
			}
		}
		return !flag;
	}
	else {
		return (!(figure.x == ublocked.x && figure.y == ublocked.y && ueaten)) ? false : true;
	}

	return false;
}

bool BOARD::canMove() {
	if (ufirst) return true;
	return moves(ublocked) ? true : false;
}

unsigned int BOARD::moves(CELL figure, CELL *res) {
	unsigned int k = 0;
	FIGURE type = gcell(figure);
	if (!canMove(figure)) return 0;
	if (IS_DRT(type)) {
		k += getSquareMoves(figure, 2, utype, res);
		if (ufirst && !k) k += getSquareMoves(figure, 1, utype, res);
	}
	if (IS_KNG(type)) {
		CANMOVE flags;
		for (int q = 2; q <= size; q++) {
			if (canMove(figure, CELL(figure.x+q, figure.y+q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y+q); else k++;
			if (canMove(figure, CELL(figure.x-q, figure.y+q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y+q); else k++;
			if (canMove(figure, CELL(figure.x+q, figure.y-q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y-q); else k++;
			if (canMove(figure, CELL(figure.x-q, figure.y-q), &flags, utype))
				if (flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y-q); else k++;
		}
		if (ufirst && !k) {
			for (int q = 1; q <= size; q++) {
				if (canMove(figure, CELL(figure.x+q, figure.y+q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y+q); else k++;
				if (canMove(figure, CELL(figure.x-q, figure.y+q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y+q); else k++;
				if (canMove(figure, CELL(figure.x+q, figure.y-q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x+q, figure.y-q); else k++;
				if (canMove(figure, CELL(figure.x-q, figure.y-q), &flags, utype))
					if (!flags.eat) if (res != NULL) res[k++] = CELL(figure.x-q, figure.y-q); else k++;
			}
		}
	}
	return k;
}

bool BOARD::move(CELL from, CELL to) {
	CANMOVE flags;
	if (!canMove(from, to, &flags, utype)) return false;
	if (ufirst) {
		if (!canMove(from)) return false;
		if (canEat(from) && !flags.eat) return false;
	}
	if (!ufirst) {
		if (!canMove(from)) return false;
		if (!canEat(from)) return false;
	}
	scell(to, from);
	scell(from, EMPTY);
	ublocked = to;
	ufirst = false;
	if (flags.eat) {
		scell(flags.eat_c, EMPTY);
		if (IS_WHITE(flags.eat)) {
			if (IS_KNG(flags.eat)) wk--;
			w--;
		}
		if (IS_BLACK(flags.eat)) {
			if (IS_KNG(flags.eat)) bk--;
			b--;
		}
		ueaten = true;
	}
	if (flags.king && IS_DRT(gcell(to))) {
		if (IS_WHITE(flags.king)) {
			scell(to, WHITE_KING);
			wk++;
		}
		if (IS_BLACK(flags.king)) {
			scell(to, BLACK_KING);
			bk++;
		}
	}
	return true;
}
bool BOARD::move(MOVE _move) {return move(_move.from, _move.to);}
bool BOARD::move(int x1, int y1, int x2, int y2) {return move(CELL(x1, y1), CELL(x2, y2));};

QDebug operator<< (QDebug qdbg, BOARD &board) {
	qdbg << " ------ BOARD ------\n";
	qdbg << "    0 1 2 3 4 5 6 7 \n\n";
	for (int y = 0; y < board.size; y++) {
		qdbg << y << " ";
		for (int x = 0; x < board.size; x++) {
			if (board.cells[x][y] == WHITE_PAWN)
				qdbg << "x";
			else if (board.cells[x][y] == BLACK_PAWN)
				qdbg << "o";
			else if (board.cells[x][y] == WHITE_KING)
				qdbg << "W";
			else if (board.cells[x][y] == BLACK_KING)
				qdbg << "B";
			else
				qdbg << " ";
		}
		qdbg << "\n";
	}
	qdbg << "-------------------";
	return qdbg;
}
