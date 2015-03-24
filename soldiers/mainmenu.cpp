#include "mainmenu.h"
#include <QLabel>
#include <iostream>

using namespace std;
mainMenu::mainMenu(MainWindow *mw) : QWidget()
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("mainMenu");
    buttonlayout->addWidget(label);


    QPushButton *newGame = new QPushButton("New Game");
    QPushButton *instr = new QPushButton("Instructions");
    QPushButton *load = new QPushButton("Load Game");
    QPushButton *leader = new QPushButton("Leaderboard");
    QPushButton *stats = new QPushButton("Statistics");

    //leftSide->setLayout(vLayout);
    buttonlayout->addWidget(newGame);
    buttonlayout->addWidget(instr);
    buttonlayout->addWidget(load);
    buttonlayout->addWidget(leader);
    buttonlayout->addWidget(stats);


    connect(newGame, SIGNAL(clicked()), this, SLOT(gotoNewGameMenu()));
    connect(instr, SIGNAL(clicked()), this, SLOT(gotoInstrMenu()));
}

void mainMenu::gotoNewGameMenu()
{
    stackedWidget->setCurrentIndex(1);
}

void mainMenu::gotoInstrMenu()
{
    stackedWidget->setCurrentIndex(2);
}


mainMenu::~mainMenu()
{

}

