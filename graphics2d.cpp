#include "graphics2d.h"
#include "algorithm"

#include <QDesktopWidget>
#include <QScreen>

Graphics2D::Graphics2D(bool _oneOrMuch,
                       QVector <QVector <double> >  _vectorOfData,
                       int _size,
                       QStringList _nameStations,
                       QVector<double> sunRise,
                       QVector<double> sunSet,
                       Ui::MainWindow* _ui, QObject* parent)
    :QObject(parent)
{
    m_vectorOfData      = _vectorOfData;
    m_size              = _size;
    m_ui                = _ui;
    m_oneOrMuchGraph    = _oneOrMuch;
    m_StationName       = _nameStations;
    m_sunRise           = sunRise;
    m_sunSet            = sunSet;
}

Graphics2D::~Graphics2D()
{
    m_StationName.clear();
}

double Graphics2D::maximumValue(QVector<double> vec)
{
    double max = vec[0];
    for(int i = 0 ; i < vec.size() ; i++)
        if(vec[i] > max)
           max = vec[i];

    return max/1000000;
}

void Graphics2D::clonePlot()
{
    m_ui->gridLayoutForGraphics->setContentsMargins(1,1,1,1);
    QCustomPlot *plot = new QCustomPlot();
    m_plots.push_back(plot);
    m_ui->gridLayoutForGraphics->addWidget(plot);
}

void Graphics2D::addingPlot(QCustomPlot *_plot, QVector <double> _vectorOfValue)
{
    qDebug() << "Пройдено";
    QVector <double> x, y;
    double value;

    for (int i = 0; i < _vectorOfValue.size(); i++)
    {
        x.push_back(i);
        value = _vectorOfValue[i];
        if(value != 0)
            value = value/1000000;  // 10 в минус 6;
        y.push_back(value);
    }

    _plot->addGraph();
    _plot->graph()->setData(x, y);

    x.clear();
    y.clear();
}

void Graphics2D::setupPlot(QCustomPlot *_plot, double max)
{
    QVector <QString> vectorOfTimes_strings = calcTimeForVectorOfTicks_strings();
    QVector <double>  vectorOfTimes_values = calcTimeForVectorOfTicks_values();

    _plot->xAxis->setLabel("time");
    _plot->yAxis->setLabel("amplitude");

    _plot->yAxis->setRange(0, max);
    _plot->xAxis->setRange(0, 17280);

    _plot->xAxis->setAutoTicks(false);
    _plot->xAxis->setAutoTickLabels(false);

    _plot->xAxis->setTickVector(vectorOfTimes_values);
    _plot->xAxis->setTickVectorLabels(vectorOfTimes_strings);

    _plot->xAxis->setTickLabelRotation(30);
    _plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8, 4));

    _plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

void Graphics2D::buildSimpleGraph()
{
    int n;
    n = m_vectorOfData.size();
    double max;

    for(int i = 0; i < n; i++)
    {
        max = maximumValue(m_vectorOfData[i]);
        clonePlot();
        addingPlot(m_plots[i], m_vectorOfData[i]);
        setupPlot(m_plots[i], max);
        m_plots[i]->legend->setVisible(true);
        m_plots[i]->graph()->setName(m_StationName[i]);
        cutNight(m_sunRise, m_sunSet);
        saveGraphAsPic(m_plots[i], m_StationName[i]);
    }    
}

void Graphics2D::buildGraphWithMeans()
{
    int n;
    n = m_vectorOfData.size()-1;
    double max;

    for(int i = 0; i < n; i++)
    {
         max = maximumValue(m_vectorOfData[i]);
         clonePlot();
         addingPlot(m_plots[i], m_vectorOfData[i]);
         setupPlot (m_plots[i], max);
    }

    addingPlot(m_plots[0], m_vectorOfData[1]);

    m_plots[0]->graph(0)->setPen(QPen(Qt::darkGreen));
    m_plots[0]->graph(1)->setPen(QPen(Qt::darkRed));

    m_plots[0]->legend->setVisible(true);
    m_plots[0]->graph(1)->setName(m_StationName[0]);
    m_plots[0]->graph(0)->setName("Means");

}

void Graphics2D::buildGraphics()
{
    if(m_oneOrMuchGraph == true)
        buildGraphWithMeans();
    if(m_oneOrMuchGraph == false)
        buildSimpleGraph();
}

void Graphics2D::cutNight(QVector<double> &sunRise,
                          QVector<double> &sunSet)
{
    QVector <double> x, x2, y;

    for(int i = 0; i < m_plots.size(); i++)
    {
        for(int j = 0; j < 160; j++)
        {
            y.push_back(j);
            x.push_back(sunRise[i]*720);
            x2.push_back(sunSet[i]*720);
        }

        m_plots[i]->addGraph();
        m_plots[i]->graph()->setData(x,y);
        m_plots[i]->graph()->removeFromLegend();
        x.clear();
        m_plots[i]->graph()->setPen(QPen(Qt::darkMagenta));
        m_plots[i]->addGraph();
        m_plots[i]->graph()->setData(x2,y);
        m_plots[i]->graph()->removeFromLegend();
        x2.clear();
        m_plots[i]->graph()->setPen(QPen(Qt::darkMagenta)); 
        y.clear();
    }
}

QVector<double> Graphics2D::calcTimeForVectorOfTicks_values()
{
    QVector<double> times;

    for(int i = 0; i < 25; i++)
        times.push_back(720*i);

    return times;
}

void Graphics2D::saveGraphAsPic(QCustomPlot *_plot, QString nameStaion)
{
    QString fileName;
    fileName = nameStaion + "_pic.jpg";
    qDebug() << fileName;
    _plot->saveJpg(fileName, 1600, 900);
}

QVector<QString> Graphics2D::calcTimeForVectorOfTicks_strings()
{
    QVector <QString> times;

    QTime time(00, 00, 00);
    QString tmp;
    for(int i = 0; ; i++)
    {
        QTime time2;
        time2 = time.addSecs(3600*i);
        tmp = time2.toString("hh:mm:ss");
        times.push_back(tmp);
     //   if((time2.hour() == 23) && (time2.minute() == 59) && (time2.second() == 55))
        if(time2.hour() == 23)
           break;
    }
    times.push_back("23:59:55");
    qDebug() << "m_times.size: " << times.size();
    return times;
}

void Graphics2D::vertScrollBarChanged(int value)
{
    qDebug() <<  "vertScrollBar/ Пройдено";

    for(int i = 0; i < m_plots.size(); i++)
    {
        m_plots.at(i)->yAxis->setRange(-value/50.0, m_plots.at(i)->yAxis->range().size());
        m_plots.at(i)->replot();
    }
}











