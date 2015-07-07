#ifndef MEAN_H
#define MEAN_H

#include "dataforcalculation.h"

class Mean : public DataForCalculation
{
public:
    Mean(const QStringList &_fileName, const QStringList &_fileName2);
    ~Mean(){}

    QVector <double> means();
    void             createResult();
    void             process();


private:

    QFile                           m_file;
    QVector <double>                m_res;
    QStringList                     m_fileNames;
    QStringList                     m_fileNames2;
    QVector <QStringList>           m_listOfValues;
    QVector <QVector <double> >     m_vectorOfData;
};

#endif // MEAN_H
