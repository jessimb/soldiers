#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "instructionsmenu.h"
#include "mainmenu.h"
#include "newgamemenu.h"
#include <QStackedWidget>
#include <QGridLayout>
#include <QWidget>

#include <QMainWindow>
class mainMenu;
class instructionsMenu;
class newGameMenu;

extern QStackedWidget *stackedWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    QStackedWidget *stackedWidget;

private:
    mainMenu *mainMenuObj;
    instructionsMenu *instrMenuObj;
    newGameMenu *newGameMenuObj;


private slots:

};

#endif // MAINWINDOW_H
