#include "winwindow.h"

#include <QLabel>

winWindow::winWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("You win!");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#fff;");
    back->setFixedSize(150, 45);
    back->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void winWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
winWindow::~winWindow()
{

}

