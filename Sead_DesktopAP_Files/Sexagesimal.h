#ifndef SEXAGESIMAL_H
#define SEXAGESIMAL_H
#include <iostream>
#include <string>
using namespace std;

/**
 * A class used for doing computations using Sexagesimal math
 *
 * Sexagesimal math is math using base 60. This is crucial for creating timelines
 * for the USMC because all operations are based upon military time.
 * Therefore, input and output for our application need to be in military time as well.
 * This class keeps track of a single time,  with hours, minutes, and seconds represented
 * in military format.
 */
class Sexagesimal
{
public:
    /**
     * Default constructor for a Sexagesimal.
     *
     * Initializes hours, minutes, seconds, totalseconds, and day to 0.
     *
     * @return the `Sexagesimal` object initalized to 00:00:00.
     */
    Sexagesimal();

    /**
     * Constructor for a custom Sexagesimal.
     *
     * Provide hours, minutes, and seconds in and this constructor returns a
     * Sexagesimal initialized to `hours:minutes:seconds`.
     *
     * @param hours the amount of hours this Sexagesimal has.
     *
     * @param minutes the amount of minutes this Sexagesimal has.
     *
     * @param seconds the amount of seconds this Sexagesimal has.
     *
     * @return the `Sexagesimal` object initalized to `hours:minutes:seconds`.
     */
    Sexagesimal(int hours, int minutes, int seconds);

    /**
     *  Operator override for adding two Sexagesimals together.
     *
     * Takes the total seconds from both Sexagesimals, adds them together,
     * then uses `convertToBase60()` to convert the new total seconds back into
     * a Sexagesimal.
     *
     * @param num the second Sexagesimal to be added to the first
     *
     * @return `Sexagesimal` representing the first two Sexagesimals added together.
     */
    Sexagesimal operator+(Sexagesimal num);

    /**
     *  Operator override for subtracting two Sexagesimals.
     *
     * Takes the total seconds from both Sexagesimals, subtracts num from the first Sexagesimal,
     * then uses `convertToBase60()` to convert the new total seconds back into
     * a Sexagesimal.
     *
     * @param num the second Sexagesimal to be added to the first
     *
     * @return `Sexagesimal` representing the first two Sexagesimals added together.
     */
    Sexagesimal operator-(Sexagesimal num);

    /**
     * > Operator overload for Sexagesimals
     *
     * Compares day, then if day is same, compares totalSeconds.
     *
     * @param s1 the `Sexagesimal` on the left hands side
     *
     * @param s2 the `Sexagesimal` on the right hands side
     *
     * @return true if s1 > s2
     */
    friend bool operator>(Sexagesimal s1, Sexagesimal s2);

    /**
    * < Operator overload for Sexagesimals
    *
    * Compares day, then if day is same, compares totalSeconds.
    *
    * @param s1 the `Sexagesimal` on the left hands side
    *
    * @param s2 the `Sexagesimal` on the right hands side
    *
    * @return true if s1 < s2
    */
    friend bool operator<(Sexagesimal s1, Sexagesimal s2);

    /**
    * == Operator overload for Sexagesimals
    *
    * Compares day, then if day is same, compares totalSeconds.
    *
    * @param s1 the `Sexagesimal` on the left hands side
    *
    * @param s2 the `Sexagesimal` on the right hands side
    *
    * @return true if s1 == s2
    */
    friend bool operator==(Sexagesimal s1, Sexagesimal s2);

    /**
    * <= Operator overload for Sexagesimals
    *
    * Compares day, then if day is same, compares totalSeconds.
    *
    * @param s1 the `Sexagesimal` on the left hands side
    *
    * @param s2 the `Sexagesimal` on the right hands side
    *
    * @return true if s1 <= s2
    */
    friend bool operator<=(Sexagesimal s1, Sexagesimal s2);

    /**
     * >= Operator overload for Sexagesimals
     *
     * Compares day, then if day is same, compares totalSeconds.
     *
     * @param s1 the `Sexagesimal` on the left hands side
     *
     * @param s2 the `Sexagesimal` on the right hands side
     *
     * @return true if s1 >= s2
     */
    friend bool operator>=(Sexagesimal s1, Sexagesimal s2);

    /**
    * << Operator overload for Sexagesimals
    *
    * Calls the print method and pushes it to the ostream
    *
    * @param os the `ostream` to stream the `Sexagesimal` to.
    *
    * @param sx the `Sexagesimal` to stream.
    *
    * @return `ostream` with printed Sexagesimal.
    */
    friend ostream& operator<<(ostream& os, Sexagesimal sx);

    /**
     * A method to print the Sexagesimal in a readable way.
     *
     * Prints `Sexagesimal` in a 00:00:00 format
     *
     * @return the formatted `Sexagesimal`
     */
    string print();
private:
    int hours; ///Represents the hours that this Sexagesimal has.
    int minutes;///Represents the minutes that this Sexagesimal has.
    int seconds;///Represents the seconds that this Sexagesimal has.
    int totalSeconds;///Represents the total Seconds this Sexagesimal has, hours, minutes, and seconds together.
    int day;///A variable mainly used for sorting and tracking, is never displayed anywhere. Keeps track of the days a Sexagesimal has.

    /**
     * A private function used when adding or subtracting Sexagesimals.
     *
     * Converts totalSeconds from adding or subtracting two Sexagesimals
     * back into a Sexagesimal filled with newly computed hours, minutes, and seconds.
     *
     * @param totalSeconds the number of seconds that needs to be converted into a Sexagesimal.
     *
     * @return `Sexagesimal` representing the total seconds.
     */
    friend Sexagesimal convertToBase60(int totalSeconds);
};


#endif
