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
    this->setStyleSheet("background-color:#fff;");
    QPixmap pixelMap = QPixmap(":/images/soldierLogo.png");
    QPixmap tempShrink = pixelMap.scaled(QSize(400,400),Qt::KeepAspectRatio);
    label->setPixmap(tempShrink);
    label->setAlignment(Qt::AlignCenter);
    buttonlayout->addWidget(label,0,0,2,2);

    QPushButton *newGame = new QPushButton("New Game");
    QPushButton *instr = new QPushButton("Instructions");
    QPushButton *load = new QPushButton("Load Game");
    QPushButton *leader = new QPushButton("Leaderboard");
    QPushButton *stats = new QPushButton("Statistics");
    newGame->setFixedSize(312, 45);
    instr->setFixedSize(150, 45);
    load->setFixedSize(150, 45);
    leader->setFixedSize(150, 45);
    stats->setFixedSize(150, 45);
    newGame->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");
    instr->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");
    load->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");
    leader->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");
    stats->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");


    buttonlayout->addWidget(newGame,1,1,1,2);
    buttonlayout->addWidget(instr, 2,1);
    buttonlayout->addWidget(load, 2,2);
    buttonlayout->addWidget(leader,3,2);
    buttonlayout->addWidget(stats,3,1);


    connect(newGame, SIGNAL(clicked()), this, SLOT(gotoNewGameMenu()));
    connect(instr, SIGNAL(clicked()), this, SLOT(gotoInstrMenu()));
    connect(load,SIGNAL(clicked()),this,SLOT(gotoPuzzleWindow()));
    connect(leader,SIGNAL(clicked()),this,SLOT(gotoLeaderboard()));
    connect(stats,SIGNAL(clicked()),this,SLOT(gotoStatsWindow()));
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
    stackedWidget->addWidget(mainWindow->puzzleWindowObj); //7
    stackedWidget->setCurrentIndex(7);
}

void mainMenu::gotoLeaderboard()
{
    stackedWidget->setCurrentIndex(4);
}

void mainMenu::gotoStatsWindow()
{
    stackedWidget->setCurrentIndex(3);
}



mainMenu::~mainMenu()
{

}

