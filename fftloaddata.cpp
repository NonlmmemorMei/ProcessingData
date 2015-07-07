#include "fftloaddata.h"

FftLoadData::FftLoadData(const QStringList &_fileName)
    :DataForGraphics()
{
    m_fileName = _fileName;
}

QVector<QVector<double> > FftLoadData::movingAverage(QVector<double> input,
                                                     QVector<QVector<double> > output,
                                                     int n)
{
    int windowSize;
    double tmp;

    windowSize = 16;

    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < i+windowSize; j++)
        {
            tmp = input[j];
            m_tmpVector.append(tmp);
        }
        m_tmpVector2.append(m_tmpVector);
        m_tmpVector.clear();
        if(i == 17264)
           break;
     }
    ShortComplex arr[windowSize];

    real_1d_array x, x2;
    complex_1d_array f;

    x.setlength(windowSize);
    x2.setlength(windowSize);

    for(int i = 0; i < m_tmpVector2.size(); i++)
    {
       for(int j = 0; j < m_tmpVector2.first().size(); j++)
       {
           arr[j].re = m_tmpVector2[i][j];
           arr[j].im = 0.0;
           x[j] = m_tmpVector2[i][j];
       }
     fftr1d(x, f);
   //  printf("%s\n", f.tostring(1).c_str());

     universal_fft(arr, 16, false);
     fftc1d(f);
     fftr1dinv(f, 16, x2);
     printf("%s\n", x2.tostring(3).c_str());
     for(int j = 0; j < m_tmpVector2.first().size(); j++)
     {
      //  tmp = (sqrt((arr[j].re * arr[j].re) + (arr[j].im * arr[j].im)))/windowSize;
       tmp = x2[j];

       if(tmp != 0.0)
           tmp = log10(tmp);

        m_tmpVector.push_back(tmp);

      }
      qDebug() << m_tmpVector;
      output.append(m_tmpVector);
      m_tmpVector.clear();
     }
     return output;
}

const QVector<QVector<double> > &FftLoadData::getYVec()
{
    return m_y2;
}

void FftLoadData::createMass()
{
    for(int i = 0; i < m_listOfValues.size(); i++)
        m_res.push_back(m_listOfValues[i][1].toDouble());
    m_vectorOfData.append(m_res);
}

void FftLoadData::process()
{
    QVector <double> y;
    double value;

     m_xSize = 16;
     m_ySize = 17265;

     for(int i = 0; i < m_xSize; i++)
             m_listNameOfFrequencys.push_back("null");

     m_file.setFileName(m_fileName[0]);
     csvReadFile(m_file, m_listOfValues);
     createMass();

     int n = m_listOfValues.size();
     for(int i = 0; i < n; i++)
     {
        value = m_listOfValues[i][1].toDouble();
        y.push_back(value);
     }
     m_y2 = movingAverage(y, m_y2, n);
}

double *FftLoadData::getArrayForCreate3DGraph()
{
    m_result = (double *)malloc((m_xSize * m_ySize) * sizeof(double));
    for (int i = 0; i < m_y2.size(); i++)
    {
       for (int j = 0; j < m_y2.first().size(); j++)
            m_result[i * m_xSize + j] = m_y2[i][j];
    }
    return m_result;
}

double FftLoadData::getMaxValueForLegeng()
{
    double max;
    max = m_y2[0][0];

    for (int i = 0; i < m_y2.size(); i++)
    {
       for (int j = 0; j < m_y2.first().size(); j++)
           if(m_y2[i][j] > max)
              max = m_y2[i][j];
    }
    return max;
}

QVector <QVector <double> > FftLoadData::getDataFor2D(){}
