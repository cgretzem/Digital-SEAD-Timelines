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


void illum(int tot, int tof, int ch){

    int TOT_HIT = (((tot * 60) - 45) - (tof + 5));
    int MIN = TOT_HIT / 60;
    int SEC = TOT_HIT % 60;
    Sexagesimal s = Sexagesimal(ch,0,0);
    cout<<"Min: "<<MIN<<" Sec: "<<SEC<<endl;
    s = s + Sexagesimal(0,MIN,SEC);
    cout<<s<<endl;
}


void whtPhos(int tot, int tof, int ch){

    int TOT_HIT = (((tot * 60) - 30) - (tof + 5));
    int MIN = TOT_HIT / 60;
    int SEC = TOT_HIT % 60;
    Sexagesimal s = Sexagesimal(ch,0,0);
    cout<<"Min: "<<MIN<<" Sec: "<<SEC<<endl;
    s = s + Sexagesimal(0,MIN,SEC);
    cout<<s<<endl;

}


void negative(){

//goes to negative reguardless??

}


void mkContinious(int tot, int stof, int ch){

 
 int TOT_HIT = ((tot * 60) - (stof + 5));
 int MIN = TOT_HIT / 60;
 int SEC = TOT_HIT % 60;

 cout<<"Min: "<<(MIN-1)<<" Sec: "<<SEC<<endl;
 Sexagesimal s = Sexagesimal(0,MIN,SEC);
 Sexagesimal s1 = s - Sexagesimal(0,1,0);
 cout<<s1<<endl;
 s1 = s;

 if(stof >= 30){
	 cout<<"Min: "<<(MIN-1)<<" Sec: "<<(SEC+30)<<endl;
	 s1 = s1 - Sexagesimal(0,1,0);
	 s1 = s1 + Sexagesimal(0,0,30);
	 cout<<s1<<endl;
 }else{
	 cout<<"Min: "<<MIN<<" Sec: "<<(SEC-30)<<endl;
	 s1 = s1 - Sexagesimal(0,0,30);
	 cout<<s1<<endl; 
 }

 s1 = s;
 s1 = s1 + Sexagesimal(0,0,0); 
 cout<<"Min: "<<MIN<<" Sec: "<<SEC<<endl;
 cout<<s1<<endl;

 if(stof < 30){
	 cout<<"Min: "<<(MIN+1)<<" Sec: "<<(SEC-30)<<endl;
	 s1 = s1 + Sexagesimal(0,1,0);
	 s1 = s1 - Sexagesimal(0,0,30);
	 cout<<s1<<endl;
 }else{
	 cout<<"Min: "<<MIN<<" Sec: "<<(SEC+30)<<endl;
	 s1 = s1 + Sexagesimal(0,0,30);
	 cout<<s1<<endl;
 }
 s1 = s;

 cout<<"Min: "<<(MIN+1)<<" Sec: "<<SEC<<endl;
 s1 = s1 + Sexagesimal(0,1,0);
 cout<<s1<<endl;
}


void mkInterrupted(int tot, int stof, int ch){

 int TOT_HIT = ((tot * 60) - (stof + 5));
 int MIN = TOT_HIT / 60;
 int SEC = TOT_HIT % 60;
 Sexagesimal s = Sexagesimal(0,MIN,SEC);
 Sexagesimal s1 = s;
 cout<<"Min: "<<(MIN-1)<<" Sec: "<<SEC<<endl;
 s1 = s1 - Sexagesimal(0,1,0);
 cout<<s1<<endl;

 s1 = s;
 if(stof >= 30){
	 
	 cout<<"Min: "<<(MIN-1)<<" Sec: "<<(SEC+30)<<endl;
         s1 = s1 - Sexagesimal(0,1,0);
	 s1 = s1 + Sexagesimal(0,0,30);
	 cout<<s1<<endl;

 }else{
	 cout<<"Min: "<<MIN<<" Sec: "<<(SEC-30)<<endl;
	 s1 = s1 - Sexagesimal(0,0,30);
	 cout<<s1<<endl;
 }

}

int main(){

int TOT = 0;
int TOF = 0;
int STOF = 0;
int booleeann = 0;
int booleeann0 = 0;
int booleeann1 = 0;
int currentHour = -1;
char mType = ' ';
char tType = ' ';
char resp = ' ';
string test = "";
string markType = "";
string tlType = "";

do{


cout<<"|-----------Welcome-----------|"<<endl;


while(currentHour < 0 || currentHour > 24){

        cout<<"\n Enter Current Hour (0 - 24): ";
        getline(cin,test);

        if(test.length() > 2){ test = "stoiWhat??"; }

        try{ currentHour = stoi(test); }
        catch(...){ cout<<"\nDONT BE THE ONE\n"<<endl; currentHour = -1; test = ""; }
}
cout<<"\n Current Hour Inputed: "<<currentHour<<endl;
test = "";


while(TOT <= 0 || TOT > 200){

	cout<<"\n Enter Time on Target (TOT): ";
        getline(cin,test);

	if(test.length() > 3){ test = "stoiWhat??"; }

	try{ TOT = stoi(test); }
        catch(...){ cout<<"\nYUT\n"<<endl; TOT = 0; test = ""; }
}
cout<<"\n Time On Target Inputed: "<<TOT<<endl;


test = "";
while(TOF <= 0 || TOF > 200){

        cout<<"\n Enter Time of Flight (TOF): ";
        getline(cin,test);

	if(test.length() > 3){ test = "stoiWhat??"; }

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

	if(test.length() > 3){ test = "stoiWhat??"; }

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
	tType = test[0];
        for(int i = 0; i < 4; i++){ if(tType == tlType[i]){ booleeann = 1; break; test = ""; } }
	}

	if(booleeann == 0){ cout<<"\nUAAAA I WANNAA GO\n"<<endl; }      

}
cout<<"\n Type Of Timeline: "<<tType<<endl;
test = "";


cout<<"\n|-----------TimeLine-----------|"<<endl;
cout<<"|---Hour---|---Min---|---Sec---|"<<endl;

if(mType == 'i' || mType == 'I'){ illum(TOT,TOF,currentHour); }
else if(mType == 'w' || mType == 'W'){ whtPhos(TOT,TOF,currentHour); }
else if(mType == 'n' || mType == 'N'){ } //goes to negative: reguardless??

cout<<endl;

if(tType == 'c' || tType == 'C'){ mkContinious(TOT,STOF,currentHour); }
else if(tType == 'i' || tType == 'I'){ mkInterrupted(TOT,STOF,currentHour); }

cout<<"|---Hour---|---Min---|---Sec---|"<<endl;
cout<<"|-----------TimeLine-----------|\n"<<endl;


while(booleeann0 == 0){

   cout<<"\nDouble Time? ( Y / N ):";
   getline(cin,test);

   if(test.length() < 2){
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
currentHour = -1;

}while(booleeann1 == 0);


}
