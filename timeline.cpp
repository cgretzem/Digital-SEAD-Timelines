#include "timeline.h"
#include <algorithm>
using namespace std;

bool shell::operator==(shell rhs)
{
    if(rhs.fireTime == this->fireTime && rhs.isHE == this->isHE)
        return true;
    return false;
}
bool shell::operator<=(shell rhs)
{
    if(*this == rhs)
        return true;
    return fireTime <= rhs.fireTime;
}
bool shell::operator>=(shell rhs)
{
    if(*this == rhs)
        return true;
    return fireTime >= rhs.fireTime;
}
bool shell::operator<(shell rhs)
{
    if(*this == rhs)
        return true;
    return fireTime < rhs.fireTime;
}
bool shell::operator>(shell rhs)
{
    if(*this == rhs)
        return true;
    return fireTime > rhs.fireTime;
}



Timeline::Timeline(int TOT, int TOF)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    this->startTime = 0;
    //Timeline is abstract, timeList needs to be initalized in derived classes
}
Timeline::Timeline(int startTime, int TOT, int TOF)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    this->startTime = startTime;
    
    //Timeline is abstract, timeList needs to be initalized in derived classes
}

int Timeline::getTOT()
{
    return this->timeOnTarget;
}

int Timeline::getTOF()
{
    return this->timeOfFlight;
}


std::vector<shell> Timeline::getTimeList()
{
    return this->timeList;
}

void Timeline::sortTimeList()
{
    if(timeList.empty())
        return;
    sort(timeList.begin(), timeList.end());
}

void Timeline::print()
{
    for(shell s : timeList)
    {
        cout << s.fireTime << " : (HE)" << endl;
    }
}

Standard_Timeline::Standard_Timeline(int TOT, int TOF, markingType mType, int MTOF, timelineType tType): Timeline(TOT, TOF)
{
    this->mType = mType;
    this->markingTOF = MTOF;
    this->tType = tType;
    this->startTime = startTime;
    this->timeList = this->makeTimelist();
}

std::vector<shell> Standard_Timeline::makeTimelist()
{
    if(tType == CONTINUOUS)
    {
        //takes time on target in minutes, subtracts (TOF+5), and a minute because HE 1 hits 1 min before TOT
        Sexagesimal firstHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,1,timeOfFlight+5);
        timeList.push_back(shell{firstHE, true});
        //subtracts 30 seconds because HE 2 hits 30 seconds before TOT
        Sexagesimal secondHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5 + 30);
        timeList.push_back(shell{secondHE, true});
        
        //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
        //supression is also different, so must use STOF instead of regular TOF.
        Sexagesimal marking;
        switch(mType)
        {
            case ILLUM:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 45);
                timeList.push_back(shell{marking, false});
                break;
            case WP:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5 + 30);
                timeList.push_back(shell{marking, false});
            case NEGATIVE:
                break;
        }
        //Round is supposed to hit at TOT specified, so just subtract Time of Flight
        Sexagesimal thirdHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5);
        timeList.push_back(shell{thirdHE, true});

        //HE round 4 hits at +30, so just subtract time of flight from TOT and then add 30
        Sexagesimal fourthHE = (Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5)) + Sexagesimal(0,0,30);
        timeList.push_back(shell{fourthHE, true});

        //HE round 4 hits at +1 min, so just subtract time of flight from TOT and then add 1 min
        Sexagesimal fifthHE = (Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5)) + Sexagesimal(0,1,0);
        timeList.push_back(shell{fifthHE, true});
    }
    else// INTERRUPTED timelineType
    {
        //takes time on target in minutes, subtracts (TOF+5), and a minute because HE 1 hits 1 min before TOT
        Sexagesimal firstHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,1,timeOfFlight+5);
        timeList.push_back(shell{firstHE, true});
        //subtracts 30 seconds because HE 2 hits 30 seconds before TOT
        Sexagesimal secondHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5 + 30);
        timeList.push_back(shell{secondHE, true});
        
        //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
        //supression is also different, so must use STOF instead of regular TOF.
        Sexagesimal marking;
        switch(mType)
        {
            case ILLUM:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 45);
                timeList.push_back(shell{marking, false});
                break;
            case WP:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 30);
                timeList.push_back(shell{marking, false});
                break;
            case NEGATIVE:
                break;
        }
    }
    
    //sorting the timeList by fireTime
    sortTimeList();
    return timeList;

}

void Standard_Timeline::print()
{
    for(shell s : timeList)
    {
        if(s.isHE)
            cout << s.fireTime << " : (HE)" << endl;
        else
        {
            if(mType == ILLUM)
                cout << s.fireTime << " : (ILLUM)" << endl;
            else
                cout << s.fireTime << " : (WP)" << endl;
        }
    }
}

int Standard_Timeline::getMTOF()
{
    return this->markingTOF;
}

markingType Standard_Timeline::getMarkingType()
{
    return this->mType;
}

timelineType Standard_Timeline::getTimelineType()
{
    return this->tType;
}

NonStandard_Timeline::NonStandard_Timeline(int TOT, int TOF, std::vector<fireRange> firingRanges, int fireFreq): Timeline(TOT, TOF)
{
    this->fireFreq = fireFreq;
    this->firingRanges = firingRanges;
    this->timeList = this->makeTimelist();
}

std::vector<shell> NonStandard_Timeline::makeTimelist()
{
    Sexagesimal currentTime;
    for(fireRange fr : firingRanges)
    {
        currentTime = Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0,fr.startMin, 0) - Sexagesimal(0, 0, timeOfFlight+5);
        while(currentTime <= (Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0, fr.endMin, 0)- Sexagesimal(0, 0, timeOfFlight+5)) )
        {
            timeList.push_back(shell{currentTime, true});
            currentTime = currentTime + Sexagesimal(0,0,fireFreq);
        }
    }
    return timeList;
}

