#include "instructionsmenu.h"
#include <QLabel>

instructionsMenu::instructionsMenu(MainWindow *mw)
{

    mainWindow = mw;
   // QWidget *widget = new QWidget;
    //setCentralWidget(widget);
   // QGridLayout *layout = new QGridLayout;
    QGridLayout *buttonlayout = new QGridLayout;

   // widget->setLayout(buttonlayout);

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("instructions");
    buttonlayout->addWidget(label);

    //Make the left side things
    //QWidget *leftSide = new QWidget;
    QPushButton *back = new QPushButton("Go Back");

    //leftSide->setLayout(vLayout);
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void instructionsMenu::gotoMainMenu()
{
   // cout << "gotomainmenu\n";
    stackedWidget->setCurrentIndex(0);
}
instructionsMenu::~instructionsMenu()
{

}

