#include "Sexagesimal.h"
using namespace std;
Sexagesimal::Sexagesimal()
{
    this->hours = 0;
    this->minutes = 0;
    this->seconds = 0;
    this->totalSeconds = 0;
    day = 0;
}

Sexagesimal::Sexagesimal(int hours, int minutes, int seconds)
{
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    this->totalSeconds = ((hours * 3600)+ (minutes*60) + seconds);
    day = 0;
}

Sexagesimal convertToBase60(int totalSeconds)
{
    //if seconds are negative, turn back the clock to end of last day, ie -5 would be 23:59:55
    int negDays = 0;
    while(totalSeconds < 0)
    {
        totalSeconds = (3600*24)+totalSeconds;
        negDays++;
    }
        
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds%3600)/60;
    int seconds = (totalSeconds%3600)%60;
    Sexagesimal output = Sexagesimal(hours, minutes, seconds);
    output.day = ((hours/24) - negDays);
    hours = (hours %24);
    return output;
}


ostream& operator<<(ostream& os, Sexagesimal sx)
{
    return os << sx.print(); 
}
//overloading the + and - operators
Sexagesimal Sexagesimal::operator+ (Sexagesimal num)
{
    //add by adding total seconds of both nums together, then converting back
    int total = this->totalSeconds + num.totalSeconds; 
    return convertToBase60(total);
}
Sexagesimal Sexagesimal::operator-(Sexagesimal num) 
{
    int total = this->totalSeconds - num.totalSeconds;
    return convertToBase60(total);
}

bool operator>(Sexagesimal s1, Sexagesimal s2)
{
    if(s1.day > s2.day)
        return true;
    if(s2.day > s1.day)
        return false;
    return s1.totalSeconds > s2.totalSeconds;
}
bool operator<(Sexagesimal s1, Sexagesimal s2)
{
    if(s1.day < s2.day)
        return true;
    if(s2.day < s1.day)
        return false;
    return s1.totalSeconds < s2.totalSeconds;
}

bool operator==(Sexagesimal s1, Sexagesimal s2)
{
    if(s1.day == s2.day && s1.totalSeconds == s2.totalSeconds)
        return true;
    return false;
}

bool operator>=(Sexagesimal s1, Sexagesimal s2)
{
    if(s1 == s2)
        return true;
    if(s1 > s2)
        return true;
    return false;
}

bool operator<=(Sexagesimal s1, Sexagesimal s2)
{
    if(s1 == s2)
        return true;
    if(s1 < s2)
        return true;
    return false;
}

string Sexagesimal::print()
{
    string output = "";
    if(hours < 10)
        output += "0";
    output += to_string(hours) + ":";
    if(minutes < 10)
        output += "0";
    output += to_string(minutes) + ":";
    if(seconds < 10)
        output += "0";
    output += to_string(seconds);
    return output;
}
