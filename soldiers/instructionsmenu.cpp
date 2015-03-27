#include "instructionsmenu.h"
#include <QLabel>

instructionsMenu::instructionsMenu(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("This is where we will talk about instructions. \nLorem ipsum dolor sit amet, consectetur adipiscing elit. \nDuis nibh nunc, venenatis eu augue in, fringilla sagittis ex.\nSed tempus ligula neque, in lacinia metus tempus sit amet. \nDuis in pulvinar turpis, at eleifend lacus.\nEtiam ac ante diam. \nQuisque placerat metus elit, facilisis tincidunt risus gravida vitae. \nUt in rhoncus libero. \nPhasellus pharetra, lorem id egestas consectetur, \nrisus libero mollis leo, in pellentesque risus diam vitae mauris. \nDuis non elit id augue euismod fermentum.");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void instructionsMenu::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
instructionsMenu::~instructionsMenu()
{

}

