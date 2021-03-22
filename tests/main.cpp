#include <QtCore>
#include "test_board.h"

int main(int argc, char** argv) {
	Test_Board test1;
	QTest::qExec(&test1);
	return 0;
}
