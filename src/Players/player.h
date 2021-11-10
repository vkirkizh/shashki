#ifndef _PLAYER_H_
	#define _PLAYER_H_

	#include "Model/board.h"

	enum PLAYER_TYPE {HUMAN, AI};

	class Player {
	protected:
		COLOR color;
		MOVE result;
	public:
		Player() {color = NONE;}
		void setColor(COLOR _color) {color = _color;};
		virtual PLAYER_TYPE type() = 0;
		virtual void execMove(BOARD board) = 0;
		MOVE getMove() {return result;}
		virtual void setLevel(int level) {};
		COLOR getColor() {return color;};
	};

#endif
