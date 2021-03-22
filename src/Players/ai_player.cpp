#include "Players/ai_player.h"

int Ai_Player::getTimeForMove() {
	return 6;
}

void Ai_Player::execMove(BOARD board) {
	time_t endTime = time(0) + getTimeForMove();

	CHOOSEN_MOVE_ARRAY moves_queue;
	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			CELL current_from(i, j), current_moves[16];
			int current_moves_count = board.moves(current_from, current_moves);
			for (int k = 0; k < current_moves_count; k++) {
				CHOOSEN_MOVE current_move(current_from, current_moves[k]);
				moves_queue.push_back(current_move);
			}
		}
	}

	MOVES_SYNC sync_obj, *sync = &sync_obj;
	pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t mark_mutex = PTHREAD_MUTEX_INITIALIZER;
	sync->plr = this;
	sync->board = &board;
	sync->next_move_num = 0;
	sync->moves_queue = &moves_queue;
	sync->queue_mutex = &queue_mutex;
	sync->alpha = -MINMAX_END;
	sync->beta = MINMAX_END;
	sync->mark_mutex = &mark_mutex;
	sync->endTime = endTime;

	std::vector<pthread_t> threads(thr_num);

	for (int i = 0; i < thr_num; i++) {
		if (pthread_create(&threads[i], NULL, &ai_plr_first_choose, (void*)sync)) exit(1);
	}

	for (int i = 0; i < thr_num; i++) {
		pthread_join(threads[i], NULL);
	}

	double score = -MINMAX_END;
	std::vector<CHOOSEN_MOVE> best_moves;
	//qDebug() << "--------------------------- " << thr_num << " ------";
	for (int i = 0; i < moves_queue.size(); i++) {
		//qDebug() << i+1 << ") " << moves_queue[i].from.x+1 << "," << moves_queue[i].from.y+1 << " -> "
		//		 << moves_queue[i].to.x+1 << "," << moves_queue[i].to.y+1 << " || " << moves_queue[i].mark;
		if (moves_queue[i].mark >= score) {
			score = moves_queue[i].mark;
		}
	}
	//qDebug() << "best score: " << score;
	for (int i = 0; i < moves_queue.size(); i++) {
		if (moves_queue[i].mark == score) {
			best_moves.push_back(moves_queue[i]);
		}
	}
	int index = 0;
	if (rndFlag) index = rand() % best_moves.size();
	result.from = best_moves[index].from;
	result.to = best_moves[index].to;
	//qDebug() << "result [" << index+1 << "/" << best_moves.size() << "]: " << result.from.x+1 << "," << result.from.y+1 << " -> "
	//					<< result.to.x+1 << "," << result.to.y+1 << " || " << score;
}

void *ai_plr_first_choose(void *ptr) {
	MOVES_SYNC *sync = (MOVES_SYNC*)ptr;

	bool moves_exist = true;
	while (moves_exist) {
		CHOOSEN_MOVE *move = 0;

		pthread_mutex_lock(sync->queue_mutex);
		if (sync->next_move_num != sync->moves_queue->size()) {
			move = &((*(sync->moves_queue))[sync->next_move_num]);
			++sync->next_move_num;
		} else {
			moves_exist = false;
		}
		pthread_mutex_unlock(sync->queue_mutex);

		if (move) {
			BOARD board_copy = *(sync->board);
			board_copy.startMove(sync->plr->color);
			board_copy.move(move->from, move->to);

			if (board_copy.moves(move->to)) {
				move->mark = sync->plr->choose(board_copy, sync->plr->color, 0, sync->alpha, sync->beta, false, sync->endTime);
			}
			else {
				move->mark = -sync->plr->choose(board_copy, sync->plr->color == WHITE ? BLACK : WHITE, 1, -sync->beta, -sync->alpha, true, sync->endTime);
			}

			/*{
				pthread_mutex_lock(sync->mark_mutex);
				if (move->mark > sync->alpha) {
					sync->alpha = move->mark;
				}
				if (move->mark < sync->beta) {
					sync->beta = move->mark;
				}
				pthread_mutex_unlock(sync->mark_mutex);
			}*/
		}
	}
}

double Ai_Player::choose(BOARD board, COLOR cColor, int step, double alpha, double beta, bool smflag, time_t endTime) {
	bool first = true;
	if (timeCtr && time(0) >= endTime) {
		qDebug() << "time control -> broken move / " << endTime << "";
		return srf(board);
	}
	if (step < max_step) {
		double tmp = -MINMAX_END;
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				int m;
				CELL d(i, j), arr[16];
				if (smflag) board.startMove(cColor);
				m = board.moves(d, arr);
				for (int k = 0; k < m; k++) {
					BOARD board_copy = board;
					board_copy.move(d, arr[k]);
					if (first) {
						if (board_copy.moves(arr[k])) {
							tmp = choose(board_copy, cColor, step, alpha, beta, false, endTime);
						}
						else {
							tmp = -choose(board_copy, cColor == WHITE ? BLACK : WHITE, step + 1, -beta, -alpha, true, endTime);
						}
						first = false;
						if (tmp > alpha) alpha = tmp;
					}
					else {
						if (board_copy.moves(arr[k])) {
							tmp = choose(board_copy, cColor, step, alpha, alpha+1, false, endTime);
							if (tmp > alpha && tmp < beta) {
								tmp = choose(board_copy, cColor, step, tmp, beta, false, endTime);
							}
						}
						else {
							tmp = -choose(board_copy, cColor == WHITE ? BLACK : WHITE, step + 1, -(alpha+1), -alpha, true, endTime);
							if (tmp > alpha && tmp < beta) {
								tmp = -choose(board_copy, cColor == WHITE ? BLACK : WHITE, step + 1, -beta, -tmp, true, endTime);
							}
						}
					}

					if (tmp > alpha) alpha = tmp;
					if (alpha >= beta) return alpha;
				}
			}
		}
		return alpha;
	}
	else {
		return srf(board);
	}

	return 0.0;
}

double Ai_Player_AlphaBeta::choose(BOARD board, COLOR cColor, int step, double alpha, double beta, bool smflag, time_t endTime) {
	if (timeCtr && time(0) >= endTime) {
		qDebug() << "time control -> broken move / " << endTime << "";
		return srf(board);
	}
	if (step < max_step) {
		double score = -MINMAX_END;
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				int m;
				CELL d(i, j), arr[16];
				if (smflag) board.startMove(cColor);
				m = board.moves(d, arr);
				for (int k = 0; k < m; k++) {
					double s;
					BOARD board_copy = board;
					board_copy.move(d, arr[k]);
					if (board_copy.moves(arr[k])) {
						s = choose(board_copy, cColor, step, alpha, beta, false, endTime);
					}
					else {
						s = -choose(board_copy, cColor == WHITE ? BLACK : WHITE, step + 1, -beta, -alpha, true, endTime);
					}
					if (s > score) score = s;
					if (score > alpha) alpha = score;
					if (alpha >= beta) return alpha;
				}
			}
		}
		return score;
	}
	else {
		return srf(board);
	}

	return 0.0;
}

Player *Ai_Player::createAiPlayer(char *str, AI_PLAYER_LEVEL level) {
	Ai_Player *plr = 0;
	if (strcmp(str, "alphabeta") == 0) {
		plr = new Ai_Player_AlphaBeta();
	} else if (strcmp(str, "negascout") == 0) {
		plr = new Ai_Player_NegaScout();
	} else {
		return 0;
	}
	plr->setLevel(level);
	return plr;
}
Player *Ai_Player::createAiPlayer(char *str, int depth) {
	Ai_Player *plr = 0;
	if (strcmp(str, "alphabeta") == 0) {
		plr = new Ai_Player_AlphaBeta();
	} else if (strcmp(str, "negascout") == 0) {
		plr = new Ai_Player_NegaScout();
	} else {
		return 0;
	}
	plr->setDepth(depth);
	return plr;
}

double Ai_Player::srf(BOARD board) {
	if (color == WHITE) {
		return (board.white() - board.black()) + 2.5 * (board.whiteKing() - board.blackKing());
	}
	else if (color == BLACK) {
		return (board.black() - board.white()) + 2.5 * (board.blackKing() - board.whiteKing());
	}

	return 0.0;
}
