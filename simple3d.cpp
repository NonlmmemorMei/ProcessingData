#include "simple3d.h"

Simple3D::Simple3D(const QStringList &_fileName)
    :DataForGraphics()
{
    m_fileName = _fileName;
}

void Simple3D::createMass()
{
    for(int i = 0; i < m_listOfValues.size(); i++)
        m_res.push_back(m_listOfValues[i][1].toDouble());
    m_vectorOfData.append(m_res);
}

void Simple3D::process()
{
    for(int i = 0; i < m_fileName.size(); i++)
    {
        m_file.setFileName(m_fileName[i]);
        csvReadFile(m_file, m_listOfValues);
        createMass();
        m_res.clear();
        m_listOfValues.clear();
    }
    m_xSize = m_vectorOfData.size();
    m_ySize = m_vectorOfData.first().size();
}


double *Simple3D::getArrayForCreate3DGraph()
{
    double min, max;
    min = minValue();
    max = maxValue();

    m_result = (double *)malloc((m_ySize * m_xSize) * sizeof(double));
    for (int i = 0; i < m_ySize; i++)
    {
        for (int j = 0; j < m_xSize; j++)
            m_result[i * m_xSize + j] = ((m_vectorOfData[j][i] - min)/(max - min));
    }
    return m_result;
}

double Simple3D::getMaxValueForLegeng()
{
    double min, max, max2;
    min = minValue();
    max = maxValue();
    max2 =((m_vectorOfData[0][0] - min)/(max - min));

    for(int i = 0; i < m_vectorOfData.size(); i++)
    {
        for(int j = 0; j < m_vectorOfData.first().size(); j++)
        {
            if((m_vectorOfData[i][j] - min)/(max - min) > max2)
                max2 = (m_vectorOfData[i][j] - min)/(max - min);
        }
     }
     m_vectorOfData.clear();

     return max2;
}

QVector<QVector<double> > Simple3D::getDataFor2D(){}




