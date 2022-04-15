#ifndef GUN_H
#define GUN_H
#include <timeline.h>
#include <iostream>
#include <QString>

using namespace std;

class Gun
{
public:
    Gun();

    //accessors
    int getTOT();
    int getTOF();
    int getMarkingRound();
    int getMarkingTOF();
    int getFireFreq();
    int getFireType();
    vector<fireRange> getFireVec();
    QString getTimeline();

    //mutators
    void setTOT(int TOT);
    void setTOF(int TOF);
    void setMarkingRound(int markingRound);
    void setMarkingTOF(int markingTOF);
    void setFireFreq(int fireFreq);
    void setFireType(int fireType);
    void setFireVec(vector<fireRange> fireVec);
    void setTimeline(QString timeline);

private:
    int TOF;
    int TOT;
    int markingRound;                   //0: negative   1: illum    2: WP
    int markingTOF;
    int fireFreq;                       //0 if not non-standard firing
    int fireType;
    std::vector<fireRange> fireVec;     //vector of all firing ranges added
    QString timeline;
};

#endif // GUN_H
