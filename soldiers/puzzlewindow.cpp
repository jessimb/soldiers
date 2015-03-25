#include "puzzlewindow.h"
#include <QLabel>

puzzleWindow::puzzleWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("puzzle");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Go Back");
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void puzzleWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
puzzleWindow::~puzzleWindow()
{

}

