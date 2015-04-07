#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H
#include "mainwindow.h"
#include <QWidget>
#include <QVector>

class MainWindow;

class leaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit leaderboardWindow(MainWindow *mw = 0);
    ~leaderboardWindow();
    QVector<int> topscores;
    void TP();
    int one;
    int two;
    int three;

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // LEADERBOARDWINDOW_H
