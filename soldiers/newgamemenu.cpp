#include "newgamemenu.h"
#include <QLabel>
#include <iostream>
#include "sigbutton.h"
#include <sstream>
newGameMenu::newGameMenu(MainWindow *mw)
{
 setFocusPolicy(Qt::ClickFocus);
    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;
    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    this->setLayout(buttonlayout);
    //buttonlayout->addWidget(label,0,0,1,2);

    this->setStyleSheet("background-color:#FAFAD2;");
    SigButton *easy = new SigButton(0);
    SigButton *medium = new SigButton(1);
    SigButton *hard = new SigButton(2);
    SigButton *expert = new SigButton(3);
    easy->setText("Easy");
    medium->setText("Medium");
    hard->setText("Hard");
    expert->setText("Expert");
    QPushButton *back = new QPushButton("Go Back");
    easy->setFixedSize(250, 45);
    medium->setFixedSize(250, 45);
    hard->setFixedSize(250, 45);
    expert->setFixedSize(250, 45);
    back->setFixedSize(250, 45);
    easy->setStyleSheet(*style);
    medium->setStyleSheet(*style);
    hard->setStyleSheet(*style);
    expert->setStyleSheet(*style);
    back->setStyleSheet(*style);

    buttonlayout->addWidget(easy);
    buttonlayout->addWidget(medium);
    buttonlayout->addWidget(hard);
    buttonlayout->addWidget(expert);
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));
    connect(easy, SIGNAL(clicked(int)), this, SLOT(gotoPuzzleWindow(int)));
    connect(medium, SIGNAL(clicked(int)), this, SLOT(gotoPuzzleWindow(int)));
    connect(hard, SIGNAL(clicked(int)), this, SLOT(gotoPuzzleWindow(int)));
    connect(expert, SIGNAL(clicked(int)), this, SLOT(gotoPuzzleWindow(int)));
}

void newGameMenu::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}

void newGameMenu::gotoPuzzleWindow(int l)
{
    int v1 = rand() % 4 + 1;
    std::string file = "";
    std::stringstream ss2;
    ss2 << v1;


    if (l == 0) {
        file = file + "e0" + ss2.str() + ".txt";
    }
    if (l == 1) {
        file = "m0" + ss2.str() + ".txt";
    }
    if (l == 2) {
        file = "h0" + ss2.str() + ".txt";
    }
    if (l == 3) {
        file = "ex0" + ss2.str() + ".txt";
    }
    mainWindow->puzzleWindowObj = new puzzleWindow(mainWindow, file);
    stackedWidget->addWidget(mainWindow->puzzleWindowObj); //lastone
    stackedWidget->setCurrentIndex(stackedWidget->count()-1);
}


newGameMenu::~newGameMenu()
{

}

