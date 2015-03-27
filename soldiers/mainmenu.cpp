#include "mainmenu.h"
#include <QLabel>
#include <iostream>
#include <QFileDialog>
#include "saveload.h"
using namespace std;
mainMenu::mainMenu(MainWindow *mw) : QWidget()
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel();
//    QString fileName = "Super Sudoku.png";
//    QFileDialog * fileDirectory = new QFileDialog();
//    QString fileName = fileDirectory->getOpenFileName(this, QString("Browse"), "/", tr("Image Files (*.png *.jpg *.bmp"));
//    cout << fileName.toStdString() << endl;
    QPixmap pixelMap = QPixmap(":/images/soldierLogo.png");
    QPixmap tempShrink = pixelMap.scaled(QSize(400,400),Qt::KeepAspectRatio);
    label->setPixmap(tempShrink);
    label->setAlignment(Qt::AlignCenter);
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
    connect(load,SIGNAL(clicked()),this,SLOT(gotoPuzzleWindow()));
}

void mainMenu::gotoNewGameMenu()
{
    stackedWidget->setCurrentIndex(1);
}

void mainMenu::gotoInstrMenu()
{

    stackedWidget->setCurrentIndex(2);
}

void mainMenu::gotoPuzzleWindow()
{
    mainWindow->puzzleWindowObj = new puzzleWindow(mainWindow,true);
    stackedWidget->addWidget(mainWindow->puzzleWindowObj); //3
    stackedWidget->setCurrentIndex(3);
}



mainMenu::~mainMenu()
{

}

