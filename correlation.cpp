#include "correlation.h"

Correlation::Correlation(const QStringList &_fileName)
    :DataForCalculation()
{
    m_fileNames = _fileName;

}

void Correlation::means(QVector<double> _massX, QVector<double> _massY)
{
    m_meanX = 0;
    m_meanY = 0;

    for(int i = 0; i < _massX.size(); i++)
    {
        m_meanX = m_meanX + _massX[i];
        m_meanY = m_meanY + _massY[i];
    }
    m_meanX = m_meanX/_massX.size();
    m_meanY = m_meanY/_massY.size();

    qDebug() << "m_meanX" << m_meanX;
    qDebug() << "m_meanY" << m_meanY;
}

void Correlation::variance(QVector<double> _massX, QVector<double> _massY)
{
    m_varianceX = 0;
    m_varianceY = 0;
    for(int i = 0; i < _massX.size(); i++)
    {
        m_varianceX = m_varianceX + ((_massX[i] - m_meanX)*(_massX[i] - m_meanX));
        m_varianceY = m_varianceY + ((_massY[i] - m_meanY)*(_massY[i] - m_meanY));
    }

    qDebug() << "m_varianceX" << m_varianceX;
    qDebug() << "m_varianceY" << m_varianceY;
}

void Correlation::covariance(QVector<double> _massX, QVector<double> _massY)
{
    m_covarianceXY = 0;

    qDebug() << "m_meanX2" << m_meanX;

    for(int i = 0; i < _massX.size(); i++)
        m_covarianceXY += ((_massX[i] - m_meanX)*(_massY[i] - m_meanY));

    qDebug() << "m_covarianceXY" << m_covarianceXY;
}

double Correlation::correl(QVector<double> &_x, QVector<double> &_y)
{
    double _correlationRes;
    means(_x, _y);
    variance(_x, _y);
    covariance(_x, _y);
    _correlationRes = m_covarianceXY/(sqrt(m_varianceX * m_varianceY));
    return _correlationRes;
}

QVector<double> Correlation::calcCorrel()
{
    for(int i = 0; i < m_vectorOfData.size(); i++)
    {
        m_vectorOfData[i].erase(m_vectorOfData[i].begin(), m_vectorOfData[i].begin()+6000);
        m_vectorOfData[i].erase(m_vectorOfData[i].end()-3000, m_vectorOfData[i].end());
    }

    qDebug() << "first.size" << m_vectorOfData.first().size(); // j - number of elements
    qDebug() << "size" << m_vectorOfData.size(); // i - number of lines

        for(int i = 0; i < m_vectorOfData.size(); i++)
        {
            m_x = m_vectorOfData[i];
            for(int j = i+1; j < m_vectorOfData.size(); j++)
            {
                 m_y = m_vectorOfData[j];
                 int size;
                 size = m_y.size();

                 qDebug() << i+1 << " = X ";
                 qDebug() << j+1 << " = Y ";
                 qDebug() << "------------";

                 m_correlationRes2 = correl(m_x, m_y);
                 m_indexesCorrel.push_back(m_correlationRes2);

                 m_y.clear();
            }
            m_x.clear();
        }
    qDebug() << m_indexesCorrel;

    return m_indexesCorrel;
}

QVector<double> Correlation::statistics(QVector <double> &res)
{
    QVector <double> stat;
    double tmp;

    for(int i = 0; i < res.size(); i++)
    {
        tmp = (res[i]/(sqrt(1-(res[i]*res[i])))) *
              (sqrt(m_vectorOfData.first().size()-2));
        stat.push_back(tmp);
    }

    return stat;
}

void Correlation::createResult()
{
    for(int i = 0; i < m_listOfValues.size(); i++)
        m_res.push_back(m_listOfValues[i][1].toDouble());
     m_vectorOfData.append(m_res);
}

void Correlation::process()
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



