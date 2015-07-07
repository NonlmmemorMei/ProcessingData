#include "concatenator.h"

Concatenator::Concatenator(const QString &_fileName1,
                           const QString &_fileName2,
                           const QString &_dirForResult)
    :DataForCalculation()
{
    m_fileName1 = _fileName1;
    m_fileName2 = _fileName2;
    m_dirForResult = _dirForResult;
}

void Concatenator::mix()
{
    QString _str = "0.0";
    int _size = min(m_listOfValues1.size(), m_listOfValues2.size());
    for(int i = 0; i < _size; i++)
    {
        if((m_listOfValues1[i][1] == "0.0") && (m_listOfValues2[i][1] == "0.0"))
            m_result.push_back(_str);
        else if((m_listOfValues1[i][1] == "0.0") && (m_listOfValues2[i][1] != "0.0"))
            m_result.push_back(m_listOfValues2[i][1]);
        else if((m_listOfValues1[i][1] != "0.0") && (m_listOfValues2[i][1] == "0.0"))        
            m_result.push_back(m_listOfValues1[i][1]);
    }
}

void Concatenator::createResult()
{
    QString _outputFileName = cutOutputFileName(m_file1.fileName());
    QFile outputFile(m_dirForResult + _outputFileName);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outputFile);
    
    QVector <QString> _times;
    _times = calcTime();

    qDebug() << _times.size();
    
    QString _date = cutDate(m_file1.fileName());
    
    for(int i = 0; i < m_listHead.size()/2; i++)
        out << m_listHead[i][0];

    for(int i = 0; i < m_result.size(); i++)
    {
        QString _result;
        _result = _date + " " + _times[i] + " " + m_result[i];
        out << _result << endl;
    }
    outputFile.close();
}

void Concatenator::process()
{
    m_file1.setFileName(m_fileName1);
    m_file2.setFileName(m_fileName2);

    csvReadCuttedFile(m_file1, m_listOfValues1);
    csvReadCuttedFile(m_file2, m_listOfValues2);
    mix();
    createResult();

    m_listOfValues1.clear();
    m_listOfValues2.clear();
}


