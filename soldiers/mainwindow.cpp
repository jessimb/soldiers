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
    puzzleWindowObj = new puzzleWindow();
    //add your widget here!

    stackedWidget = new QStackedWidget();

    stackedWidget->addWidget(mainMenuObj); //0
    stackedWidget->addWidget(newGameMenuObj); //1
    stackedWidget->addWidget(instrMenuObj); //2
    stackedWidget->addWidget(puzzleWindowObj); //3
    //add your widget to the stackedWidget


    QGridLayout *layout = new QGridLayout();
    QLabel *label = new QLabel("mainWindow");
    layout->addWidget(stackedWidget);
    layout->addWidget(label);
     widget->setLayout(layout);

    stackedWidget->setCurrentWidget(mainMenuObj);
}


MainWindow::~MainWindow()
{

}
