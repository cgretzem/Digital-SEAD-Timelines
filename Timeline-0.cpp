//getting input from user//
#include "timeline.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<fstream>
#include<iostream>

Timeline::Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType){
    
    this->timeOnTarget = TOT;
    this->timeOfFlight = TOF;
    this->mType = mType;
    this->supressionTOF = STOF;
    this->tType = tType;
    //Timeline is abstract, timeList needs to be initalized in derived classes
}

int Timeline::getTOT(){ return this->timeOnTarget; }

int Timeline::getTOF(){ return this->timeOfFlight; }

int Timeline::getSTOF(){ return this->supressionTOF; }

markingType Timeline::getMarkingType(){ return this->mType; }

timelineType Timeline::getTimelineType(){ return this->tType; }


std::vector<Sexagesimal> Timeline::getTimeList(){ return this->timeList; }





Standard_Timeline::Standard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType): Timeline(TOT, TOF, mType, STOF, tType){
       	this->timeList = this->makeTimeline();
}


std::vector<Sexagesimal> Standard_Timeline::makeTimeline(){

return this->makeTimeline();    
    //Need some help here understanding when each round is suppposed to hit
}






/*

//need to fix this method, right now it is the same as standard
NonStandard_Timeline::NonStandard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType): Timeline(TOT, TOF, mType, STOF, tType){
       	this->timeList = this->makeTimeline();
}


std::vector<Sexagesimal> NonStandard_Timeline::makeTimeline(){
    //Need some help here understanding when each round is suppposed to hit
return this->makeTimeline();
}

*/


void illum(int tot, int tof){

    int TOT_HIT = (((tot * 60) - 45) - (tof + 5));
    int MIN = TOT_HIT / 60;
    int SEC = TOT_HIT % 60;
    cout<<"Min: "<<MIN<<" Sec: "<<SEC<<endl;

}


void whtPhos(int tot, int tof){

    int TOT_HIT = (((tot * 60) - 30) - (tof + 5));
    int MIN = TOT_HIT / 60;
    int SEC = TOT_HIT % 60;
    cout<<"Min: "<<MIN<<" Sec: "<<SEC<<endl;

}


void negative(){

//goes to negative reguardless??

}


void mkContinious(int tot, int stof){

 int TOT_HIT = ((tot * 60) - (stof + 5));
 int MIN = TOT_HIT / 60;
 int SEC = TOT_HIT % 60;

 cout<<"Min: "<<(MIN-1)<<" Sec: "<<SEC<<endl;

 if(stof >= 30){ cout<<"Min: "<<(MIN-1)<<" Sec: "<<(SEC+30)<<endl; }
 else{ cout<<"Min: "<<MIN<<" Sec: "<<(SEC-30)<<endl; }

 cout<<"Min: "<<MIN<<" Sec: "<<SEC<<endl;

 if(stof < 30){ cout<<"Min: "<<(MIN+1)<<" Sec: "<<(SEC-30)<<endl; }
 else{ cout<<"Min: "<<MIN<<" Sec: "<<(SEC+30)<<endl; }

 cout<<"Min: "<<(MIN+1)<<" Sec: "<<SEC<<endl;

}


void mkInterrupted(int tot, int stof){

 int TOT_HIT = ((tot * 60) - (stof + 5));
 int MIN = TOT_HIT / 60;
 int SEC = TOT_HIT % 60;

 cout<<"Min: "<<(MIN-1)<<" Sec: "<<SEC<<endl;

 if(stof >= 30){ cout<<"Min: "<<(MIN-1)<<" Sec: "<<(SEC+30)<<endl; }
 else{ cout<<"Min: "<<MIN<<" Sec: "<<(SEC-30)<<endl; }

}

int main(){

int TOT = 0;
int TOF = 0;
int STOF = 0;
int booleeann = 0;
int booleeann0 = 0;
int booleeann1 = 0;
char mType = ' ';
char tType = ' ';
char resp = ' ';
string test = "";
string markType = "";
string tlType = "";

do{


cout<<"|-----------Welcome-----------|"<<endl;


while(TOT <= 0 || TOT > 200){

	cout<<"\n Enter Time on Target (TOT): ";
        getline(cin,test);

	if(test.length() > 6){ test = "stoiWhat??"; }
        else{ test = test.substr(0,4); test[3] = '\0'; }

	try{ TOT = stoi(test); }
        catch(...){ cout<<"\nYUT\n"<<endl; TOT = 0; test = ""; }
}
cout<<"\n Time On Target Inputed: "<<TOT<<endl;


test = "";
while(TOF <= 0 || TOF > 200){

        cout<<"\n Enter Time of Flight (TOF): ";
        getline(cin,test);

	if(test.length() > 6){ test = "stoiWhat??"; }
	else{ test = test.substr(0,4); test[3] = '\0'; }

        try{ TOF = stoi(test); }
        catch(...){ cout<<"\nJJDIDTIEBUCKLE\n"<<endl; TOF = 0; test = ""; }
}
cout<<"\n Time Of Flight Inputed: "<<TOF<<endl;


test = "";
markType = "iIwWnN";
booleeann = 0;
while(booleeann == 0){
        
        cout<<"\nEnter Marking Type -- I for Illumination -- W for White Phosphorus -- N for Negative: ";
	getline(cin,test);

        if(test.length() < 2){ 
	test = test.substr(0,2);
        test[1] = '\0';
        mType = test[0];
                 
	for(int i = 0; i < 6; i++){ if(mType == markType[i]){ booleeann = 1; break; test = ""; } }
        }

	if(booleeann == 0){ cout<<"\nPROS AND CONS WILL REFLECT\n"<<endl; }

}
cout<<"\n Type Of Marking Round: "<<mType<<endl;


test = "";
markType = "";
while(STOF <= 0 || STOF > 200){

        cout<<"\n Enter Supression Time of Flight (STOF): ";
        getline(cin,test);

	if(test.length() > 6){ test = "stoiWhat??"; }
        else{ test = test.substr(0,4); test[3] = '\0'; }

        try{ STOF = stoi(test); }
        catch(...){ cout<<"\nWWCD?\n"<<endl; STOF = 0; test = ""; }
}
cout<<"\n Supression Time Of Flight Inputed: "<<STOF<<endl;


test = "";
tlType = "iIcC";
booleeann = 0;
while(booleeann == 0){

        cout<<"\nEnter Type of Timeline -- C for Continious -- I for Interupted: ";
	getline(cin,test);

        if(test.length() < 2){
	test = test.substr(0,2);
        test[1] = '\0';
        tType = test[0];

        for(int i = 0; i < 4; i++){ if(tType == tlType[i]){ booleeann = 1; break; test = ""; } }
	}

	if(booleeann == 0){ cout<<"\nUAAAA I WANNAA GO\n"<<endl; }      

}
cout<<"\n Type Of Timeline: "<<tType<<endl;
test = "";


cout<<"\n|-----------TimeLine-----------|"<<endl;
cout<<"|----Min---|--------|---Sec----|"<<endl;

if(mType == 'i' || mType == 'I'){ illum(TOT,TOF); }

else if(mType == 'w' || mType == 'W'){ whtPhos(TOT,TOF); }

else if(mType == 'n' || mType == 'N'){ } //goes to negative: reguardless??

cout<<endl;

if(tType == 'c' || tType == 'C'){ mkContinious(TOT,STOF); }

else if(tType == 'i' || tType == 'I'){ mkInterrupted(TOT,STOF); }

cout<<"|----Min---|--------|---Sec----|"<<endl;
cout<<"|-----------TimeLine-----------|\n"<<endl;


while(booleeann0 == 0){

   cout<<"\nDouble Time? ( Y / N ):";
   getline(cin,test);

   if(test.length() < 2){

   test = test.substr(0,2);
   test[1] = '\0';
   resp = test[0];

   if(resp == 'n' || resp == 'N'){ booleeann0 = 1; booleeann1 = 1;  }
   else if(resp == 'y' || resp == 'Y'){ booleeann0 = 1; booleeann1 = 0; }
   else{ booleeann0 = 0; booleeann1 = 0; test = ""; resp = ' '; }
  
   }

   if(booleeann0 == 0){ cout<<"\nTHERES ALWAYS ONE\n"<<endl; }
}


test = "";
resp = ' ';
TOT = 0;
TOF = 0;
STOF = 0;
mType = ' ';
tType = ' ';
resp = ' ';
test = "";
markType = "";
tlType = "";
booleeann0 = 0;


}while(booleeann1 == 0);


}
