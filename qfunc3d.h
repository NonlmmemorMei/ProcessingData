#ifndef QFUNC3D_H
#define QFUNC3D_H

#include <qwt3d_function.h>

class QFunc3D : public Qwt3D::Function
{
public:
    QFunc3D(Qwt3D::SurfacePlot *, double *,double *,double *,
            int,int);
    ~QFunc3D();

    double      operator()(double, double);

private:
    double*     m_x, *m_y, *m_z;
    int         m_xSize, m_ySize;
};

#endif // QFUNC3D_H

