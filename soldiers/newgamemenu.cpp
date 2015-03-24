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


}

void newGameMenu::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}

newGameMenu::~newGameMenu()
{

}

