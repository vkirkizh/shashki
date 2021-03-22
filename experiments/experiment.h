#ifndef _EXPERIMENT_H_
	#define _EXPERIMENT_H_

	#include <vector>
	#include "Players/ai_player.h"

	typedef std::vector<double> times_array;

	enum READY_STATE {EXP_NOREADY, EXP_READY_COVAR, EXP_READY_MAXEXP};

	class Experiment {
	protected:
		BOARD board;
		COLOR color;
		int minExp, maxExp;
		double Covar;
		int minDepth, maxDepth;
	public:
		Experiment(const BOARD &_board, COLOR _color, int _minExp, int _maxExp, double _Covar, int minDepth, int maxDepth, char *title = "Experiment");
		void run(Ai_Player *player, char *title = "Default");
	protected:
		READY_STATE isReady(const times_array &times, double &M, double &covar);
	};

#endif
