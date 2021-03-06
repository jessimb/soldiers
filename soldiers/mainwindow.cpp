#include "mainwindow.h"

#include <iostream>
#include <QLabel>

using namespace std;
extern QString globalUser;
QStackedWidget *stackedWidget;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QIcon icon("icon.ico");
    setWindowIcon(icon);
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    mainMenuObj = new mainMenu(this);
    instrMenuObj = new instructionsMenu(this);
    newGameMenuObj = new newGameMenu(this);
    statsWindowObj = new statsWindow(this);
    leaderboardWindowObj = new leaderboardWindow(this);
    pauseWindowObj = new pauseWindow(this);
    winWindowObj = new winWindow(this);


    widget->setStyleSheet("background-color:#FAFAD2;");
    //add your widget here!

    stackedWidget = new QStackedWidget();

    stackedWidget->addWidget(mainMenuObj); //0
    stackedWidget->addWidget(newGameMenuObj); //1
    stackedWidget->addWidget(instrMenuObj); //2
    stackedWidget->addWidget(statsWindowObj); //3
    stackedWidget->addWidget(leaderboardWindowObj); //4
    stackedWidget->addWidget(pauseWindowObj); //5
    stackedWidget->addWidget(winWindowObj);//6


    //add your widget to the stackedWidget


    QGridLayout *layout = new QGridLayout();
    stackedWidget->setMinimumSize(600,600);

   // layout->addWidget(label);
    widget->setLayout(layout);
    string loginstuff= "\t\t\t\t\t\t\tLogged in as: "+globalUser.toStdString();
    usrlabel =new QLabel(QString::fromStdString(loginstuff));
    QFont font;
    font.setBold(true);
    usrlabel->setFont(font);
    layout->addWidget(usrlabel);
    layout->addWidget(stackedWidget);
    stackedWidget->setCurrentWidget(mainMenuObj);
    statsWindow::loadStats();
}


MainWindow::~MainWindow()
{

}
