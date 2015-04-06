#include "statswindow.h"
#include <QLabel>
#include <QDebug>

statsWindow::statsWindow(MainWindow *mw,QString name)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;
    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    username=name;

    this->setLayout(buttonlayout);
//start here
    QWidget *statsholder = new QWidget;
    QGridLayout *statsholderlayout = new QGridLayout;

    int averageHS=averagehighscore();
    int averageBS=averagebesttime();
    QLabel *label = new QLabel("Statistics");
    QLabel *score = new QLabel("High Score: ");
    QLabel *time = new QLabel("Best Time: ");

    QString str;
    str.setNum(averageHS);
    QLabel *highscore = new QLabel;
    highscore->setText(str);

    QString str2;
    str2.setNum(averageBS);
    QLabel *besttime = new QLabel;
    besttime->setText(str2);

    buttonlayout->addWidget(label,0,500);
    buttonlayout->addWidget(score,1,500);
    buttonlayout->addWidget(highscore,1,500);
    buttonlayout->addWidget(time,2,0);
    buttonlayout->addWidget(besttime,2,500);
    statsholder->setLayout(statsholderlayout);

    buttonlayout->addWidget(statsholder);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet(*style);
    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));

    this->setStyleSheet("background-color:#FAFAD2;");

}

void statsWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
statsWindow::~statsWindow()
{

}

void statsWindow::statsfunction(int score, int time)
{
    currentscore=score;
    scorevec.push_front(currentscore);
    totalgamesplayed++;
    currenttime=time;
    timevec.push_front(currenttime);
}

int statsWindow::highscore()
{
    for(int i=0;i<scorevec.size()-1;i++)
    {
        highScore=0;
        if(scorevec.at(i)>highScore)
        {
            highScore=scorevec.at(i);
        }
    }
    int HS=highScore/totalgamesplayed;
    return HS;
}
int statsWindow::besttime()
{
    for(int i=0;i<timevec.size()-1;i++)
    {
        bestTime=0;
        if(timevec.at(i)>bestTime)
        {
            bestTime=timevec.at(i);
        }
    }
    int BT=bestTime/totalgamesplayed;
    return BT;
}
