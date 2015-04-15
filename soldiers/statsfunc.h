#ifndef STATSFUNC_H
#define STATSFUNC_H

#include <QWidget>
class QString;
class statsfunc: public QWidget
{
public:

    double currenttime;
    double currentscore;
    double bestTime;
    int totalgamesplayed;
    int highScore;
    QString username;
    QVector<int> scorevec;
    QVector<int> timevec;
    int highscorefunc();
    int besttimefunc();
    int BT();
    int HS();
    void statsfunction(int score, int time);
    statsfunc(QString);
};

#endif // STATSFUNC_H
