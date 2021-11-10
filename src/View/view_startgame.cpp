#include "View/view_startgame.h"

View_StartGame::View_StartGame(QWidget *parent) {
	qDebug() << "View_StartGame::View_StartGame(QWidget *parent)";

	window = parent;
	greeting = NULL;
	settings = NULL;
	wp = NULL;
	bp = NULL;
}

void View_StartGame::show() {
	qDebug() << "View_StartGame::show() -> BEGIN";

	greeting = new QFrame(window);
	greeting->setGeometry(40, 40, 720, 340);
	greeting->setFrameStyle(QFrame::Box | QFrame::Plain);
	greeting->setLineWidth(3);
	greeting->show();
	qDebug() << "View_StartGame::show() -> greeting box";

	QGroupBox *plr1 = new QGroupBox(greeting);
	plr1->setObjectName("White player");
	plr1->setGeometry(10, 5, 340, 270);
	QLabel *plr1_Label = new QLabel("White player");
	QRadioButton *plr1_Human = new QRadioButton("Human");
	QRadioButton *plr1_Ai = new QRadioButton("Computer");
	plr1_Ai->setChecked(true);
	QVBoxLayout *plr1_Layout = new QVBoxLayout;
	plr1_Layout->addWidget(plr1_Label);
	plr1_Layout->addWidget(plr1_Human);
	plr1_Layout->addWidget(plr1_Ai);
	plr1->setLayout(plr1_Layout);
	plr1->show();
	qDebug() << "View_StartGame::show() -> choose white player";

	QGroupBox *plr2 = new QGroupBox(greeting);
	plr2->setObjectName("Black player");
	plr2->setGeometry(360, 5, 340, 270);
	QLabel *plr2_Label = new QLabel("Black player", plr2);
	QRadioButton *plr2_Human = new QRadioButton("Human", plr2);
	QRadioButton *plr2_Ai = new QRadioButton("Computer", plr2);
	plr2_Ai->setChecked(true);
	QVBoxLayout *plr2_Layout = new QVBoxLayout;
	plr2_Layout->addWidget(plr2_Label);
	plr2_Layout->addWidget(plr2_Human);
	plr2_Layout->addWidget(plr2_Ai);
	plr2->setLayout(plr2_Layout);
	plr2->show();
	qDebug() << "View_StartGame::show() -> choose black player";

	QPushButton *start_btn = new QPushButton("Start game!", greeting);
	start_btn->setGeometry(260, 280, 200, 45);
	start_btn->show();
	connect(start_btn, SIGNAL(clicked()), SLOT(startGame()));

	qDebug() << "View_StartGame::show() -> END";
}

void View_StartGame::hide() {
	qDebug() << "View_StartGame::hide() -> greeting box";

	if (greeting) delete greeting;
	greeting = NULL;

	if (settings) delete settings;
	settings = NULL;

	qDebug() << "View_StartGame::hide() -> END";
}

void View_StartGame::startGame() {
	qDebug() << "View_StartGame::startGame()";

	QList<QRadioButton*> wLst = greeting->findChild<QGroupBox*>("White player")->findChildren<QRadioButton*>();
	if (wLst.at(0)->isChecked()) wPlr = HUMAN;
	else if (wLst.at(1)->isChecked()) wPlr = AI;

	QList<QRadioButton*> bLst = greeting->findChild<QGroupBox*>("Black player")->findChildren<QRadioButton*>();
	if (bLst.at(0)->isChecked()) bPlr = HUMAN;
	else if (bLst.at(1)->isChecked()) bPlr = AI;

	greeting->hide();
	delete greeting;
	greeting = NULL;

	qDebug() << "View_StartGame -> setupPlayerBegin(WHITE)";
	setupPlayerBegin(WHITE);
}

void View_StartGame::setupPlayerBegin(COLOR color) {
	curColor = color;
	PLAYER_TYPE plr = (color == WHITE ? wPlr : bPlr);

	qDebug() << "View_StartGame::setupPlayerBegin(COLOR color) -> BEGIN -> " << (color == WHITE ? "White" : "Black");

	settings = new QFrame(window);
	settings->setGeometry(40, 40, 720, 340);
	settings->setFrameStyle(QFrame::Box | QFrame::Plain);
	settings->setLineWidth(3);
	settings->show();

	QLabel *header = new QLabel(color == WHITE ? "White player settings" : "Black player settings", settings);
	header->setGeometry(10, 5, 700, 30);
	header->show();

	next_btn = new QPushButton("Next >>", settings);
	next_btn->setGeometry(260, 280, 200, 45);
	next_btn->show();

	connect(this, SIGNAL(setupPlayerEndSignal(Player*)), SLOT(setupPlayerEndSlot(Player*)));

	if (plr == HUMAN) {
		emit setupPlayerEndSignal(NULL);
	} else if (plr == AI) {
		AiPlr = new Ai_Player();
		AiPlr->setColor(color);
		setupAi();
	} else {
		exit(1);
	}
}

void View_StartGame::setupAi() {
	qDebug() << "View_StartGame::setupAi()";

	setupAiShowLevel();
}

void View_StartGame::setupAiShowLevel() {
	qDebug() << "View_StartGame::setupAiShowLevel()";

	QGroupBox *ai_level = new QGroupBox(settings);
	ai_level->setObjectName("Ai level");
	ai_level->setGeometry(180, 40, 360, 240);
	QLabel *ai_level_Label = new QLabel("Ai Level:");
	QRadioButton *ai_level_1 = new QRadioButton("Easy");
	QRadioButton *ai_level_2 = new QRadioButton("Medium");
	QRadioButton *ai_level_3 = new QRadioButton("Hard");
	ai_level_2->setChecked(true);
	QVBoxLayout *ai_level_Layout = new QVBoxLayout;
	ai_level_Layout->addWidget(ai_level_Label);
	ai_level_Layout->addWidget(ai_level_1);
	ai_level_Layout->addWidget(ai_level_2);
	ai_level_Layout->addWidget(ai_level_3);
	ai_level->setLayout(ai_level_Layout);
	ai_level->show();
	connect(next_btn, SIGNAL(clicked()), SLOT(setupAiGetLevel()));
}
void View_StartGame::setupAiGetLevel() {
	qDebug() << "View_StartGame::setupAiGetLevel()";

	disconnect(next_btn, SIGNAL(clicked()), this, SLOT(setupAiGetLevel()));
	settings->findChild<QGroupBox*>("Ai level")->hide();
	QList<QRadioButton*> ai_level = settings->findChild<QGroupBox*>("Ai level")->findChildren<QRadioButton*>();
	if (ai_level.at(0)->isChecked()) AiPlr->setLevel(LVL_L);
	else if (ai_level.at(1)->isChecked()) AiPlr->setLevel(LVL_M);
	else if (ai_level.at(2)->isChecked()) AiPlr->setLevel(LVL_D);
	setupAiEnd();
}

void View_StartGame::setupAiEnd() {
	qDebug() << "View_StartGame::setupAiEnd()";

	Player *p = (Player*)AiPlr;
	emit setupPlayerEndSignal(p);
}

void View_StartGame::setupPlayerEndSlot(Player *p) {
	qDebug() << "View_StartGame::setupPlayerEndSlot(Player *p)";

	settings->hide();
	delete settings;
	settings = NULL;
	disconnect(this, SIGNAL(setupPlayerEndSignal(Player*)), this, SLOT(setupPlayerEndSlot(Player*)));
	if (curColor == WHITE) {
		wp = p;
		qDebug() << "View_StartGame -> setupPlayerBegin(BLACK)";
		setupPlayerBegin(BLACK);
	} else if (curColor == BLACK) {
		bp = p;
		qDebug() << "View_StartGame emit createGame(wp, bp);";
		emit createGame(wp, bp);
	} else {
		exit(1);
	}
}

View_StartGame::~View_StartGame() {
	qDebug() << "View_StartGame::~View_StartGame() -> BEGIN";

	if (wp) delete wp;
	if (bp) delete bp;

	qDebug() << "View_StartGame::~View_StartGame() -> END";
}
