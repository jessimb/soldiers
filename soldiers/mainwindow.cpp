#include "mainwindow.h"
#include <iostream>
#include <QLabel>

using namespace std;

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
    QLabel *label = new QLabel("mainWindow");
    stackedWidget->setMinimumSize(500,500);
    layout->addWidget(stackedWidget);
   // layout->addWidget(label);
    widget->setLayout(layout);

    stackedWidget->setCurrentWidget(mainMenuObj);
}


MainWindow::~MainWindow()
{

}
