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

    int averageHS= highscorefunc();
    int averageBS= besttimefunc();
    QLabel *label = new QLabel("Statistics");
    QFont f( "Courier New", 20, QFont::Bold);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(f);
    QLabel *score = new QLabel("Average High Score: ");
    QFont f1( "Courier New", 15);
    score->setFont(f1);
    QLabel *time = new QLabel("Average Best Time: ");
    time->setFont(f1);

    QString str;
    str.setNum(averageHS);
    QLabel *highscore = new QLabel;
    highscore->setText(str);
    QFont f2("Courier New", 15);
    highscore->setFont(f2);

    QString str2;
    str2.setNum(averageBS);
    QLabel *besttime = new QLabel;
    besttime->setText(str2);
    besttime->setFont(f2);

    buttonlayout->addWidget(label);
    buttonlayout->addWidget(score,1,0);
    buttonlayout->addWidget(highscore,1,10000);
    buttonlayout->addWidget(time,2,0);
    buttonlayout->addWidget(besttime,2,10000);
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

int statsWindow::highscorefunc()
{
    highScore=0;
    for(int i=0;i<scorevec.size()-1;i++)
    {

        if(scorevec.at(i)>highScore)
        {
            highScore=scorevec.at(i);
        }
    }
    int HS=highScore/totalgamesplayed;
    return HS;
}
int statsWindow::besttimefunc()
{
    bestTime=0;
    for(int i=0;i<timevec.size()-1;i++)
    {
        if(timevec.at(i)>bestTime)
        {
            bestTime=timevec.at(i);
        }
    }
    int BT=bestTime/totalgamesplayed;
    return BT;
}
