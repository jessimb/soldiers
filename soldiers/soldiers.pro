#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T16:49:21
#
#-------------------------------------------------

QT       += core gui network webkit webkitwidgets widgets script
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui network webkit webkitwidgets widgets script

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
    winwindow.cpp \
    MainWindowContainer.cpp \
    FBApi.cpp \
    UT.cpp \
    HttpClient.cpp \
    json_reader.cpp \
    json_value.cpp \
    json_writer.cpp \
    statsfunc.cpp \
    undoerase.cpp

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
    winwindow.h \
    FBApi.h \
    HttpClient.h \
    MainWindowContainer.h \
    ui_fbapi_gui.h \
    UT.h \
    autolink.h \
    config.h \
    features.h \
    forwards.h \
    json.h \
    reader.h \
    value.h \
    writer.h \
    json_batchallocator.h \
    statsfunc.h \
    undoerase.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    icon.ico \
    README.txt

FORMS += \
    fbapi_gui.ui
