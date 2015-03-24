#include "newgamemenu.h"
#include <QLabel>

newGameMenu::newGameMenu(MainWindow *mw)
{

    mainWindow = mw;
   // QWidget *widget = new QWidget;
    //setCentralWidget(widget);
   // QGridLayout *layout = new QGridLayout;
    QGridLayout *buttonlayout = new QGridLayout;

   // widget->setLayout(buttonlayout);

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("newGameMenu");
    buttonlayout->addWidget(label);

    //Make the left side things
    //QWidget *leftSide = new QWidget;
    QPushButton *easy = new QPushButton("Easy");
    QPushButton *medium = new QPushButton("Medium");
    QPushButton *hard = new QPushButton("Hard");
    QPushButton *expert = new QPushButton("Expert");
    QPushButton *back = new QPushButton("Go Back");

    //leftSide->setLayout(vLayout);
    buttonlayout->addWidget(easy);
    buttonlayout->addWidget(medium);
    buttonlayout->addWidget(hard);
    buttonlayout->addWidget(expert);
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void newGameMenu::gotoMainMenu()
{
    //cout << "gotomainmenu\n";

    stackedWidget->setCurrentIndex(0);
}

newGameMenu::~newGameMenu()
{

}

