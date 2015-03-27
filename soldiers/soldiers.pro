#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T16:49:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Soldier Sudoku"
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenu.cpp \
    instructionsmenu.cpp \
    newgamemenu.cpp \
    sigbutton.cpp \
    clickablelabel.cpp \
    puzzlewindow.cpp \
    saveload.cpp \
    leaderboardwindow.cpp \
    statswindow.cpp \
    pausewindow.cpp \
    winwindow.cpp

HEADERS  += mainwindow.h \
    mainmenu.h \
    instructionsmenu.h \
    newgamemenu.h \
    sigbutton.h \
    clickablelabel.h \
    puzzlewindow.h \
    saveload.h \
    leaderboardwindow.h \
    statswindow.h \
    pausewindow.h \
    winwindow.h

RESOURCES += \
    resources.qrc
