#ifndef MAINMENU_H
#define MAINMENU_H
#include "mainwindow.h"
#include <QWidget>
#include "statswindow.h"
#include "statsfunc.h"
#include <tr1/unordered_map>
class MainWindow;
class QString;
#include <QString>
using namespace std::tr1;
class mainMenu : public QWidget
{
    Q_OBJECT

public:
    static QString globalUser;
    explicit mainMenu(MainWindow *mw = 0);
    ~mainMenu();

    void loadStats();

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
