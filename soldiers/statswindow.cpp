#include "statswindow.h"
#include <QLabel>
#include <QDebug>
#include <tr1/unordered_map>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace std::tr1;

extern unordered_map<string,statsfunc*> users;

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

    int averageHS= highscorefunction();
    int averageBS= besttimefunction();
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
void statsWindow::statsupdate(QString name)
{
    statsfunc * userStats = users.find(name.toStdString())->second;
    highScore = userStats->highScore;
    totalgamesplayed = userStats->totalgamesplayed;
    bestTime = userStats->bestTime;
    scorevec = userStats->scorevec;
    timevec = userStats->timevec;

    int averageHS= highscorefunction();
    int averageBS= besttimefunction();

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

}

void statsWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
statsWindow::~statsWindow()
{

}

int statsWindow::highscorefunction()
{
   
    for(int i=0;i<scorevec.size()-1;i++)
    {

        if(scorevec.at(i)>highScore)
        {
            highScore=scorevec.at(i);
        }
    }
    if(totalgamesplayed == 0)
        return 0;
    int HS=highScore/totalgamesplayed;
    return HS;
}

int statsWindow::besttimefunction()
{
    
    for(int i=0;i<timevec.size()-1;i++)
    {
        if(timevec.at(i)>bestTime)
        {
            bestTime=timevec.at(i);
        }
    }
    //int BT=bestTime/totalgamesplayed;
    return 0;
}

void statsWindow::loadStats()
{
    ifstream myfile("sudoku.sudostat");
    string line="";
    if(myfile.is_open())
    {
       getline (myfile,line);
       int totalRecords = atoi(line.c_str());

       for(int i=0;i<totalRecords;i++)
       {
           //Get name
           getline(myfile,line);
           string name = line;

           statsfunc * cur = new statsfunc(QString::fromStdString(name));

           getline(myfile,line);
           cur->bestTime = atoi(line.c_str());

           getline(myfile,line);
           cur->highScore = atoi(line.c_str());

           getline(myfile,line);
           int totalScores = atoi(line.c_str());

           QVector<int> scoreset;
           for(int k=0;k<totalScores;k++)
           {
               getline(myfile,line);
               scoreset.push_back(atoi(line.c_str()));
           }
           getline(myfile,line);
           int totalTimes = atoi(line.c_str());
           QVector<int> timeset;
           for(int a=0;a<totalTimes;a++)
           {
               getline(myfile,line);
               timeset.push_back((atoi(line.c_str())));
           }

           users.insert(pair<string,statsfunc*>(name,cur));
       }


    }
    else
    {
        return;
    }
}

void statsWindow::writeStats()
{
    std::ofstream ofs;
    ofs.open("sudoku.sudostat", std::ofstream::out | std::ofstream::trunc);
    unordered_map<string,statsfunc*>::iterator it = users.begin();
    ofs << users.size() << "\n";
    for(;it!=users.end();it++)
    {
        ofs<<it->first<<"\n";

        statsfunc * current = it->second;
        ofs << current->bestTime <<"\n";
        ofs << current->highScore <<"\n";
        ofs << current->scorevec.size()<<"\n";
        for(int x=0;x<current->scorevec.size();x++)
        {
            ofs << current->scorevec[x] <<"\n";
        }
        ofs << current->timevec.size()<<"\n";

        for(int y = 0;y < current->timevec.size();y++)
        {
            ofs <<current->timevec[y]<<"\n";
        }




    }
    ofs.close();
}
