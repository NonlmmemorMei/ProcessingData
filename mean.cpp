#include "mean.h"

Mean::Mean(const QStringList &_fileName,
           const QStringList &_fileName2)
    :DataForCalculation()
{
     m_fileNames = _fileName;
     m_fileNames2 = _fileName2;
}

QVector <double> Mean::means()
{
    double meanX;
    int n = m_vectorOfData.size();

    QVector <double> meansX;

    for(int i = 0; i < m_vectorOfData.first().size(); i++)
    {
        meanX = 0.0;
        for(int j = 0; j < m_vectorOfData.size(); j++)
        {
            qDebug() << "- " << m_vectorOfData.at(j).at(i);
            meanX += m_vectorOfData.at(j).at(i);
        }
    meansX.push_back(meanX/n);
    }
    qDebug() << meansX;

return meansX;

}

void Mean::createResult()
{
    for(int i = 0; i < m_listOfValues.size(); i++)
        m_res.push_back(m_listOfValues[i][1].toDouble());
     m_vectorOfData.append(m_res);
}

void Mean::process()
{
    for(int i = 0; i < m_fileNames.size(); i++)
    {
        m_file.setFileName(m_fileNames[i]);
        csvReadCuttedFile(m_file, m_listOfValues);
        createResult();
        m_res.clear();
        m_listOfValues.clear();
    }


}
