#ifndef CUT_H
#define CUT_H

#include "dataforcalculation.h"

#include <algorithm>
#include <QString>
#include <QFile>
#include <QVector>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>

class Cut : public DataForCalculation
{
public:
    Cut(const QString &_fileName, const QString &_dirForResult);
    ~Cut(){}

    void                    csvRead(QString fileName);
    void                    createResult();
    void                    process();

private:
    QFile                   m_file;
    QString                 m_fileName, m_dirForResult;
    QVector <QString>       m_times;
    QVector <QStringList>   m_listOfValues;    
};

#endif // CUT_H
