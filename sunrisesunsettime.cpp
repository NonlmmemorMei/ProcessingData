#include "sunrisesunsettime.h"
#include <QDebug>

SunRiseSunSetTime::SunRiseSunSetTime()
{
    m_zenith = 90.5;
    m_offset = 4;
}

double SunRiseSunSetTime::getSunRiseSunSetTime(bool select)
{
    double dToR, rToD;
    dToR = M_PI/180;
    rToD = 180/M_PI;

    int n1, n2, n3, dayOfYear;
    double longitudeHour;
    double t, t1, uT, localTime; // Промежуточное время
    double sunAnomaly;
    double trueLongitude;
    double rightAscension;
    double lQuadrant, RaQuadrant;
    double sinDec, cosDec, cosH, h;

    n1 = floor(275*m_month/9);
    n2 = floor((m_month + 9)/12);
    n3 = (1 + floor((m_year - 4 * floor(m_year/4) + 2)/3));
    dayOfYear = n1 - (n2 * n3) + m_day - 30;     // Расчёт дня года
    longitudeHour = m_longitude/15;
    if(select == true)
       t = dayOfYear + ((6 - longitudeHour)/24);
    else
       t = dayOfYear + ((18 - longitudeHour)/24);

    sunAnomaly = (0.9856 * t) - 3.289;
    trueLongitude = sunAnomaly + (1.916 * sin(dToR * sunAnomaly)) + (0.020 * sin(2 * dToR * sunAnomaly)) + 282.634;

    if(trueLongitude < 0)
       trueLongitude = trueLongitude + 360;
    if(trueLongitude > 360)
       trueLongitude = trueLongitude - 360;

    rightAscension = rToD * atan(0.91764 * tan(dToR * trueLongitude));
    lQuadrant = (floor(trueLongitude/90)*90);
    RaQuadrant = (floor(rightAscension/90)*90);
    rightAscension = (rightAscension + (lQuadrant - RaQuadrant))/15;

    sinDec = 0.39728 * sin(dToR * trueLongitude);
    cosDec = cos(asin(sinDec));
    cosH = (cos(dToR * m_zenith) - (sinDec * sin(dToR * m_latitude))) / (cosDec * cos(dToR * m_latitude));

    if(cosH > 1)
    {
       qDebug() << "The Sun is never rises (for this date)";
       uT = -1;
    }
       else
       {
            if(select == true)
                h = (360 - (rToD * acos(cosH)))/15;
            else
                h = (rToD * acos(cosH))/15;

            t1 = h + rightAscension - (0.06571 * t) - 6.622;
            uT = t1 - longitudeHour;

            if(uT < 0)
               uT = uT + 24;
            if(uT > 24)
               uT = uT - 24;
       }

    localTime = uT + m_offset;
    return localTime;
}

void SunRiseSunSetTime::setDay(int _day)
{
    m_day = _day;
}

void SunRiseSunSetTime::setMonth(int _month)
{
    m_month = _month;
}

void SunRiseSunSetTime::setYear(int _year)
{
    m_year = _year;
}

void SunRiseSunSetTime::setLatitude(double _latitude)
{
    m_latitude = _latitude;
}

void SunRiseSunSetTime::setLongitude(double _longituge)
{
    m_longitude = _longituge;
}

