#include "statswindow.h"
#include <QLabel>
#include <QDebug>

statsWindow::statsWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;
    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    this->setLayout(buttonlayout);
    int averageHS=averagehighscore();
    int averageBS=averagebesttime();
    QLabel *label = new QLabel("Statistics");

    QString str;
    str.setNum(averageHS);// val may be any integer value
    QLabel *highscore = new QLabel;
    highscore->setText(str);

    QString str2;
    str2.setNum(averageBS);
    QLabel *besttime = new QLabel;
    besttime->setText(str2);

    buttonlayout->addWidget(label);
    buttonlayout->addWidget(highscore);
    buttonlayout->addWidget(besttime);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet(*style);
    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void statsWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
statsWindow::~statsWindow()
{

}
int statsWindow::averagehighscore()
{
     //int averageHS=highScore/totalgamesplayed;
    qDebug()<<"in average high score";
    return 5;
}
int statsWindow::averagebesttime()
{
    //int averagetime=bestTime/totalgamesplayed;
    qDebug()<<"in average time";
    return 2;
}
