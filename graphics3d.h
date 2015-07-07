#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H

#include "qfunc3d.h"
#include "timeitems.h"
#include "letter.h"
#include "simple3d.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QGridLayout>
#include <qwt3d_surfaceplot.h>
#include <QLabel>
#include <QDebug>

class Graphics3D : public QObject
{
    Q_OBJECT

public:
    explicit Graphics3D(double *data, int xSize, int ySize,
                        int maxValue, const QStringList freq,
                        double beginTime, double endTime,
                        Ui::MainWindow *ui = 0, QObject *parent = 0);
    ~Graphics3D(){}

private slots:
    void                        on_actionRestore_triggered();
    void                        procRotate(double, double, double);
    void                        showRotate(double, double, double);
    void                        showShift(double, double);
    void                        showScale(double, double, double);
    void                        showZoom(double);
    int                         setNumberMajors();


private:
    int                         m_xSize, m_ySize;
    int                         m_majors, m_maxValueOfColorLegeng;
    double                      m_beginTime, m_endTime;
    double*                     m_data;
    QStringList                 m_labs;
    QStringList                 m_freq;
    QLabel*                     rotateLabel;
    QLabel*                     shiftLabel;
    QLabel*                     scaleLabel;
    QLabel*                     zoomLabel;
    Qwt3D::SurfacePlot *        surf;
};

#endif // GRAPHICS3D_H
