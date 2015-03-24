#include "mainmenu.h"
#include <QLabel>
#include <iostream>

using namespace std;
mainMenu::mainMenu(MainWindow *mw) : QWidget()
{

    mainWindow = mw;
    //QWidget *widget = new QWidget;
    //setCentralWidget(widget);
   // QGridLayout *layout = new QGridLayout;
    QGridLayout *buttonlayout = new QGridLayout;

    //widget->setLayout(buttonlayout);

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("mainMenu");
    buttonlayout->addWidget(label);


    //Make the left side things
    //QWidget *leftSide = new QWidget;
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


    //layout->addWidget(buttonlayout);
   /// layout->addLayout(buttonlayout);

    connect(newGame, SIGNAL(clicked()), this, SLOT(gotoNewGameMenu()));
    connect(instr, SIGNAL(clicked()), this, SLOT(gotoInstrMenu()));
}

void mainMenu::gotoNewGameMenu()
{
   // cout << "gotonewgamemenu\n";
    //mainWindow->changeToNewGameMenu();
    stackedWidget->setCurrentIndex(1);
}

void mainMenu::gotoInstrMenu()
{
   // cout << "gotonewgamemenu\n";
    stackedWidget->setCurrentIndex(2);
}


mainMenu::~mainMenu()
{

}

