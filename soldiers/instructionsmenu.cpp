#include "instructionsmenu.h"
#include <QLabel>

instructionsMenu::instructionsMenu(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("instructions");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Go Back");
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void instructionsMenu::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
instructionsMenu::~instructionsMenu()
{

}

