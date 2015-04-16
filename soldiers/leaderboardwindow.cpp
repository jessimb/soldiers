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
    buttonlayout->addWidget(first);
    buttonlayout->addWidget(second);
    buttonlayout->addWidget(third);
  //  buttonlayout->addWidget(firstname,1,0);
   // buttonlayout->addWidget(secondname,2,0);
   // buttonlayout->addWidget(thirdname,3,0);

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
    cout<<"IN TP PS HELLA JANK"<<endl;
//    int pos=0;
//    string temp;
//    QVector<QString> namevec;
//    namevec=mainWindow->statsWindowObj->getNameVector();
//    topscores=mainWindow->statsWindowObj->getScoreVector();

    for(int i=0;i<mainWindow->statsWindowObj->scorevec.size();i++)
    { cout<<"in loop"<<endl;
        if(mainWindow->statsWindowObj->scorevec.at(i)>one)
        {
            one = mainWindow->statsWindowObj->scorevec.at(i);

            //firstname->setText(namevec.at(i));
        }
    }
    for(int i=0;i<mainWindow->statsWindowObj->scorevec.size();i++)
    {
        if(mainWindow->statsWindowObj->scorevec.at(i)>two)
        {
            two = mainWindow->statsWindowObj->scorevec.at(i);
            if(two>=one)
            {
                two=0;
            }
         }
    }
    for(int i=0;i<mainWindow->statsWindowObj->scorevec.size();i++)
    {
        if(mainWindow->statsWindowObj->scorevec.at(i)>three)
        {
            three = mainWindow->statsWindowObj->scorevec.at(i);
            if(three>=two)
            {
                three=0;
            }
        }
    }
    QString str = QString::number(one);
    first->setText(str);
    QFont f2("Courier New", 15);
    first->setFont(f2);
    first->setAlignment(Qt::AlignCenter);

    QString str2 = QString::number(two);
    second->setText(str2);
    second->setFont(f2);
    second->setAlignment(Qt::AlignCenter);

    QString str3 = QString::number(three);
    third->setText(str3);
    third->setFont(f2);
    third->setAlignment(Qt::AlignCenter);
}

