#ifndef _AI_H_
	#define _AI_H_

	#include <vector>
	#include <pthread.h>
	#include <string.h>
	#include "Players/player.h"

	enum AI_PLAYER_LEVEL {LVL_L, LVL_M, LVL_D};

	class CHOOSEN_MOVE {
	public:
		CELL from, to;
		double mark;
		CHOOSEN_MOVE() {mark = 0.0;};
		CHOOSEN_MOVE(CELL _from, CELL _to, double _mark = 0.0) {
			from = _from;
			to = _to;
			mark = _mark;
		};
	};

	typedef std::vector<CHOOSEN_MOVE> CHOOSEN_MOVE_ARRAY;

	void *ai_plr_first_choose(void *ptr);

	class Ai_Player: public Player {
	protected:
		const static int MINMAX_END = 2000000;
		unsigned int max_step;
		virtual double srf(BOARD board);
		unsigned int thr_num;
		bool rndFlag;
		bool timeCtr;
	public:
		Ai_Player(AI_PLAYER_LEVEL level = LVL_M) {
			setLevel(level);
			thr_num = 1;
			srand(time(0));
			rndFlag = true;
		}
		virtual PLAYER_TYPE type() {return AI;};
		virtual void execMove(BOARD board);
		void setLevel(AI_PLAYER_LEVEL level) {
			timeCtr = true;
			switch (level) {
				case LVL_L:
					max_step = 8;
				break;
				case LVL_M:
					max_step = 9;
				break;
				case LVL_D:
					max_step = 10;
				break;
			}
		};
		void setDepth(int depth) {
			timeCtr = false;
			max_step = depth;
		};
		void setThrNum(int num) {
			thr_num = num;
		};
		int getLevel() {return max_step;};
		int getThrNum() {return thr_num;};
		void randomize(bool var) {rndFlag = var;}
		static Player *createAiPlayer(char *str, AI_PLAYER_LEVEL level);
		static Player *createAiPlayer(char *str, int depth);
	protected:
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true, time_t endTime = -1);
		int getTimeForMove();
		friend void *ai_plr_first_choose(void *ptr);
	};

	class Ai_Player_NegaScout: public Ai_Player {
	public:
		Ai_Player_NegaScout(AI_PLAYER_LEVEL level = LVL_M): Ai_Player(level) {}
	};

	class Ai_Player_AlphaBeta: public Ai_Player {
	public:
		Ai_Player_AlphaBeta(AI_PLAYER_LEVEL level = LVL_M): Ai_Player(level) {}
		virtual double choose(BOARD board, COLOR _color, int step = 0, double alpha = -MINMAX_END, double beta = MINMAX_END, bool smflag = true, time_t endTime = -1);
	};

	struct MOVES_SYNC {
	public:
		Ai_Player *plr;
		BOARD *board;
		int next_move_num;
		CHOOSEN_MOVE_ARRAY *moves_queue;
		pthread_mutex_t *queue_mutex;
		double alpha, beta;
		pthread_mutex_t *mark_mutex;
		time_t endTime;
	};

#endif
