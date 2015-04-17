#include "leaderboardwindow.h"
#include "statswindow.h"
#include <QLabel>
#include <iostream>

leaderboardWindow::leaderboardWindow(MainWindow *mw)
{

    mainWindow = mw;
    mw->statsWindowObj;
    QGridLayout *buttonlayout = new QGridLayout;
    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    this->setLayout(buttonlayout);
    TP();
    QLabel *label = new QLabel("Leaderboard");
    QFont f( "Courier New", 20, QFont::Bold);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(f);

//    QString str;
//    str.setNum(one);
//    first->setText(str);
//    QFont f2("Courier New", 15);
//    first->setFont(f2);
//    first->setAlignment(Qt::AlignCenter);

//    QString str2;
//    str2.setNum(two);
//    second->setText(str2);
//    second->setFont(f2);
//    second->setAlignment(Qt::AlignCenter);

//    QString str3;
//    str3.setNum(three);
//    third->setText(str3);
//    third->setFont(f2);
//    third->setAlignment(Qt::AlignCenter);


    buttonlayout->addWidget(label);
    buttonlayout->addWidget(first,1,10000);
    buttonlayout->addWidget(second,2,10000);
    buttonlayout->addWidget(third,3,10000);
    buttonlayout->addWidget(firstname,1,0);
    buttonlayout->addWidget(secondname,2,0);
    buttonlayout->addWidget(thirdname,3,0);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet(*style);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void leaderboardWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
leaderboardWindow::~leaderboardWindow()
{

}
void leaderboardWindow::TP()
{

    QVector<int> use = mainWindow->statsWindowObj->getScoreVector();
    QVector<QString> username= mainWindow->statsWindowObj->getNameVector();

    int index1=-1;
    int index2=-1;
    int index3=-1;
    cout<<"tpsize"<<use.size()<<endl;
    if(use.size()>1){
    cout<<"scores: "<<use[0]<<" : "<<use[1]<<endl;}

    one =0;
    two=0;
    three=0;
    for(int i=0;i<use.size();i++)
    {

        if(use.at(i)>one)
        {
            one = use.at(i);
            index1=i;
            cout<<"one "<<one<<":"<<index1<<endl;
            firstname->setText(username.at(index1));
        }
    }
    for(int i=0;i<use.size();i++)
    {
        if(use.size()<2)
            break;

        cout<<"at"<<use[i]<<endl;
        if(use.at(i)>=two && use.at(i)<=one && i!=index1)
        {
            cout<<"in here"<<endl;
            index2=i;
            two = use.at(i);
            secondname->setText(username.at(index2));
            cout<<"twox"<<two<<endl;
        }
    }
    for(int i=0;i<use.size();i++)
    {
        if(use.size()<3)
            break;

        if(use.at(i)>=three && use.at(i)<=two && i!=index2 && i!=index1)
        {
            index3=i;
            three = use.at(i);
            thirdname->setText(username.at(index3));

        }


    }
    QString str = QString::number(one);
    first->setText(str);
    QFont f2("Courier New", 15);
    first->setFont(f2);
    //first->setAlignment(Qt::AlignCenter);

    QString str2 = QString::number(two);
    cout<<"two"<<two<<endl;
    second->setText(str2);
    second->setFont(f2);
  //  second->setAlignment(Qt::AlignCenter);

    QString str3 = QString::number(three);
    third->setText(str3);
    third->setFont(f2);
   // third->setAlignment(Qt::AlignCenter);

    firstname->setFont(f2);
    secondname->setFont(f2);
    thirdname->setFont(f2);
}

