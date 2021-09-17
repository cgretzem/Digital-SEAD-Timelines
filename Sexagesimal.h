#ifndef SEXSIGMAL_H
#define SEXSIGMAL_H
#include <iostream>
#include <string>
using namespace std;
class Sexagesimal
{
    public:
        Sexagesimal(int hours, int minutes, int seconds);
        Sexagesimal operator+(Sexagesimal num);
        Sexagesimal operator-(Sexagesimal num);
        //+ and - int overload assumes seconds
        Sexagesimal operator+(int seconds);
        Sexagesimal operator-(int seconds);
        friend ostream& operator<<(ostream& os, Sexagesimal sx);
        string print();
        int getSeconds();
    private:
        int hours;
        int minutes;
        int seconds;
        int totalSeconds;
};

Sexagesimal::Sexagesimal(int hours, int minutes, int seconds)
{
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    this->totalSeconds = ((hours * 3600)+ (minutes*60) + seconds);
}

//could add functinality for changing the day in this method, if you want to specify day and time of attacks.
static Sexagesimal convertToBase60(int totalSeconds)
{
    //if seconds are negative, turn back the clock to end of last day, ie -5 would be 23:59:55
    if(totalSeconds < 0)
        totalSeconds = (3600*24)+totalSeconds;
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds%3600)/60;
    int seconds = (totalSeconds%3600)%60;
    hours = (hours %24);
    return Sexagesimal(hours, minutes, seconds);
}

int Sexagesimal::getSeconds()
{
    return totalSeconds;
}


ostream& operator<<(ostream& os, Sexagesimal sx)
{
    return os << sx.print(); 
}
//overloading the + and - operators
Sexagesimal Sexagesimal::operator+ (Sexagesimal num)
{
    //add by adding total seconds of both nums together, then converting back
    int total = this->totalSeconds + num.getSeconds(); 
    return convertToBase60(total);
}
Sexagesimal Sexagesimal::operator-(Sexagesimal num) 
{
    int total = this->totalSeconds - num.getSeconds();
    return convertToBase60(total);
}
Sexagesimal Sexagesimal::operator+(int seconds)
{
    return convertToBase60(totalSeconds+seconds);
}
Sexagesimal Sexagesimal::operator-(int seconds)
{
    return convertToBase60(totalSeconds-seconds);
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
#endif