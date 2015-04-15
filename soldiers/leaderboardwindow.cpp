#include "leaderboardwindow.h"
#include "statswindow.h"
#include <QLabel>

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

    QString str;
    str.setNum(one);
    QLabel *first = new QLabel;
    first->setText(str);
    QFont f2("Courier New", 15);
    first->setFont(f2);
    first->setAlignment(Qt::AlignCenter);

    QString str2;
    str2.setNum(two);
    QLabel *second = new QLabel;
    second->setText(str2);
    second->setFont(f2);
    second->setAlignment(Qt::AlignCenter);

    QString str3;
    str3.setNum(three);
    QLabel *third = new QLabel;
    third->setText(str3);
    third->setFont(f2);
    third->setAlignment(Qt::AlignCenter);

    buttonlayout->addWidget(label);
    buttonlayout->addWidget(first);
    buttonlayout->addWidget(second);
    buttonlayout->addWidget(third);

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
    topscores=mainWindow->statsWindowObj->getScoreVector();

    for(int i=0;i<topscores.size()-1;i++)
    {
        if(topscores.at(i)>one)
        {
            one = topscores.at(i);
        }
    }
    for(int i=0;i<topscores.size()-1;i++)
    {
        if(topscores.at(i)>two && two<one)
        {
            two = topscores.at(i);
        }
    }
    for(int i=0;i<topscores.size()-1;i++)
    {
        if(topscores.at(i)>three && three<two)
        {
            three = topscores.at(i);
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

