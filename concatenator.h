#ifndef CONCATENATOR_H
#define CONCATENATOR_H

#include "dataforcalculation.h"

class Concatenator : public DataForCalculation
{
public:
    Concatenator(const QString &_fileName1, const QString &_fileName2,
                 const QString &_dirForResult);
    ~Concatenator(){}

    void                   mix();
    void                   createResult();
    void                   process();

private:
    QFile                  m_file1, m_file2;
    QString                m_fileName1, m_fileName2, m_dirForResult;
    QVector <QString>      m_result;
    QVector <QStringList>  m_listOfValues1, m_listOfValues2;    
};

#endif // CONCATENATOR_H
