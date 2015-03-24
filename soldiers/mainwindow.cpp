#include "mainwindow.h"
#include <iostream>
#include <QLabel>

using namespace std;

QStackedWidget *stackedWidget;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    mainMenuObj = new mainMenu();
    instrMenuObj = new instructionsMenu();
    newGameMenuObj = new newGameMenu();

    stackedWidget = new QStackedWidget();

    stackedWidget->addWidget(mainMenuObj); //0
    stackedWidget->addWidget(newGameMenuObj); //1
    stackedWidget->addWidget(instrMenuObj); //2


    QGridLayout *layout = new QGridLayout();
    QLabel *label = new QLabel("mainWindow");
    layout->addWidget(stackedWidget);
    layout->addWidget(label);
     widget->setLayout(layout);

//    layout->addWidget(stackedWidget);
    //setLayout(layout);

//    layout->addWidget(mainMenuObj);
//    layout->addWidget(instrMenuObj);
//    layout->addWidget(newGameMenuObj);

//    mainMenuObj->hide();
//    instrMenuObj->hide();
//    newGameMenuObj->hide();


//    mainMenuObj->show();
//    setCentralWidget(mainMenuObj);
    stackedWidget->setCurrentWidget(mainMenuObj);
   // cout << stackedWidget->currentIndex();
}


MainWindow::~MainWindow()
{

}
