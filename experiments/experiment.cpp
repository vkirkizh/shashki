#include <iostream>
#include <time.h>
#include <math.h>
#include "experiment.h"

Experiment::Experiment(const BOARD &_board, COLOR _color, int _minExp, int _maxExp, double _Covar, int _minDepth, int _maxDepth, char *title):
	minExp(_minExp), maxExp(_maxExp), Covar(_Covar), minDepth(_minDepth), maxDepth(_maxDepth)
{
	board = _board;
	color = _color;
	qDebug() << "====== " << title << " ======";
	qDebug() << board;
	qDebug() << "    " << (color == WHITE ? "White moves" : "Black moves");
	qDebug() << " -------------------";
};

void Experiment::run(Ai_Player *player, char *title) {
	time_t start_time, end_time;
	std::cout << "=== " << title << " ===" << std::endl;
	player->setColor(color);
	player->randomize(false);
	board.startMove(color);
	for (int n = minDepth; n <= maxDepth; n++) {
		player->setDepth(n);
		times_array times;
		double M = -1.0, covar = -1.0;
		READY_STATE res;
		int k = 0;
		while ((res = isReady(times, M, covar)) == EXP_NOREADY) {
			time(&start_time);
			player->execMove(board);
			time(&end_time);
			times.push_back(difftime(end_time, start_time));
		}
		std::cout << n << " | ";
		switch (res) {
			case EXP_READY_MAXEXP: std::cout << "maxexp"; break;
			case EXP_READY_COVAR:  std::cout << "covar"; break;
		}
		std::cout << " | " << M << " | " << covar << std::endl;
	}
	std::cout << std::endl;
	delete player;
}

READY_STATE Experiment::isReady(const times_array &times, double &M, double &covar) {
	if (times.size() < minExp) return EXP_NOREADY;

	double M2 = 0, D = 0; M = 0;
	for (int i = 0; i < times.size(); i++) {
		M += times[i];
		M2 += pow(times[i], 2);
	}
	M /= (double)times.size();
	M2 /= (double)times.size();
	D = M2 - pow(M, 2);
	covar = sqrt(D)/M;
	if (covar <= Covar) return EXP_READY_COVAR;

	if (times.size() >= maxExp) return EXP_READY_MAXEXP;

	return EXP_NOREADY;
}
