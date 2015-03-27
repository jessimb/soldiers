#include "newgamemenu.h"
#include <QLabel>
#include <iostream>
newGameMenu::newGameMenu(MainWindow *mw)
{
 setFocusPolicy(Qt::ClickFocus);
    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    //buttonlayout->addWidget(label,0,0,1,2);

    this->setStyleSheet("background-color:#FAFAD2;");
    QPushButton *easy = new QPushButton("Easy");
    QPushButton *medium = new QPushButton("Medium");
    QPushButton *hard = new QPushButton("Hard");
    QPushButton *expert = new QPushButton("Expert");
    QPushButton *back = new QPushButton("Go Back");
    easy->setFixedSize(250, 45);
    medium->setFixedSize(250, 45);
    hard->setFixedSize(250, 45);
    expert->setFixedSize(250, 45);
    back->setFixedSize(250, 45);
    easy->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    medium->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    hard->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    expert->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    back->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    buttonlayout->addWidget(easy);
    buttonlayout->addWidget(medium);
    buttonlayout->addWidget(hard);
    buttonlayout->addWidget(expert);
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));
    connect(easy, SIGNAL(clicked()), this, SLOT(gotoPuzzleWindow()));


}

void newGameMenu::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}

void newGameMenu::gotoPuzzleWindow()
{

    mainWindow->puzzleWindowObj = new puzzleWindow();
    stackedWidget->addWidget(mainWindow->puzzleWindowObj); //lastone
    stackedWidget->setCurrentIndex(stackedWidget->count()-1);
}


newGameMenu::~newGameMenu()
{

}

