#ifndef STATSWINDOW_H
#define STATSWINDOW_H

#include "mainwindow.h"
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <vector>

class MainWindow;
class QString;

using namespace std;
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
    QLabel *highscorelabel = new QLabel;
    QLabel *besttimelabel = new QLabel;
    int highscorefunction();
    int besttimefunction();
    int BT();
    int HS();
    void statsfunction(int score, int time);
    void updatestats(QString name);

    QVector<int> getScoreVector();
    QVector<string> getNameVector();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // STATSWINDOW_H
