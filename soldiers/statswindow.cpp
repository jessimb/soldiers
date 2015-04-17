#include "statswindow.h"
#include "statsfunc.h"
#include <QLabel>
#include <QDebug>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <QDir>
using namespace std;

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
    highscorelabel->setText(str);
    QFont f2("Courier New", 15);
    highscorelabel->setFont(f2);

    QString str2;
    str2.setNum(averageBS);
    besttimelabel->setText(str2);
    besttimelabel->setFont(f2);

    buttonlayout->addWidget(label);
    buttonlayout->addWidget(score,1,0);
    buttonlayout->addWidget(highscorelabel,1,10000);
    buttonlayout->addWidget(time,2,0);
    buttonlayout->addWidget(besttimelabel,2,10000);
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
void statsWindow::updatestats(QString name)
{
    if(users.find(name.toStdString())==users.end())
        return;
    statsfunc* currentUser = users.find(name.toStdString())->second;
    bestTime=currentUser->bestTime;
    totalgamesplayed=currentUser->totalgamesplayed;
    highScore=currentUser->highScore;
    scorevec=currentUser->scorevec;
    timevec=currentUser->timevec;

    int averageHS= highscorefunction();
    int averageBS= besttimefunction();

    QString str=QString::number(averageHS);

    cout<<"setting string\n"<<str.toStdString()<<endl;
    highscorelabel->setText(str);
    QFont f2("Courier New", 15);
    highscorelabel->setFont(f2);

    QString str2= QString::number(averageBS);

    besttimelabel->setText(str2);
    besttimelabel->setFont(f2);

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
    int HS=highScore;
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
    int BT=bestTime;
    return BT;
}

void statsWindow::loadStats()
{

    string pathdet=QDir::homePath().toStdString()+"/sudoku.stat";
    cout<<"path details\n"<<pathdet<<endl;
    ifstream myfile(pathdet);

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
           cout<<"loading best time: "<<cur->bestTime<<endl;

           getline(myfile,line);
           cur->highScore = atoi(line.c_str());
           cout<<"loading best score: "<<cur->highScore<<endl;

           getline(myfile,line);
           int totalScores = atoi(line.c_str());
           cout<<"num scores: "<<totalScores<<endl;
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
    cout<<"writing stats sudostat"<<endl;
    string filewrite=QDir::homePath().toStdString()+"/sudoku.stat";
    cout<<"string to write "<<filewrite<<endl;
    std::ofstream ofs(filewrite,std::ios::out,std::ios::trunc);
    unordered_map<string,statsfunc*>::iterator it = users.begin();
    char b0[50];
    char b1[50];
    char b2[50];
    char b3[50];
    char b4[50];
    char b5[50];
    string totalstring="";
    string usrstr = string(itoa(users.size(),b0,10))+ "\n";
    totalstring+=usrstr;
    cout<<"users.size() "<<users.size()<<endl;
    for(;it!=users.end();it++)
    {
        cout<<"is open"<< ofs.is_open() <<" brr\n";

        totalstring +=it->first+"\n";
        cout<< "tstring="<<totalstring;

        statsfunc * current = it->second;
        totalstring+=string(itoa(current->bestTime,b1,10))+"\n";
        totalstring+=string(itoa(current->highScore,b2,10)) +"\n";
        totalstring+=string(itoa(current->scorevec.size(),b3,10))+"\n";
        cout<<"btime "<<current->bestTime<<endl;
        cout<<"hstime "<<current->highScore<<endl;
        cout<<current->scorevec.size()<<endl;
        cout<<current->timevec.size()<<endl;
        for(int x=0;x<current->scorevec.size();x++)
        {
            char b6[50];
            totalstring+=string(itoa(current->scorevec[x],b6,10)) +"\n";
        }
        totalstring+= string(itoa(current->timevec.size(),b4,10))+"\n";

        for(int y = 0;y < current->timevec.size();y++)
        {
            char b7[50];
            cout<<"vec checking "<<current->timevec[y]<<endl;
            totalstring+=string(itoa(current->timevec[y],b7,10))+"\n";
        }




    }
    cout<<"tstring\n\n\n"<<totalstring<<endl;
    cout<<"size "<<totalstring.size()<<endl;
    ofs.write(totalstring.c_str(),totalstring.size());
    cout<<"closed"<<endl;

    ofs.close();
}

QVector<int> statsWindow::getScoreVector()
{
    QVector<int> scvec;
    for(auto it =users.begin();it!=users.end();it++)
    {
        statsfunc * current= it->second;
        scvec.push_back(current->highScore);
    }
    return scvec;
}

QVector<QString> statsWindow::getNameVector()
{
    QVector<QString> scvec;
    for(auto it =users.begin();it!=users.end();it++)
    {

        //scvec.push_back(it->first);
    }
    return scvec;
}

