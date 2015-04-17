#include "statsfunc.h"

statsfunc::statsfunc(QString nm)
{
    username = nm;
}

void statsfunc::statsfunction(int score, int time)
{
    currentscore=score;
    scorevec.push_back(currentscore);
    totalgamesplayed++;
    currenttime=time;
    timevec.push_back(currenttime);
    highScore=highscorefunc();
    bestTime=besttimefunc();
}

int statsfunc::highscorefunc()
{
    highScore=0;
    for(int i=0;i<scorevec.size();i++)
    {

        if(scorevec.at(i)>highScore)
        {
            highScore=scorevec.at(i);
        }
    }
    if(totalgamesplayed == 0)
        return 0;
    int HS=highScore;
    return HS;
}
int statsfunc::besttimefunc()
{
    bestTime=9999999999;
    for(int i=0;i<timevec.size();i++)
    {
        if(timevec.at(i)<bestTime)
        {
            bestTime=timevec.at(i);
        }
    }
    int BT=bestTime;
    return BT;
}
