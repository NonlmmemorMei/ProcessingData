#ifndef SUNRISESUNSETTIME_H
#define SUNRISESUNSETTIME_H

#include <QDateTime>
#include "qmath.h"
#include "math.h"

class SunRiseSunSetTime
{
public:
    explicit SunRiseSunSetTime();

    double getSunRiseSunSetTime(bool select);
    // setters:
    void   setDay(int _day);
    void   setMonth(int _month);
    void   setYear(int _year);
    void   setLatitude(double _latitude);
    void   setLongitude(double _longitude);
    void   setOffset(double _offset);

private:

    int m_day;
    int m_month;
    int m_year;

    double m_latitude;
    double m_longitude;
    double m_zenith;
    double m_offset;

    bool m_select;
};

#endif // SUNRISESUNSETTIME_H
