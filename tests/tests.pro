TEMPLATE = app
TARGET = ../test
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
QT += testlib
CONFIG += qt debug warn_off qtestlib
OBJECTS_DIR = ../bin/tests
MOC_DIR = ../bin/tests
DEFINES += DATADIR=\\\"$$DATADIR\\\"

HEADERS += test_board.h \
           Players/player.h \
           Players/ai_player.h \
           Model/board.h

SOURCES += main.cpp \
           test_board.cpp \
           Players/ai_player.cpp \
           Model/board.cpp
