TEMPLATE = app
TARGET = ../tournament
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
CONFIG += qt debug warn_off
OBJECTS_DIR = ../bin/tournaments
MOC_DIR = ../bin/tournaments
DEFINES += DATADIR=\\\"$$DATADIR\\\"

HEADERS += Players/player.h \
           Players/ai_player.h \
           Model/board.h \
           Model/game.h \
           tournament.h

SOURCES += main.cpp \
           Players/ai_player.cpp \
           Model/board.cpp \
           Model/game.cpp \
           tournament.cpp
