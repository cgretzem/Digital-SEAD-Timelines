#include "timeline.h"
#include <algorithm>
#include <string>

using namespace std;

bool shell::operator==(shell rhs)
{
    if (rhs.fireTime == this->fireTime && rhs.mType == this->mType)
        return true;
    return false;
}
bool shell::operator<=(shell rhs)
{
    if (*this == rhs)
        return true;
    return fireTime <= rhs.fireTime;
}
bool shell::operator>=(shell rhs)
{
    if (*this == rhs)
        return true;
    return fireTime >= rhs.fireTime;
}
bool shell::operator<(shell rhs)
{
    if (*this == rhs)
        return true;
    return fireTime < rhs.fireTime;
}
bool shell::operator>(shell rhs)
{
    if (*this == rhs)
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
    if (timeList.empty())
        return;
    sort(timeList.begin(), timeList.end());
}

/*
void Timeline::print()
{
    for (shell s : timeList)
    {
        cout << s.fireTime << " : (HE)" << endl;
    }
}
*/
string Timeline::print(){

    string lineOftime = "";

    //for (shell s : timeList){ cout << s.fireTime << " : (HE)" << endl; }
    for (shell s : timeList){

        lineOftime += s.fireTime.print();
        lineOftime +=  " : (HE)\n";
    }

    return lineOftime;
}


Standard_Timeline::Standard_Timeline(int TOT, int TOF, markingType mType, int MTOF, timelineType tType) : Timeline(TOT, TOF)
{
    this->mType = mType;
    this->markingTOF = MTOF;
    this->tType = tType;
    this->startTime = startTime;
    this->timeList = this->makeTimelist();
}

std::vector<shell> Standard_Timeline::makeTimelist()
{
    if (tType == CONTINUOUS)
    {
        //takes time on target in minutes, subtracts (TOF+5), and a minute because HE 1 hits 1 min before TOT
        Sexagesimal firstHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 1, timeOfFlight + 5);
        timeList.push_back(shell{ firstHE, NEGATIVE });
        //subtracts 30 seconds because HE 2 hits 30 seconds before TOT
        Sexagesimal secondHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, timeOfFlight + 5 + 30);
        timeList.push_back(shell{ secondHE, NEGATIVE });

        //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
        //supression is also different, so must use STOF instead of regular TOF.
        Sexagesimal marking;
        switch (mType)
        {
        case ILLUM:
            marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, markingTOF + 5 + 45);
            timeList.push_back(shell{ marking, mType });
            break;
        case WP:
            //marking not TOF?
            marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, markingTOF + 5 + 30);
            timeList.push_back(shell{ marking, mType });
        case NEGATIVE:
            break;
        }
        //Round is supposed to hit at TOT specified, so just subtract Time of Flight
        Sexagesimal thirdHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, timeOfFlight + 5);
        timeList.push_back(shell{ thirdHE, NEGATIVE });

        //HE round 4 hits at +30, so just subtract time of flight from TOT and then add 30
        Sexagesimal fourthHE = (Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, timeOfFlight + 5)) + Sexagesimal(0, 0, 30);
        timeList.push_back(shell{ fourthHE, NEGATIVE });

        //HE round 4 hits at +1 min, so just subtract time of flight from TOT and then add 1 min
        Sexagesimal fifthHE = (Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, timeOfFlight + 5)) + Sexagesimal(0, 1, 0);
        timeList.push_back(shell{ fifthHE, NEGATIVE });
    }
    else// INTERRUPTED timelineType
    {
        //takes time on target in minutes, subtracts (TOF+5), and a minute because HE 1 hits 1 min before TOT
        Sexagesimal firstHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 1, timeOfFlight + 5);
        timeList.push_back(shell{ firstHE, NEGATIVE });
        //subtracts 30 seconds because HE 2 hits 30 seconds before TOT
        Sexagesimal secondHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, timeOfFlight + 5 + 30);
        timeList.push_back(shell{ secondHE, NEGATIVE });

        //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
        //supression is also different, so must use STOF instead of regular TOF.
        Sexagesimal marking;
        switch (mType)
        {
        case ILLUM:
            marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, markingTOF + 5 + 45);
            timeList.push_back(shell{ marking, mType });
            break;
        case WP:
            marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, markingTOF + 5 + 30);
            timeList.push_back(shell{ marking, mType });
            break;
        case NEGATIVE:
            break;
        }
    }

    //sorting the timeList by fireTime
    sortTimeList();
    return timeList;

}
//void

string Standard_Timeline::print(){

    string otherTimeline = "";

    int countHE = 0;
    int countIllum = 0;
    int countWP = 0;
    int countRounds = 1;
   
    for (shell s : timeList)
    {
        if (s.mType == NEGATIVE) {
            //cout << "Round " << countRounds << ": " << s.fireTime << " : (HE)" << endl;
            otherTimeline += "Round ";
            otherTimeline += to_string(countRounds);
            otherTimeline += ": ";
            otherTimeline += s.fireTime.print();
            otherTimeline += " : (HE)\n";
            countHE++;
            countRounds++;
        }
        else
        {
            if (mType == ILLUM) {
                //cout << "Round " << countRounds << ": " << s.fireTime << " : (ILLUM)" << endl;
                otherTimeline += "Round ";
                otherTimeline += to_string(countRounds);
                otherTimeline += ": ";
                otherTimeline += s.fireTime.print();
                otherTimeline += " : (ILLUM)\n";
                countIllum++;
                countRounds++;
            }
            else {
                //cout << "Round " << countRounds << ": " << s.fireTime << " : (WP)" << endl;
                otherTimeline += "Round ";
                otherTimeline += to_string(countRounds);
                otherTimeline += ": ";
                otherTimeline += s.fireTime.print();
                otherTimeline += " : (WP)\n";
                countWP++;
                countRounds++;
            }
        }
    }
    
    //cout << "\n HE count: " << countHE << endl;
    otherTimeline += " HE count: ";
    otherTimeline += to_string(countHE);
    otherTimeline += "\n";

    //cout << "\n WP count: " << countWP << endl;
    otherTimeline += " WP count: ";
    otherTimeline += to_string(countWP);
    otherTimeline += "\n";

    //cout << "\n ILLUM count: " << countIllum << endl;
    otherTimeline += " ILLUM count: ";
    otherTimeline += to_string(countIllum);
    otherTimeline += "\n";
    //cout << "\n";

    return otherTimeline;
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


NonStandard_Timeline::NonStandard_Timeline(int TOT, int TOF, int MTOF, std::vector<fireRange> firingRanges, int fireFreq) : Timeline(TOT, TOF)
{
    this->markingTOF = MTOF;
    this->startTime = startTime;
    this->fireFreq = fireFreq;
    this->firingRanges = firingRanges;
    this->timeList = this->makeTimelist();
}

std::vector<shell> NonStandard_Timeline::makeTimelist()
{
    Sexagesimal currentTime;
    for (fireRange fr : firingRanges)
    {
        currentTime = Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0, fr.startMin, 0) - Sexagesimal(0, 0, timeOfFlight + 5);
        while (currentTime <= (Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0, fr.endMin, 0) - Sexagesimal(0, 0, timeOfFlight + 5)))
        {
            timeList.push_back(shell{ currentTime, NEGATIVE });
            currentTime = currentTime + Sexagesimal(0, 0, fireFreq);
        }
    }

    //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
    //supression is also different, so must use STOF instead of regular TOF.
    // Sexagesimal marking;
    // switch (mType)
    // {
    // case ILLUM:
    //     marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, markingTOF + 5 + 45);
    //     timeList.push_back(shell{ marking, false });
    //     break;
    // case WP:
    //     //marking not TOF?
    //     marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0, 0, markingTOF + 5 + 30);
    //     timeList.push_back(shell{ marking, false });
    // case NEGATIVE:
    //     break;
    // }

    sortTimeList();
    return timeList;
}

void NonStandard_Timeline::addFireRange(fireRange newFR)
{
    Sexagesimal currentTime = Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0, newFR.startMin, 0) - Sexagesimal(0, 0, timeOfFlight + 5);
    while (currentTime <= (Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0, newFR.endMin, 0) - Sexagesimal(0, 0, timeOfFlight + 5)))
    {
        timeList.push_back(shell{ currentTime, NEGATIVE });
        currentTime = currentTime + Sexagesimal(0, 0, fireFreq);
    }
    sortTimeList();
}

void NonStandard_Timeline::addMarkingRound(markingType mType, int markingTOT)
{

    Sexagesimal marking = Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0,0, markingTOF - 5 - markingTOT);
    timeList.push_back(shell{marking, mType});
    sortTimeList();
}

string NonStandard_Timeline::print()
{
    int countHE = 0;
    int countIllum = 0;
    int countWP = 0;
    int countRounds = 1;

    string otherTimeline = "";

    for (shell s : timeList)
    {
        if (s.mType == NEGATIVE) {
            //cout << "Round "<<countRounds<<": " << s.fireTime << " : (HE)" << endl;
            otherTimeline += "Round ";
            otherTimeline += to_string(countRounds);
            otherTimeline += ": ";
            otherTimeline += s.fireTime.print();
            otherTimeline += " : (HE)\n";
            countHE++;
            countRounds++;

        }
        else
        {
            if (s.mType == ILLUM) {
                //cout << "Round " << countRounds << ": " << s.fireTime << " : (ILLUM)" << endl;
                otherTimeline += "Round ";
                otherTimeline += to_string(countRounds);
                otherTimeline += ": ";
                otherTimeline += s.fireTime.print();
                otherTimeline += " : (ILLUM)\n";
                countIllum++;
                countRounds++;
            }
            else {
                //cout << "Round " << countRounds << ": " << s.fireTime << " : (WP)" << endl;
                otherTimeline += "Round ";
                otherTimeline += to_string(countRounds);
                otherTimeline += ": ";
                otherTimeline += s.fireTime.print();
                otherTimeline += " : (WP)\n";
                countWP++;
                countRounds++;
            }
        }
    }
    //cout << "\n HE count: " << countHE << endl;
    otherTimeline += " HE count: ";
    otherTimeline += to_string(countHE);
    otherTimeline += "\n";

    //cout << "\n WP count: " << countWP << endl;
    otherTimeline += " WP count: ";
    otherTimeline += to_string(countWP);
    otherTimeline += "\n";

    //cout << "\n ILLUM count: " << countIllum << endl;
    otherTimeline += " ILLUM count: ";
    otherTimeline += to_string(countIllum);
    otherTimeline += "\n";

    //cout << "\n";

  return otherTimeline;
}

int NonStandard_Timeline::getMTOF()
{
    return this->markingTOF;
}
