#include "simple2d.h"

Simple2D::Simple2D(const QStringList &_fileName)
    :DataForGraphics()
{
    m_fileName = _fileName;
}

void Simple2D::createMass()
{
    for(int i = 0; i < m_listOfValues.size(); i++)
        m_res.push_back(m_listOfValues[i][1].toDouble());
    m_vectorOfData.append(m_res);
}

void Simple2D::process()
{
    for(int i = 0; i < m_fileName.size(); i++)
    {
        m_file.setFileName(m_fileName[i]);
        csvReadFile(m_file, m_listOfValues);
        createMass();
        m_res.clear();
        m_listOfValues.clear();
    }
}

double *Simple2D::getArrayForCreate3DGraph(){}
double Simple2D::getMaxValueForLegeng(){}

QVector<QVector<double> > Simple2D::getDataFor2D()
{
    return m_vectorOfData;
}

