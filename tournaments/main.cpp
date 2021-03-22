#include <QtCore>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tournament.h"
#include "Players/ai_player.h"

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);

	if (argc < 2) {
		qDebug() << "=== Error! ===========================================";
		qDebug() << "Please, give the filename with tournaments parametres!";
		qDebug() << "Example: " << argv[0] << " tournaments.txt";
		qDebug() << "======================================================";
	}

	std::ifstream file(argv[1]);
	char str[500], *p_title, *p_plr1, *p_lvl1, *p_plr2, *p_lvl2, *p_cnt;
	bool timeCtr1, timeCtr2;
	AI_PLAYER_LEVEL level1, level2;
	int depth1, depth2, cnt;

	while (!file.eof()) {
		file.getline(str, sizeof(str));

		p_title = strtok(str, "\t\n\r");
		if (!p_title) continue;
		std::string title(p_title);

		p_plr1 = strtok(NULL, "\t\n\r");
		if (!p_plr1) continue;
		p_lvl1 = strtok(NULL, "\t\n\r");
		if (!p_lvl1) continue;
		qDebug() << "p_lvl1 = " << p_lvl1 << " :: " << is_numeric(p_lvl1) << "";
		if (is_numeric(p_lvl1)) {
			timeCtr1 = false;
			depth1 = atoi(p_lvl1);
			if (depth1 <= 0 || depth1 > 12) continue;
		} else {
			timeCtr1 = true;
			if (p_lvl1[0] == 'L') level1 = LVL_L;
			else if (p_lvl1[0] == 'M') level1 = LVL_M;
			else if (p_lvl1[0] == 'D') level1 = LVL_D;
			else continue;
		}

		p_plr2 = strtok(NULL, "\t\n\r");
		if (!p_plr2) continue;
		p_lvl2 = strtok(NULL, "\t\n\r");
		if (!p_lvl2) continue;
		if (is_numeric(p_lvl2)) {
			timeCtr2 = false;
			depth2 = atoi(p_lvl2);
			if (depth2 <= 0 || depth2 > 12) continue;
		} else {
			timeCtr2 = true;
			if (p_lvl2[0] == 'L') level2 = LVL_L;
			else if (p_lvl2[0] == 'M') level2 = LVL_M;
			else if (p_lvl2[0] == 'D') level2 = LVL_D;
			else continue;
		}

		p_cnt = strtok(NULL, "\t\n\r");
		if (!p_cnt) continue;
		cnt = atoi(p_cnt);
		if (cnt <= 0) continue;

		new Tournament(title,
					timeCtr1 ? Ai_Player::createAiPlayer(p_plr1, level1) : Ai_Player::createAiPlayer(p_plr1, depth1),
					timeCtr2 ? Ai_Player::createAiPlayer(p_plr2, level2) : Ai_Player::createAiPlayer(p_plr2, depth2),
		cnt);
	}

	return app.exec();
}
