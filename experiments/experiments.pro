TEMPLATE = app
TARGET = ../experiment
DEPENDPATH += . ../src
INCLUDEPATH += . ../src
QT += testlib
CONFIG += qt debug warn_off
OBJECTS_DIR = ../bin/experiments
MOC_DIR = ../bin/experiments
DEFINES += DATADIR=\\\"$$DATADIR\\\"

HEADERS += experiment.h \
           Players/player.h \
           Players/ai_player.h \
           Model/board.h

SOURCES += main.cpp \
           experiment.cpp \
           Players/ai_player.cpp \
           Model/board.cpp
