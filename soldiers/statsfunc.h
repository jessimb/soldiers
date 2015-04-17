#ifndef STATSFUNC_H
#define STATSFUNC_H

#include <QWidget>
class QString;
class statsfunc: public QWidget
{
public:


    double currenttime = 0;
    double currentscore = 0;
    int bestTime = 0;
    int totalgamesplayed = 0;
    int highScore = 0;
    QString username = "";
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
