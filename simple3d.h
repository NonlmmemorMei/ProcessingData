#ifndef SIMPLE3D_H
#define SIMPLE3D_H

#include "dataforgraphics.h"

class Simple3D : public DataForGraphics
{
public:
    Simple3D(const QStringList &_fileName);
    ~Simple3D(){}

    void                            createMass();
    void                            process();
    double*                         getArrayForCreate3DGraph();
    double                          getMaxValueForLegeng();
    QVector <QVector <double> >     getDataFor2D();

};

#endif // SIMPLE3D_H

