#include "timeline.h"

Timeline::Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    this->mType = mType;
    this->markingTOF = STOF;
    this->tType = tType;
    this->startTime = 0;
    //Timeline is abstract, timeList needs to be initalized in derived classes
}
Timeline::Timeline(int startTime, int TOT, int TOF, markingType mType, int STOF, timelineType tType)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    this->mType = mType;
    this->markingTOF = STOF;
    this->tType = tType;
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

int Timeline::getMTOF()
{
    return this->markingTOF;
}

markingType Timeline::getMarkingType()
{
    return this->mType;
}

timelineType Timeline::getTimelineType()
{
    return this->tType;
}

std::vector<shell> Timeline::getTimeList()
{
    return this->timeList;
}

void Timeline::print()
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

Standard_Timeline::Standard_Timeline(int TOT, int TOF, markingType mType, int MTOF, timelineType tType): Timeline(TOT, TOF, mType, MTOF, tType)
{
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
        
        
        //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
        //supression is also different, so must use STOF instead of regular TOF.
        Sexagesimal marking;
        switch(mType)
        {
            case ILLUM:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 45);
                if(marking > secondHE && ((marking.getHours() != 0 && secondHE.getHours() != 0) || (marking.getHours() == 0 && secondHE.getHours() == 23)))
                {
                    timeList.push_back(shell{secondHE, true});
                    timeList.push_back(shell{marking, false});
                }
                else
                {
                    timeList.push_back(shell{marking, false});
                    timeList.push_back(shell{secondHE, true});
                }
                
                break;
            case WP:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5 + 30);
                if(marking > secondHE && ((marking.getHours() != 0 && secondHE.getHours() != 0) || (marking.getHours() == 0 && secondHE.getHours() == 23)))
                {
                    timeList.push_back(shell{secondHE, true});
                    timeList.push_back(shell{marking, false});
                }
                else
                {
                    timeList.push_back(shell{marking, false});
                    timeList.push_back(shell{secondHE, true});
                }
                break;
            default:
                timeList.push_back(shell{secondHE, true});
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
                if(marking > secondHE && ((marking.getHours() != 0 && secondHE.getHours() != 0) || (marking.getHours() == 0 && secondHE.getHours() == 23)))
                {
                    timeList.push_back(shell{secondHE, true});
                    timeList.push_back(shell{marking, false});
                }
                else
                {
                    timeList.push_back(shell{marking, false});
                    timeList.push_back(shell{secondHE, true});
                }
                
                break;
            case WP:
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5 + 30);
                if(marking > secondHE && ((marking.getHours() != 0 && secondHE.getHours() != 0) || (marking.getHours() == 0 && secondHE.getHours() == 23)))
                {
                    timeList.push_back(shell{secondHE, true});
                    timeList.push_back(shell{marking, false});
                }
                else
                {
                    timeList.push_back(shell{marking, false});
                    timeList.push_back(shell{secondHE, true});
                }
                break;
        }
    }
    


    return timeList;

}

NonStandard_Timeline::NonStandard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType, std::vector<fireRange> firingRanges, int fireFreq): Timeline(TOT, TOF, mType, STOF, tType)
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
        while(currentTime < (Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0, fr.endMin, 0)) )
        {
            timeList.push_back(shell{currentTime, true});
            currentTime = currentTime + Sexagesimal(0,0,fireFreq);
        }
    }
    return timeList;
}

int main()
{
    // int tot, tof, mtof;
    // mtof = 0;
    // markingType mType;
    // timelineType tType;
    // cout <<"Enter Time on Target" << endl;
    // cin >> tot;
    // cout << "Enter time of fire" << endl;
    // cin >> tof;
    // int marking;
    // cout << "Enter marking type -" << endl << "0 - NONE\n1 - ILLUM\n2 - WP" << endl;
    // cin >> marking;
    // //turns int into enum value
    // mType = static_cast<markingType>(marking);
    // if(mType != NEGATIVE)
    // {
    //     cout <<"Enter marking Time of Flight" << endl;
    //     cin >> mtof;
    // }
    // cout << "Choose timeline type -" << endl << "0 - Continuous\n1 - Interrupted" << endl;
    // int timeline;
    // cin >> timeline;
    // //turns int into enum value
    // tType = static_cast<timelineType>(timeline);
    // Standard_Timeline t = Standard_Timeline(tot, tof, mType, mtof, tType);
    // t.print();
    std::vector<fireRange> frVec;
    frVec.push_back(fireRange{-2, 1});
    frVec.push_back(fireRange{3, 5});
    NonStandard_Timeline nST = NonStandard_Timeline(40, 30, NEGATIVE, 0, CONTINUOUS, frVec, 30);
    nST.print();
}

