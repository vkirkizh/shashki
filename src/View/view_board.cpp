#include "View/view_board.h"

View_Board::View_Board(QWidget *parent):QWidget(parent) {
	qDebug() << "View_Board::View_Board(QWidget *parent):QWidget(parent)";

	window = parent;
}

void View_Board::init(Game *_game) {
	qDebug() << "View_Board::init(Game *_game) -> BEGIN";

	game = _game;
	board = &game->getBoard();
	end_flag = END_NONE;

	connect(game, SIGNAL(updateBoard()), SLOT(updateBoard()));
	connect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));

	setGeometry(10, 10, 450, 400);

	installEventFilter(this);

	show();

	qDebug() << "View_Board::init(Game *_game) -> END";
}

void View_Board::execMove(BOARD board) {
	qDebug() << "View_Board::execMove(BOARD board) -> BEGIN";

	read_flag = true;
	ready = 0;
	qDebug() << "ready = 0;";
	do {
		if (isReady()) {
			qDebug() << "View_Board::execMove(BOARD board) -> result = " << result.from.x+1 << "," << result.from.y+1 << " >> " << result.to.x+1 << "," << result.to.y+1;
			break;
		}
		usleep(300);
	} while (true);

	qDebug() << "View_Board::execMove(BOARD board) -> END";
}

bool View_Board::isReady() {
	return ready == 2;
}

void View_Board::paintEvent(QPaintEvent *event) {
	QPainter paint(this);
	paint.setPen(QPen(Qt::white, 1));
	paint.setBrush(QBrush(QColor(0x55, 0x55, 0x55)));
	for (int i = 1; i <= 8; i++) {
		paint.drawRect(QRect(i * 44, 0, 44, 44));
	}
	for (int j = 1; j <= 8; j++) {
		paint.drawRect(QRect(0, j * 44, 44, 44));
	}
	paint.drawText(60 + 44*0, 30, "1");
	paint.drawText(60 + 44*1, 30, "2");
	paint.drawText(60 + 44*2, 30, "3");
	paint.drawText(60 + 44*3, 30, "4");
	paint.drawText(60 + 44*4, 30, "5");
	paint.drawText(60 + 44*5, 30, "6");
	paint.drawText(60 + 44*6, 30, "7");
	paint.drawText(60 + 44*7, 30, "8");
	paint.drawText(15, 75 + 44*0, "1");
	paint.drawText(15, 75 + 44*1, "2");
	paint.drawText(15, 75 + 44*2, "3");
	paint.drawText(15, 75 + 44*3, "4");
	paint.drawText(15, 75 + 44*4, "5");
	paint.drawText(15, 75 + 44*5, "6");
	paint.drawText(15, 75 + 44*6, "7");
	paint.drawText(15, 75 + 44*7, "8");
	paint.setPen(QPen(Qt::white, 1));
	for (int i = 0, x0 = 44; i < 8; i++) {
		for (int j = 0, y0 = 44; j < 8; j++) {
			paint.setBrush(QBrush(( (i + j) % 2 ? QColor(0x77, 0xdd, 0x77) : QColor(0xba, 0xdb, 0xad) )));
			paint.drawRect(QRect(x0 + i * 44, y0 + j * 44, 44, 44));
		}
	}
	for (int i = 0, x0 = 44; i < 8; i++) {
		for (int j = 0, y0 = 44; j < 8; j++) {
			FIGURE f = board->gcell(i, j);
			if (IS_EMPTY(f)) continue;
			paint.setBrush(QBrush(IS_WHITE(f) ? Qt::white : Qt::black));
			paint.setPen(QPen(IS_WHITE(f) ? Qt::black : Qt::white, 1));
			paint.drawEllipse(QRect(x0 + i * 44 + 4, y0 + j * 44 + 4, 36, 36));
			if (IS_KNG(f)) {
				paint.setPen(QPen(IS_WHITE(f) ? Qt::black : Qt::white, 3));
				paint.drawEllipse(QRect(x0 + i * 44 + 10, y0 + j * 44 + 10, 24, 24));
			}
		}
	}
	if (!end_flag) {
		paint.setBrush(QBrush(Qt::yellow));
		paint.setPen(QPen(Qt::white, 2));
		if (board->getCurrentColor() != WHITE) {
			paint.drawEllipse(QRect(410, 60, 20, 20));
		} else {
			paint.drawEllipse(QRect(410, 360, 20, 20));
		}
	}
}

bool View_Board::eventFilter(QObject *target, QEvent *event) {
	if (event->type() == QEvent::MouseButtonPress && read_flag) {
		QMouseEvent *mouseEvent = (QMouseEvent*)event;
		int x = (mouseEvent->pos().x() - 44) / 44, y = (mouseEvent->pos().y() - 44) / 44;
		FIGURE f = board->gcell(x, y);
		if (ready == 0) {
			qDebug() << "if (ready == 0) ...";
			result.from.x = x;
			result.from.y = y;
			if (0
				|| (color == WHITE && !IS_WHITE(f))
				|| (color == BLACK && !IS_BLACK(f))
			) return true;
			ready = 1;
			qDebug() << "ready = 1;";
			return true;
		}
		else if (ready == 1) {
			qDebug() << "if (ready == 1) ...";
			result.to.x = x;
			result.to.y = y;
			if (!board->canMove(result)) {
				result.from.x = x;
				result.from.y = y;
				if (0
					|| (color == WHITE && !IS_WHITE(f))
					|| (color == BLACK && !IS_BLACK(f))
				) {
					ready = 0;
					qDebug() << "ready = 0;";
					return true;
				}
				ready = 1;
				qDebug() << "ready = 1;";
				return true;
			}
			ready = 2;
			qDebug() << "ready = 2;";
			read_flag = false;
			return true;
		}
		return true;
	}
	return false;
};

void View_Board::updateBoard() {
	update();
}

void View_Board::finishGame(GAMESTATE res_flag) {
	qDebug() << "View_Board::finishGame(GAMESTATE res_flag)";

	end_flag = res_flag;
	update();
}
