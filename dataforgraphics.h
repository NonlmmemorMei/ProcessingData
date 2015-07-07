#ifndef DATAFORGRAPHICS_H
#define DATAFORGRAPHICS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QVector>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>
#include <QChar>

#include "sunrisesunsettime.h"

class DataForGraphics : public QObject
{
    Q_OBJECT
public:
    explicit DataForGraphics(QObject *parent = 0);
    ~DataForGraphics(){}

    void                openFile(QFile &file);
    QStringList         trimCsv(QStringList itemsList) const;
    void                csvReadFile(QFile &file, QVector<QStringList> &listOfValues);
    double              maxValue();
    double              minValue();

    const int&          getXAxisSize();
    const int&          getYAxisSize();


    const int&          getSunRiseTime(QString fileName);
    const int&          getSunSetTime(QString fileName);

    double              getMax();
    const QStringList&  getFrequences();
    QString             cutLongAndLat(const QString &name);

    QString             cutName(const QString &filePath);
    QString             cutDay(const QString &filePath);
    QString             cutMonth(const QString &filePath);
    QString             cutYear(const QString &filePath);

    QString             getLongitude();
    QString             getLatitude();

    double              sunRiseSunSet(bool, QString &fileName);

    virtual void                             createMass()    = 0;
    virtual void                             process()       = 0;
    virtual double*                          getArrayForCreate3DGraph() = 0;
    virtual double                           getMaxValueForLegeng() = 0;
    virtual QVector <QVector <double> >      getDataFor2D() = 0;



protected:
    SunRiseSunSetTime*          m_sunRiseSunSetTime;
    const QChar                 m_separator;
    const QChar                 m_commentator;
    QFile                       m_file;
    QString                     m_latitude, m_longitude;
    int                         m_xSize, m_ySize;
    double                      m_timeSunRiseSunSet;
    double                      m_maxValue, m_minValue, m_max2;
    QStringList                 m_listNameOfFrequencys;
    double*                     m_result;
    QStringList                 m_fileName;
    QVector <double>            m_res;
    QVector <QStringList>       m_listOfValues;
    QVector <QVector <double> > m_vectorOfData;
};

#endif // DATAFORGRAPHICS_H




