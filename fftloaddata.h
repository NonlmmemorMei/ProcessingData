#ifndef FFTLOADDATA_H
#define FFTLOADDATA_H

#include "dataforgraphics.h"
#include "fft.h"
//#include "alglib/stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "string.h"
#include "alglib/fasttransforms.h"

using namespace alglib;

class FftLoadData : public DataForGraphics
{
public:
    FftLoadData(const QStringList &_fileName);
    ~FftLoadData(){}

    QVector< QVector<double> >           movingAverage(QVector<double> input, QVector<QVector<double> > output,
                                                       int n);
    const QVector< QVector<double> >&    getYVec();
    void                                 createMass();
    void                                 process();
    double*                              getArrayForCreate3DGraph();
    double                               getMaxValueForLegeng();
    QVector <QVector <double> >          getDataFor2D();

private:
    QVector  <double>                    m_tmpVector;
    QVector <QVector <double> >          m_tmpVector2;
    QVector <QVector <double> >          m_y2;
    double*                             m_result;

};

#endif // FFTLOADDATA_H
