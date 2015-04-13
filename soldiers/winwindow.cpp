#include "winwindow.h"
#include "puzzlewindow.h"
#include <QLabel>
#include <QMovie>

winWindow::winWindow(MainWindow *mw)
{

    mainWindow = mw;
    buttonLayout = new QGridLayout;

    this->setLayout(buttonLayout);
    //Doesn't properly show the score since this is created when the game is created not when a game is won.
    scoreLabel = new QLabel();
    QLabel * fireWorksLabel = new QLabel();
    QMovie * temp = new QMovie(":/images/Fireworks.gif");
    fireWorksLabel->setMovie(temp);
    temp->start();
    buttonLayout->addWidget(fireWorksLabel,0,0,2,1,Qt::AlignHCenter);
    buttonLayout->addWidget(scoreLabel,2,0,1,1,Qt::AlignHCenter);


    QPushButton *back = new QPushButton("Main Menu");
    buttonLayout->addWidget(back,3,0,1,1,Qt::AlignHCenter);
    this->setStyleSheet("background-color:#FAFAD2;");
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

void winWindow::updateScore(){
    buttonLayout->removeWidget(scoreLabel);
    buttonLayout->addWidget(scoreLabel,2,0,1,1,Qt::AlignHCenter);
}
