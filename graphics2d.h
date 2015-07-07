#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <QObject>

#include "qcustomplot.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataforcalculation.h"

#include "algorithm"

class Graphics2D : public QObject
{
     Q_OBJECT
public:
    Graphics2D(bool _oneOrMuch,
               QVector <QVector <double> >  _vectorOfData,
               int _size, QStringList _nameStations,
               QVector<double> sunRise, QVector<double> sunSet,
               Ui::MainWindow *_ui = 0, QObject *parent = 0);
    ~Graphics2D();

    double maximumValue(QVector <double> vec);
    void clonePlot();
    void addingPlot(QCustomPlot *_plot, QVector<double> _vectorOfValue);
    void setupPlot(QCustomPlot *_plot, double max);
    void buildSimpleGraph();
    void buildGraphWithMeans();
    void buildGraphics();
    void cutNight(QVector<double> &sunRise, QVector<double> &sunSet);
    QVector<QString> calcTimeForVectorOfTicks_strings();
    QVector<double>  calcTimeForVectorOfTicks_values();
    void saveGraphAsPic(QCustomPlot *_plot, QString nameStaion);

    
private slots:
//  void horzScrollBarChanged(int value);
    void vertScrollBarChanged(int value);

    
private:
    QVector <QVector <double> > m_vectorOfData;
    QVector <QCustomPlot *>     m_plots;
    Ui::MainWindow*             m_ui;
    int                         m_size;
    bool                        m_oneOrMuchGraph;
    QStringList                 m_StationName;
    QVector <double>            m_sunRise, m_sunSet;


};

#endif // GRAPHICS2D_H
