#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "instructionsmenu.h"
#include "mainmenu.h"
#include "newgamemenu.h"
#include "puzzlewindow.h"
#include <QStackedWidget>
#include <QGridLayout>
#include <QWidget>
#include <QMainWindow>

class mainMenu;
class instructionsMenu;
class newGameMenu;
class puzzleWindow;
//add your class here

extern QStackedWidget *stackedWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    puzzleWindow *puzzleWindowObj;
private:
    mainMenu *mainMenuObj;
    instructionsMenu *instrMenuObj;
    newGameMenu *newGameMenuObj;

    //add your widget here


private slots:

};

#endif // MAINWINDOW_H
