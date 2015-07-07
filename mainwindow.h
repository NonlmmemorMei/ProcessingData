#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QException>
#include <QTableWidget>

#include "graphics3d.h"
#include "dataforcalculation.h"
#include "concatenator.h"
#include "cut.h"
#include "correlation.h"
#include "simple3d.h"
#include "graphics3d.h"
#include "fftloaddata.h"
#include "simple2d.h"
#include "graphics2d.h"
#include "mean.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow*   ui;
    void                clearGridLayout();

private slots:
    QStringList         selectFiles();
    QString             selectDirectory();
    void                cutFile();
    void                concatenateFiles();
    void                correlation();
    void                make3DGraph();
    void                makeFft();
    void                make2DGraph();
    void                makeMeans();

private:
    int                 m_xAxisSize, m_yAxisSize;
    int                 m_maxValue;
    double              m_sunRiseTime, m_sunSetTime;
    double              m_timeSunRiseSunSet;
    double*             m_array;
    QString             m_directoryPath;
    QStringList         m_fileNames, m_fileNames2,
                        m_graphNames;
    QStringList         m_frequences;

    QVector <double>    m_resCorr;
    QVector <QVector <double> > m_vectorOfData;
    QString             m_graphName;



};

#endif // MAINWINDOW_H
