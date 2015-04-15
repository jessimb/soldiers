#include "statsfunc.h"

statsfunc::statsfunc(QString nm)
{
    username = nm;
}

void statsfunc::statsfunction(int score, int time)
{
    currentscore=score;
    scorevec.push_front(currentscore);
    totalgamesplayed++;
    currenttime=time;
    timevec.push_front(currenttime);
}

int statsfunc::highscorefunc()
{
    highScore=0;
    for(int i=0;i<scorevec.size()-1;i++)
    {

        if(scorevec.at(i)>highScore)
        {
            highScore=scorevec.at(i);
        }
    }
    if(totalgamesplayed == 0)
        return 0;
    int HS=highScore/totalgamesplayed;
    return HS;
}
int statsfunc::besttimefunc()
{
    bestTime=0;
    for(int i=0;i<timevec.size()-1;i++)
    {
        if(timevec.at(i)>bestTime)
        {
            bestTime=timevec.at(i);
        }
    }
    int BT=bestTime/totalgamesplayed;
    return BT;
}
