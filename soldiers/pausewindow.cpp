#include "pausewindow.h"
#include <QLabel>

pauseWindow::pauseWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("game is paused");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Continue");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#fff;");
    back->setFixedSize(150, 45);
    back->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");


    connect(back, SIGNAL(clicked()), this, SLOT(goBackToPuzzle()));


}

void pauseWindow::goBackToPuzzle()
{
    stackedWidget->setCurrentIndex(7);
}
pauseWindow::~pauseWindow()
{

}

