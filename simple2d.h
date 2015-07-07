#ifndef SIMPLE2D_H
#define SIMPLE2D_H

#include "dataforgraphics.h"

class Simple2D : public DataForGraphics
{
public:
    Simple2D(const QStringList &_fileName);
    ~Simple2D(){}

    void                            createMass();
    void                            process();
    double*                         getArrayForCreate3DGraph();
    double                          getMaxValueForLegeng();
    QVector <QVector <double> >     getDataFor2D();
};

#endif // SIMPLE2D_H
