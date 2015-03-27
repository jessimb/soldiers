#include "newgamemenu.h"
#include <QLabel>


newGameMenu::newGameMenu(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("newGameMenu");
    buttonlayout->addWidget(label);

    QPushButton *easy = new QPushButton("Easy");
    QPushButton *medium = new QPushButton("Medium");
    QPushButton *hard = new QPushButton("Hard");
    QPushButton *expert = new QPushButton("Expert");
    QPushButton *back = new QPushButton("Go Back");

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
    stackedWidget->addWidget(mainWindow->puzzleWindowObj); //3
    stackedWidget->setCurrentIndex(3);
}


newGameMenu::~newGameMenu()
{

}

