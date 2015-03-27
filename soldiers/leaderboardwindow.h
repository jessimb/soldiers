#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class leaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit leaderboardWindow(MainWindow *mw = 0);
    ~leaderboardWindow();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // LEADERBOARDWINDOW_H
