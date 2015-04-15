#ifndef MAINMENU_H
#define MAINMENU_H
#include "mainwindow.h"
#include <QWidget>
#include "statswindow.h"
#include "statsfunc.h"
#include <unordered_map>
class MainWindow;

using namespace std;
class mainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainMenu(MainWindow *mw = 0);
    ~mainMenu();

    void loadStats();
    unordered_map<string,statsfunc *> users;
    void populateStats();

private slots:
    void gotoNewGameMenu();
    void gotoInstrMenu();
    void gotoPuzzleWindow();
    void gotoStatsWindow();
    void gotoLeaderboard();
    void gotoFacebook();

//    void gotoPauseWindow();

private:
    MainWindow *mainWindow;
};

#endif // MAINMENU_H
