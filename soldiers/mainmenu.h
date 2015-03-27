#ifndef MAINMENU_H
#define MAINMENU_H
#include "mainwindow.h"
#include <QWidget>

class MainWindow;


class mainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainMenu(MainWindow *mw = 0);
    ~mainMenu();

private slots:
    void gotoNewGameMenu();
    void gotoInstrMenu();
    void gotoPuzzleWindow();
    void gotoStatsWindow();
    void gotoLeaderboard();
//    void gotoPauseWindow();

private:
    MainWindow *mainWindow;
};

#endif // MAINMENU_H
