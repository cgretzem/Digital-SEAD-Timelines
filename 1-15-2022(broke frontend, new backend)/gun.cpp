#include "gun.h"

Gun::Gun()
{
    this->markingRound = -1;
    this->fireType = 0;
}

int Gun::getTOT(){
    return TOT;
}

int Gun::getTOF(){
    return TOF;
}

int Gun::getMarkingRound(){
    return markingRound;
}

int Gun::getMarkingTOF(){
    return markingTOF;
}

int Gun::getFireFreq(){
    return fireFreq;
}

int Gun::getFireType(){
    return fireType;
}

vector<fireRange> Gun::getFireVec(){
    return fireVec;
}

QString Gun::getTimeline(){
    return timeline;
}

void Gun::setTOT(int TOT){
    this->TOT = TOT;
}

void Gun::setTOF(int TOF){
    this->TOF = TOF;
}

void Gun::setMarkingRound(int markingRound){
    this->markingRound = markingRound;
}

void Gun::setMarkingTOF(int markingTOF){
    this->markingTOF = markingTOF;
}

void Gun::setFireFreq(int fireFreq){
    this->fireFreq = fireFreq;
}

void Gun::setFireType(int fireType){
    this->fireType = fireType;
}

void Gun::setFireVec(vector<fireRange> fireVec){
    this->fireVec = fireVec;
}

void Gun::setTimeline(QString timeline){
    this->timeline = timeline;
}
