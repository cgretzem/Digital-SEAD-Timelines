#ifndef TIMELINE_H
#define TIMELINE_H
#include "Sexagesimal.h"
#include <vector>

/**
 * Supported marking types for initial marking round before actual shells.
 *
 * These values are used to check which marking round is to be used and compute timelines
 * based on which one is chosen.
 */
typedef enum markingType
{
    ///No marking round is to be fired
    NEGATIVE,
    ///Illumination marking round
    ILLUM,
    ///White Phosphorus marking round
    WP
}markingType;


/**
 * A shell object to be used in the timeList to track type of round and what time to fire the round.
 *
 * isHE is used to tell if the shell is marking round or HE round.
 */
typedef struct shell
{
    ///Firing time for round
    Sexagesimal fireTime;
    ///Ff round is marking or HE
    bool isHE;
    /**
    * == Operator overload for shells
    *
    * @return true if shell == rhs
    */
    bool operator==(shell rhs);

    /**
     * > Operator overload for shells
     *
     * @return true if shell > rhs
     */
    bool operator>(shell rhs);

    /**
     * < Operator overload for shells
     *
     * @return true if shell < rhs
     */
    bool operator<(shell rhs);

    /**
     * >= Operator overload for shells
     *
     * @return true if shell >= rhs
     */
    bool operator>=(shell rhs);

    /**
     * <= Operator overload for shells
     *
     * @return true if shell <= rhs
     */
    bool operator<=(shell rhs);
}shell;


/**
 * Supported Timeline types for computing firing timelines.
 *
 * These values are used to check if there is a delay needed between each round
 * and is to be used and compute timelines
 * based on which one is chosen.
 */
typedef enum timelineType
{
    ///Continuous timeline - shells one after another
    CONTINUOUS,
    ///Interrupted timeline - shells have a delay between firing
    INTERRUPTED
}timelineType;

/**
 * Represents a range of values to fire under, based on TOT as 0.
 *
 * These are integer values that represent the + or - that the firing is to occur.
 * For example, if TOT is 15, range of -1 to +2, firing would occur from 14 to 16
 */
typedef struct fireRange
{
    ///Represents the offset of the starting minute based on the TOT
    int startMin;
    ///Represents the offset of the ending minute based on the TOT
    int endMin;
}fireRange;


/**
 * Abstract class used as a base class for Standard_Timeline
 * and NonStandard_Timeline.
 *
 * As firing times are computed, they are added as Sexagesimals
 * into the timeline's `timeList`. This timeList can then be printed
 * to show the time at which each shell should be fired.
 */
    class Timeline
{
protected:
    std::vector<shell> timeList;
    int startTime;
    int timeOnTarget;
    int timeOfFlight; /// How long the shell is in the air (seconds)

    /**
     * Sorts the timelist by fireTime of shells.
     */
    void sortTimeList();

public:
    /**
     * Constructor for abstract Timeline class, initalizes all private members
     * except for `timeList`
     *
     * @param TOT the Time on Target. Must be a whole number.
     *
     * @param TOF the Time of Flight of the shell. Must be a whole number.
     *
     * @return the `Timeline` object. This object has not set the value of `timeList` yet, so it must
     * be done in the derived classes.
     */
    Timeline(int TOT, int TOF);

    /**
     * Constructor for abstract Timeline class, initalizes all private members
     * except for `timeList`. Includes custom startTime Parameter
     *
     * @param startTime the Time to start firing timeline
     *
     * @param TOT the Time on Target. Must be a whole number.
     *
     * @param TOF the Time of Flight of the shell. Must be a whole number.
     *
     * @param mType the type of marking round to be fired, if negative do not fire
     * any marking round.
     *
     * @param MTOF the marking shell time of flight. Must be a whole number.
     *
     * @param tType the type of timeline to be created. Can be either continuous or interrupted.
     *
     * @return the `Timeline` object. This object has not set the value of `timeList` yet, so it must
     * be done in the derived classes.
     */
    Timeline(int startTime, int TOT, int TOF);

    /**
     * Fills the `timeList` table with Sexagesimal times that represent when each shell should be fired.
     * This method is pure virtual void, so it must be overwritten in both derived classes.
     *
     * @return firing times.
     */
    virtual std::vector<shell> makeTimelist() = 0;

    /**
     * Getter method for the `timeList` vector.
     *
     * @return shell type and firing time.
     */
    std::vector<shell> getTimeList();

    /**
     * Getter method for Time on Target.
     *
     * @return Time on Target.
     */
    int getTOT();

    /**
     * Getter method for Time of Flight.
     *
     * @return Time of FLight.
     */
    int getTOF();

    /**
     * Method for formatting the firing times in a readable way.
     */
    //virtual void print();
    string print();

};

/**
 * Class to represent a standard firing timeline
 *
 * As firing times are computed, they are added as shells
 * into the timeline's `timeList`. This timeList can then be printed
 * to show the type of shell, and the time at which each shell should be fired.
 */
class Standard_Timeline final : public Timeline
{
public:
    /**
     * Constructor for  Standard_Timeline class, uses parent constructor to initalize all private members
     * except for `timeList`, then calls `makeTimelist()` to fill `timeList` with data.
     *
     * @see makeTimelist()
     *
     * @param TOT the Time on Target. Must be a whole number.
     *
     * @param TOF the Time of FLight of the shell. Must be a whole number.
     *
     * @param mType the type of marking round to be fired, if negative do not fire
     * any marking round.
     *
     * @param MTOF the marking shell time of flight. Must be a whole number.
     *
     * @param tType the type of timeline to be created. Can be either continuous or interrupted.
     *
     * @return the `Standard_Timeline` object.
     */
    Standard_Timeline(int TOT, int TOF, markingType mType, int MTOF, timelineType tType);

    /**
     * Getter method for Supression Time of Flight.
     *
     * @return supressionTOF.
     */
    int getMTOF();

    /**
     * Getter method for the marking type.
     *
     * @return marking type.
     */
    markingType getMarkingType();

    /**
     * Getter method for timeline type.
     *
     * @return timeline type.
     */
    timelineType getTimelineType();

    /**
    * Method for formatting the firing times in a readable way.
    */
    //void print();
    string print();

private:
    /**
     * Fills the `timeList` table with Sexagesimal times that represent when each shell should be fired.
     *
     * @return shell types and firing times.
     */
    std::vector<shell> makeTimelist();
    markingType mType; ///Marking type of round, ILLUM, WP, or NEGATIVE
    int markingTOF; /// Time in seconds
    timelineType tType; ///Type of timeline, CONTINUOUS or INTERRUPTED 
};

/**
 * Class to represent a Non-standard firing timeline
 *
 * As firing times are computed, they are added as Sexagesimals
 * into the timeline's `timeList`. This timeList can then be printed
 * to show the type of shell, and the time at which each shell should be fired.
 */
class NonStandard_Timeline final : public Timeline
{
public:
    //TODO : change constructor to include new parameters for a nonstandard timeline
        /**
         * Constructor for  NonStandard_Timeline class, uses parent constructor to initalize all private members
         * except for `timeList`, then calls `makeTimelist()` to fill `timeList` with data.
         *
         * @see makeTimelist()
         *
         * @param TOT the Time on Target. Must be a whole number.
         *
         * @param TOF the Time of FLight of the shell. Must be a whole number.
         * 
         * @param mType the type of marking round to be fired, if negative do not fire
         * any marking round.
         *
         * @param MTOF the marking shell time of flight. Must be a whole number.
         *
         * @param firingRanges A list of ranges over which to fire shells.
         *
         * @param fireFreq How frequently, in seconds, a round is fired. Default is 30.
         *
         * @return the `NonStandard_Timeline` object.
         */
         
    NonStandard_Timeline(int TOT, int TOF, markingType mType, int MTOF, std::vector<fireRange> firingRanges, int fireFreq);

    /**
     * Getter method for Marking Time of Flight.
     *
     * @return MarkingTOF.
     */
    int getMTOF();

    /**
     * Getter method for the marking type.
     *
     * @return marking type.
     */
    markingType getMarkingType();

    /**
    * Method for formatting the firing times in a readable way.
    */
    //void print();
    string print();
private:
    /**
     * Fills the `timeList` table with Sexagesimal times that represent when each shell should be fired.
     *
     * @return shell types and firing times.
     */
    std::vector<shell> makeTimelist();
    markingType mType; ///Marking type of round, ILLUM, WP, or NEGATIVE
    int markingTOF; /// Time in seconds
    std::vector<fireRange> firingRanges;
    int fireFreq;
};


#endif
