#include "timeline.h"

Timeline::Timeline(int TOT, int TOF)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    //Timeline is abstract, timeList needs to be initalized in derived classes
}
Timeline::Timeline(int startTime, int TOT, int TOF)
{
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    
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

void Timeline::print()
{
    for(shell s : timeList)
    {
        cout << s.fireTime << " : (HE)" << endl;
    }
}

Standard_Timeline::Standard_Timeline(int TOT, int TOF, markingType mType, int MTOF, timelineType tType): Timeline(startTime, TOT, TOF)
{
    this->startTime = 0;     // no idea why this was starting at 2 ??
    this->TOT = TOT;             //---
    this->supressionTOF = TOF;  // couldnt figure how this was randomizing each run
    this->mType = mType;
    this->markingTOF = MTOF;
    this->tType = tType;
    //this->startTime = startTime;
    this->timeList = this->makeTimelist(); // calling this function first without the variables being set
}

std::vector<shell> Standard_Timeline::makeTimelist()
{
    if(tType == CONTINUOUS)
    {
        //cout<<": ) continuous"<<endl;
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
                //cout<<" : ) illum"<<endl;
		marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 45);
                if(marking > secondHE)
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
                //cout<<" : ) whtPhos"<<endl;
		//markingTOF instead of TOT
		marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 30);
                if(marking > secondHE)
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
                //cout<<" : ) no mark"<<endl;
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
        //cout<<" : ) interupted"<<endl;
	//takes time on target in minutes, subtracts (TOF+5), and a minute because HE 1 hits 1 min before TOT
        Sexagesimal firstHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,1,timeOfFlight+5);
        timeList.push_back(shell{firstHE, true});
        //subtracts 30 seconds because HE 2 hits 30 seconds before TOT
        Sexagesimal secondHE = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,timeOfFlight+5 + 30);
        //timeList.push_back(shell{secondHE, true});
	//this is double in the timelist for some reason 
	//think beacuse we are pushing here
	//and then pushing in the switch case
	//added default to add to end instead of here
        
        //puts a marking round into the list if one is specified, -45 for illum and -30 for wp. Time of flight for
        //supression is also different, so must use STOF instead of regular TOF.
        Sexagesimal marking;
        switch(mType)
        {
            case ILLUM:
                //cout<<" :) illum"<<endl;
		marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 45);
                if(marking > secondHE)
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
		//cout<<" :) Wht Phos"<<endl;
		//markingTOF instead of CAS TOT
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 30);
                if(marking > secondHE)
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
		timeList.push_back(shell{secondHE, true}); // add to timelist if default
		break;
        }
    }
    


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

NonStandard_Timeline::NonStandard_Timeline(int TOT, int TOF, markingType mType, int MTOF, std::vector<fireRange> firingRanges, int fireFreq): Timeline(TOT, TOF)
{
    this->startTime = 0;        //added the same as standard
    this->TOT = TOT;
    this->supressionTOF = TOF;
    this->mType = mType;
    this->markingTOF = MTOF;
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
   
    //working on the ability to add marking rounds if needed for different frequencies of rounds//
    Sexagesimal marking;
    currentTime2 = Sexagesimal(startTime, timeOnTarget, 0) + Sexagesimal(0,fr.startMin, 0) - Sexagesimal(0, 0, timeOfFlight+5);
        switch(mType)
        {
            case ILLUM:
                //cout<<" :) illum"<<endl;
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 45);
		
		if(marking > secondHE)
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
                //cout<<" :) Wht Phos"<<endl;
                //markingTOF instead of CAS TOT
                marking = Sexagesimal(startTime, timeOnTarget, 0) - Sexagesimal(0,0,markingTOF+5 + 30);
                timeList.push_back(shell{marking, false});
		/*
		if(marking > secondHE)
                {
                    timeList.push_back(shell{secondHE, true});
                    timeList.push_back(shell{marking, false});
                }
                else
                {
                    timeList.push_back(shell{marking, false});
                    timeList.push_back(shell{secondHE, true});
                }
		*/
                break;
            
	    case NEGATIVE:
                //timeList.push_back(shell{secondHE, true}); // add to timelist if default
                break;
        }
    
    return timeList;
}

int main()
{
   
    cout<<"Standard example 1"<<endl;	
    markingType mType0 = ILLUM;
    timelineType tType0 = CONTINUOUS;
    Standard_Timeline t0 = Standard_Timeline(15, 25, mType0, 30, tType0);
    t0.print();

    cout<<"Standard example 2"<<endl;
    markingType mType1 = WP;
    timelineType tType1 = INTERRUPTED;
    Standard_Timeline t1 = Standard_Timeline(20, 31, mType1, 40, tType1);
    t1.print();

    cout<<"Non-Standard example 3"<<endl;
    std::vector<fireRange> frVec;
    frVec.push_back(fireRange{-2, 1}); // 1 - (-2) = 3 min interval
    //cout<<"gap"<<endl;               // 3 - 1 = 2 min interval
    frVec.push_back(fireRange{3, 5}); // 5 - 3 = 2 min interval

    NonStandard_Timeline nST = NonStandard_Timeline(40, 30, ILLUM, 240, frVec, 30);
    nST.print();

}
