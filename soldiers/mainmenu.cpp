#include "mainmenu.h"
#include <QLabel>
#include <iostream>
#include <QFileDialog>
#include "saveload.h"
#include "MainWindowContainer.h"
#include <string>
using namespace std;
QString globalUser="Anonymous";
unordered_map<string,statsfunc *> users;
mainMenu::mainMenu(MainWindow *mw) : QWidget()
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    QString *fbstyle = new QString("QPushButton {font-family: \"Lucida Grande\"; font-size: 18px; border:1px solid #000;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    this->setLayout(buttonlayout);
    QLabel *label = new QLabel();
//    QString fileName = "Super Sudoku.png";
//    QFileDialog * fileDirectory = new QFileDialog();
//    QString fileName = fileDirectory->getOpenFileName(this, QString("Browse"), "/", tr("Image Files (*.png *.jpg *.bmp"));
//    cout << fileName.toStdString() << endl;
    this->setStyleSheet("background-color:#FAFAD2;");
    QPixmap pixelMap = QPixmap(":/images/soldierLogo.png");
    QPixmap tempShrink = pixelMap.scaled(QSize(400,400),Qt::KeepAspectRatio);


    label->setPixmap(tempShrink);
    label->setAlignment(Qt::AlignCenter);
    buttonlayout->addWidget(label,0,0);

    QPushButton *newGame = new QPushButton("New Game");
    QPushButton *instr = new QPushButton("Instructions");
    QPushButton *load = new QPushButton("Load Game");
    QPushButton *leader = new QPushButton("Leaderboard");
    QPushButton *stats = new QPushButton("Statistics");
    QPushButton *fb = new QPushButton();
    newGame->setFixedSize(312, 45);
    instr->setFixedSize(150, 45);
    load->setFixedSize(150, 45);
    leader->setFixedSize(150, 45);
    stats->setFixedSize(150, 45);
    fb->setFixedSize(150, 30);



    QPixmap pixelMapFb = QPixmap(":/images/facebooklogin.png");
    QPixmap tempShrinkFb = pixelMapFb.scaled(QSize(150,30),Qt::KeepAspectRatio);
    QIcon ButtonIcon(tempShrinkFb);
    fb->setIcon(ButtonIcon);
    fb->setIconSize(tempShrinkFb.rect().size());

    newGame->setStyleSheet(*style);
    instr->setStyleSheet(*style);
    load->setStyleSheet(*style);
    leader->setStyleSheet(*style);
    stats->setStyleSheet(*style);
    fb->setStyleSheet(*fbstyle);

    QWidget * buttonHolder = new QWidget();
    QGridLayout * buttonHolderLayout = new QGridLayout;
    buttonHolderLayout->setHorizontalSpacing(0);
    buttonHolderLayout->addWidget(newGame,0,0,1,2,Qt::AlignHCenter);
    buttonHolderLayout->addWidget(instr, 1,0);
    buttonHolderLayout->addWidget(load, 1,1);
    buttonHolderLayout->addWidget(leader,2,0);
    buttonHolderLayout->addWidget(stats,2,1);
    buttonHolderLayout->addWidget(fb,3,0,1,2,Qt::AlignHCenter);
    buttonHolder->setLayout(buttonHolderLayout);

    buttonlayout->addWidget(buttonHolder);



    connect(newGame, SIGNAL(clicked()), this, SLOT(gotoNewGameMenu()));
    connect(instr, SIGNAL(clicked()), this, SLOT(gotoInstrMenu()));
    connect(load,SIGNAL(clicked()),this,SLOT(gotoPuzzleWindow()));
    connect(leader,SIGNAL(clicked()),this,SLOT(gotoLeaderboard()));
    connect(stats,SIGNAL(clicked()),this,SLOT(gotoStatsWindow()));
    connect(fb,SIGNAL(clicked()),this,SLOT(gotoFacebook()));

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
    mainWindow->puzzleWindowObj = new puzzleWindow(mainWindow,"",true);
    stackedWidget->addWidget(mainWindow->puzzleWindowObj); //lastone
    stackedWidget->setCurrentIndex(stackedWidget->count() -1);
}

void mainMenu::gotoLeaderboard()
{
    mainWindow->leaderboardWindowObj->TP();
    stackedWidget->setCurrentIndex(4);
}

void mainMenu::gotoStatsWindow()
{
    mainWindow->statsWindowObj->updatestats(globalUser);
    stackedWidget->setCurrentIndex(3);
}

void mainMenu::gotoFacebook()
{
    MainWindowContainer *m= new MainWindowContainer(mainWindow);
    m->show();

}


mainMenu::~mainMenu()
{

}

