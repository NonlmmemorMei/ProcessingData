#include "qfunc3d.h"
#include <qwt3d_surfaceplot.h>

QFunc3D::QFunc3D(Qwt3D::SurfacePlot *sp, double *x, double *y, double *z, int _xSize, int _ySize) :
    Function(sp){
    m_x = (double *)malloc((_xSize + _ySize + _xSize * _ySize)*sizeof(double));
    m_y = m_x + _xSize;
    m_z = m_y + _ySize;
    for (int i = 0; i < _xSize; i++)
        m_x[i] = x[i];
    for (int j = 0; j < _ySize; j++)
    {
        m_y[j] = y[j];
        for (int k = 0; k < _xSize; k++)
             m_z[j *_xSize + k] = z[j * _xSize + k];
    }
    m_xSize = _xSize;
    m_ySize = _ySize;
}

QFunc3D::~QFunc3D()
{
    free((void *)m_x);
}

double QFunc3D::operator()(double x, double y)
{
    double X = (m_x[m_xSize - 1] - m_x[0]) / (m_xSize - 1);
    int n = floor((x - m_x[0])/X + 0.5);
    if (n < 0 || n > m_xSize - 1)
        return 0;
    double Y = (m_y[m_ySize - 1] - m_y[0]) / (m_ySize-1);
    int m = floor((y - m_y[0])/Y + 0.5);
    return m_z[m * m_xSize + n];
}
