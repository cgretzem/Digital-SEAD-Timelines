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
    ///Illumination round
    ILLUM,
    ///What is wp again?
    WP,
    ///No marking round is to be fired
    NEGATIVE
}markingType;


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
        std::vector<Sexagesimal> timeList;

    private:
        markingType mType;
        timelineType tType;
        int supressionTOF;
        int timeOnTarget;
        int timeOfFlight;

    public:
        /**
         * Constructor for abstract Timeline class, initalizes all private members
         * except for `timeList`
         * 
         * @param TOT the Time on Target. Must be a whole number.
         * 
         * @param TOF the Time of FLight of the shell. Must be a whole number.
         * 
         * @param mType the type of marking round to be fired, if negative do not fire
         * any marking round. 
         * 
         * @param STOF the supression time of flight. Must be a whole number.
         * 
         * @param tType the type of timeline to be created. Can be either continuous or interrupted.
         * 
         * @return the `Timeline` object. This object has not set the value of `timeList` yet, so it must
         * be done in the derived classes.
         */
        Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType);

        /**
         * Fills the `timeLine` table with Sexagesimal times that represent when each shell should be fired.
         * This method is pure virtual void, so it must be overwritten in both derived classes.
         * 
         * @return firing times.
         */
        virtual std::vector<Sexagesimal> makeTimeline() = 0;

        /**
         * Getter method for the `timeList` vector.
         * 
         * @return firing times.
         */
        std::vector<Sexagesimal> getTimeList();

        /**
         * Getter method for Supression Time of Flight.
         * 
         * @return supressionTOF.
         */
        int getSTOF();

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
         * Outstream method for using cout with the timeline.
         * 
         * @param os the outstream that the formatted data will be sent to.
         * 
         * @param tl the timeline to be sent out.
         */
        friend ostream& operator<<(ostream& os, Timeline tl);

        /**
         * Method for formatting the firing times in a readable way.
         * 
         * @return formatted string with firing times
         */
        string print();

};

/**
 * Class to represent a standard firing timeline
 * 
 * As firing times are computed, they are added as Sexagesimals
 * into the timeline's `timeList`. This timeList can then be printed
 * to show the time at which each shell should be fired.
 */
class Standard_Timeline final: public Timeline
{
    public:
        /**
         * Constructor for  Standard_Timeline class, uses parent constructor to initalize all private members
         * except for `timeList`, then calls `makeTimeline()` to fill `timeList` with data.
         * 
         * @see makeTimeLine()
         * 
         * @param TOT the Time on Target. Must be a whole number.
         * 
         * @param TOF the Time of FLight of the shell. Must be a whole number.
         * 
         * @param mType the type of marking round to be fired, if negative do not fire
         * any marking round. 
         * 
         * @param STOF the supression time of flight. Must be a whole number.
         * 
         * @param tType the type of timeline to be created. Can be either continuous or interrupted.
         * 
         * @return the `Standard_Timeline` object.
         */
        Standard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType);
    private:
        /**
         * Fills the `timeLine` table with Sexagesimal times that represent when each shell should be fired.
         *  
         * @return firing times.
         */
        std::vector<Sexagesimal> makeTimeline();
};

/**
 * Class to represent a Non-standard firing timeline
 * 
 * As firing times are computed, they are added as Sexagesimals
 * into the timeline's `timeList`. This timeList can then be printed
 * to show the time at which each shell should be fired.
 */
class NonStandard_Timeline final: public Timeline
{
    public:
    //TODO : change constructor to include new parameters for a nonstandard timeline
        /**
         * Constructor for  NonStandard_Timeline class, uses parent constructor to initalize all private members
         * except for `timeList`, then calls `makeTimeline()` to fill `timeList` with data.
         * 
         * @see makeTimeLine()
         * 
         * @param TOT the Time on Target. Must be a whole number.
         * 
         * @param TOF the Time of FLight of the shell. Must be a whole number.
         * 
         * @param mType the type of marking round to be fired, if negative do not fire
         * any marking round. 
         * 
         * @param STOF the supression time of flight. Must be a whole number.
         * 
         * @param tType the type of timeline to be created. Can be either continuous or interrupted.
         * 
         * @return the `NonStandard_Timeline` object.
         */
        NonStandard_Timeline(int TOT, int TOF, markingType mType, int STOF, timelineType tType);
        private:
            /**
             * Fills the `timeLine` table with Sexagesimal times that represent when each shell should be fired.
             *  
             * @return firing times.
             */
            std::vector<Sexagesimal> makeTimeline();
};


#endif