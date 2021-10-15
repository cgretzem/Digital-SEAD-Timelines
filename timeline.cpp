#include "timeline.h"

Timeline::Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    this->mType = mType;
    this->supressionTOF = STOF;
    this->tType = tType;
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

int Timeline::getSTOF()
{
    return this->supressionTOF;
}

markingType Timeline::getMarkingType()
{
    return this->mType;
}

timelineType Timeline::getTimelineType()
{
    return this->tType;
}

std::vector<Sexagesimal> Timeline::getTimeList()
{
    return this->timeList;
}

Standard_Timeline::Standard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType): Timeline(TOT, TOF, mType, STOF, tType)
{
    this->timeList = this->makeTimeline();
}

std::vector<Sexagesimal> Standard_Timeline::makeTimeline()
{
    //Need some help here understanding when each round is suppposed to hit
}


//need to fix this method, right now it is the same as standard
NonStandard_Timeline::NonStandard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType): Timeline(TOT, TOF, mType, STOF, tType)
{
    this->timeList = this->makeTimeline();
}

std::vector<Sexagesimal> NonStandard_Timeline::makeTimeline()
{
    //Need some help here understanding when each round is suppposed to hit
}

