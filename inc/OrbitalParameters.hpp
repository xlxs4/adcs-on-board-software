#pragma once

#include "Eigen/Dense"

#include "sgp4.h"

#include "TLEUtils.hpp"


/**
 * A class that takes a TLE file and initialize Gregorian time, greenwich sidereal time, satellite position in LLH frame and in ECI,
 * time since epoch, satrec, julian Date,
 */
class OrbitalParameters {
private:
    /**
     * Day month year hour minute second converted into julian date
     */
    double julianDate;
    /**
     * Structure containing all the sgp4 satellite information
     */
    elsetrec satrec;
    /**
     * Time since epoch in minutes
     */
    double timeSince;
    /**
     * Satellite position in ECI frame
     */
    Eigen::Vector3f satelliteECI;
    /**
     * Greenwich sidereal time (0 to 2pi rad)
     */
    double greenwichSiderealTime;
    double timeGregorian;
    Eigen::Vector3f satelliteLLH;

public:
    /**
     * Initialize properties of OrbitalParameters class julianDate, timeSince, position, greenwichSiderealTime, timeGregorian, satelliteLLH
     */
    OrbitalParameters();

    /**
     * Calculate julian day and Gregorian time
     *
     * @param tle Two-line element set
     * @param typerun type of run (verification 'v',catalog 'c',manual 'm')
     * @param typeinput type of manual input (mfe 'm', epoch 'e', dayofyr 'd')
     * @param opsmode mode of operation afspc or improved 'a', 'i'
     * @param whichconst which set of constants to use  72, 84
     */
    void
    calculateTime(const TLE &tle, char typerun, char typeinput, char opsmode, gravconsttype whichconst);

    /**
     * Calculate satellite position for the next time-step
     */
    void calculateNextPosition();

    double getJulianDate() const {
        return julianDate;
    }

    elsetrec getSatrec() const {
        return satrec;
    }

    /**
     * @return time since epoch (minutes)
     */
    double getTimeSince() const {
        return timeSince;
    }

    /**
     * @return satellite position ECI frame
     */
    Eigen::Vector3f getPosition() const {
        return satelliteECI;
    }

    /**
     * @return satellite position LLH frame
     */
    Eigen::Vector3f getSatelliteLLH() const {
        return satelliteLLH;
    }

    /**
     * @return greenwich sidereal time
     */
    double getGreenwichSiderealTime() const {
        return greenwichSiderealTime;
    }

    double getTimeGregorian() const {
        return timeGregorian;
    }
};