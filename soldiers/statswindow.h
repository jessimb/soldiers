#ifndef STATSWINDOW_H
#define STATSWINDOW_H
#include "mainwindow.h"
#include <QWidget>
#include <QVector>

class MainWindow;

class statsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit statsWindow(MainWindow *mw = 0);
    ~statsWindow();
    double currenttime;
    double currentscore;
    QString username;//passed
    double bestTime;
    int totalgamesplayed;
    int highScore;
    QVector<int> scorevec;
    QVector<int> timevec;
    int BT();
    int HS();
    int statsfunction(int score, int time);
private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // STATSWINDOW_H
