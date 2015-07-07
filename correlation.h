#ifndef CORRELATION_H
#define CORRELATION_H

#include "dataforcalculation.h"
#include "math.h"
#include "alglib/statistics.h"

class Correlation : public DataForCalculation
{
public:
    Correlation(const QStringList &_fileName);
    ~Correlation(){}

    void                            means(QVector<double> _massX, QVector<double> _massY);
    void                            variance(QVector <double> _massX, QVector <double> _massY);
    void                            covariance(QVector <double> _massX, QVector <double> _massY);
    double                          correl(QVector <double> &_x, QVector <double> &_y);
    QVector <double>                calcCorrel();
    QVector <double>                statistics(QVector <double> &res);
    void                            createResult();
    void                            process();

private:
    QFile                           m_file;
    double                          m_meanX, m_meanY;
    double                          m_varianceX, m_varianceY;
    double                          m_covarianceXY;
    double                          m_correlationRes;
    double                          m_correlationRes2;
    QStringList                     m_fileNames;
    QVector <double>                m_x, m_y, m_indexesCorrel, m_res;
    QVector <QStringList>           m_listOfValues;
    QVector <QVector <double> >     m_vectorOfData;


};

#endif // CORRELATION_H
