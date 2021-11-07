#ifndef SEXSIGMAL_H
#define SEXSIGMAL_H
#include <iostream>
#include <string>
using namespace std;
class Sexagesimal
{
    public:
        Sexagesimal();
        Sexagesimal(int hours, int minutes, int seconds);
        void setDay(int day);
        int getDay();
        Sexagesimal operator+(Sexagesimal num);
        Sexagesimal operator-(Sexagesimal num);
        //+ and - int overload assumes seconds
        Sexagesimal operator+(int seconds);
        Sexagesimal operator-(int seconds);
        friend bool operator>(Sexagesimal s1, Sexagesimal s2);
        friend bool operator<(Sexagesimal s1, Sexagesimal s2);
        friend bool operator==(Sexagesimal s1, Sexagesimal s2);
        friend bool operator<=(Sexagesimal s1, Sexagesimal s2);
        friend bool operator>=(Sexagesimal s1, Sexagesimal s2);
        friend ostream& operator<<(ostream& os, Sexagesimal sx);
        string print();
        int getSeconds();
        int getHours();
        int getMinutes();
        int getTotalSeconds();
    private:
        int hours;
        int minutes;
        int seconds;
        int totalSeconds;
        int day;
};


#endif