#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include "mainwindow.h"
#include <QWidget>
#include <QVector>

class MainWindow;
class QString;


class statsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit statsWindow(MainWindow *mw = 0,QString name="");
    ~statsWindow();
    static void writeStats();
    static void loadStats();
    int bestTime=0;
    int totalgamesplayed=0;
    int highScore=0;
    QString username;
    QVector<int> scorevec;
    QVector<int> timevec;
    int highscorefunction();
    int besttimefunction();
    int BT();
    int HS();
    void statsfunction(int score, int time);
    void statsupdate(QString name);
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // STATSWINDOW_H
