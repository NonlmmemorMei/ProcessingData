#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionCut,            SIGNAL(triggered()),  this, SLOT(cutFile()));
    connect(ui->actionConcatenate,    SIGNAL(triggered()),  this, SLOT(concatenateFiles()));
    connect(ui->actionCorrelation,    SIGNAL(triggered()),  this, SLOT(correlation()));
    connect(ui->action3DMake,         SIGNAL(triggered()),  this, SLOT(make3DGraph()));
    connect(ui->actionSpectrumMake,   SIGNAL(triggered()),  this, SLOT(makeFft()));
    connect(ui->action2DMake,         SIGNAL(triggered()),  this, SLOT(make2DGraph()));
    connect(ui->action2DMakeWithMean, SIGNAL(triggered()),  this, SLOT(makeMeans()));

    ui->actionShowHideDockInput->toggled(false);
}

inline int min(int a, int b)
{
    return (a > b) ? b : a;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearGridLayout()
{
    QLayout* layout = ui->gridLayoutForGraphics;
    QLayoutItem* item;
    if(layout->count() != 0)
    {
        while( (item = layout->itemAt(0)) )
        {
            layout->removeItem(item);
            layout->removeWidget(item->widget());
            delete item->widget();
            delete item;
            layout->update();
        }
    }
}

QStringList MainWindow::selectFiles()
{
    QStringList _files;
    _files = QFileDialog::getOpenFileNames(this, "Open File","","");
    if(_files.isEmpty())
       ui->textEdit->append("Файлы не загружены. Повторите выбор файлов.");
    else
    {
        ui->textEdit->append("Файлы загружены: ");
        for(int i = 0; i < _files.size(); i++)
            ui->textEdit->append(_files[i]);
    }
    return _files;
}

QString MainWindow::selectDirectory()
{
    QString _directoryPath;
    _directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly);
    if(_directoryPath.isEmpty())
       ui->textEdit->append("Директория не выбрана. Повторите выбор директории.");
    else
    {
        ui->textEdit->append("Директория выбрана: ");
        ui->textEdit->append(_directoryPath);
    }
    return _directoryPath;
}

void MainWindow::cutFile()
{
    m_fileNames     = selectFiles();
    m_directoryPath = selectDirectory();

    DataForCalculation* cut = new Cut(m_fileNames[0], m_directoryPath);
    cut->process();

    QMessageBox* message = new QMessageBox(this);
    message->setIcon(QMessageBox::Information);
    message->setText("Выполнено");
    message->show();

    delete cut;
}

void MainWindow::concatenateFiles()
{
    DataForCalculation* concatenate;

    m_fileNames     = selectFiles();
    m_fileNames2    = selectFiles();
    m_directoryPath = selectDirectory();

    int size = min(m_fileNames.size(), m_fileNames2.size());
    qDebug() << "Количество загруженных файлов: " << size << endl;

    for(int i = 0; i < size; i++)
    {
        concatenate = new Concatenator(m_fileNames[i], m_fileNames2[i],
                                       m_directoryPath);
        concatenate->process();
    }
    QMessageBox* message = new QMessageBox(this);
    message->setIcon(QMessageBox::Information);
    message->setText("Выполнено");
    message->show();

    delete concatenate;
}

void MainWindow::correlation()
{
    clearGridLayout();
    m_fileNames = selectFiles();
    int size    = m_fileNames.size();

    qDebug() << "Количество загруженных файлов: " << size << endl;

    QVector <double> statistics;
    QVector <QString> names;
    QVector <QString> tmp1, tmp2;
    QString tmp, name, power;
    QColor color;

    Correlation* corr = new Correlation(m_fileNames);
    corr->process();
    m_resCorr = corr->calcCorrel();
    statistics = corr->statistics(m_resCorr);

    QTableWidget *tableWidget = new QTableWidget(m_resCorr.size(), 5, this);
    ui->gridLayoutForGraphics->addWidget(tableWidget, 0, 0);

    ui->textEdit->append("Результаты корреляции: ");

    for(int i = 0; i < m_fileNames.size(); i++)
    {
        for(int j = i+1; j < m_fileNames.size(); j++)
        {
            name = "между " + corr->cuttedName(m_fileNames[i]) + " и "
                   + corr->cuttedName(m_fileNames[j]) + " = ";
            names.push_back(name);
            tmp1.push_back(corr->cuttedName(m_fileNames[i]));
            tmp2.push_back(corr->cuttedName(m_fileNames[j]));
        }
    }

    for(int i = 0; i < m_resCorr.size(); i++)
    {
        if(((m_resCorr[i] >= 1) && (m_resCorr[i] <= -0.8)) ||
           ((m_resCorr[i] >= 0.8) && (m_resCorr[i] <= 1)))
        {
            power = " - корреляция сильная";
            ui->textEdit->setTextColor(QColor(178, 34, 34));
            color = Qt::red;
        }

        if(((m_resCorr[i] >= -0.8) && (m_resCorr[i] <= -0.5)) ||
           ((m_resCorr[i] >= 0.5) && (m_resCorr[i] <= 0.8)))
        {
            power = " - корреляция существенная";
            ui->textEdit->setTextColor(QColor(21, 96, 189));
            color = Qt::yellow;
        }

        if((m_resCorr[i] >= -0.5) && (m_resCorr[i] <= 0.5))
        {
            power = " - корреляция слабая";
            ui->textEdit->setTextColor(QColor(3, 192, 60));
            color = Qt::green;

        }

        QTableWidgetItem *item = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        QTableWidgetItem *item4 = new QTableWidgetItem();
        QTableWidgetItem *item5 = new QTableWidgetItem();

        item->setText(tmp1[i]);
        item2->setText(tmp2[i]);
        item3->setText(QString::number(m_resCorr[i]));

        item4->setText(power);
        item5->setText(QString::number(statistics[i]));

        tableWidget->setItem(i,0,item);
        tableWidget->setItem(i,1,item2);
        tableWidget->setItem(i,2,item3);
        item4->setBackgroundColor(color);
        tableWidget->setItem(i,3,item4);
        tableWidget->setItem(i,4,item5);

        tmp = names[i] + QString::number(m_resCorr[i]) + power;
        ui->textEdit->append(tmp);
    }
    ui->textEdit->setTextColor(QColor(0,0,0));

    delete corr;
}

void MainWindow::make3DGraph()
{
    Graphics3D* graphics3D;
    m_fileNames = selectFiles();
    int size    = m_fileNames.size();

    qDebug() << "Количество загруженных файлов: " << size << endl;

    clearGridLayout();
    DataForGraphics* simple3D = new Simple3D(m_fileNames);
    simple3D->process();

    m_frequences = simple3D->getFrequences();
    m_array = simple3D->getArrayForCreate3DGraph();
    m_maxValue = simple3D->getMaxValueForLegeng();
    m_xAxisSize = simple3D->getXAxisSize();
    m_yAxisSize = simple3D->getYAxisSize();
    m_sunRiseTime = simple3D->getSunRiseTime(m_fileNames[11]);
    m_sunSetTime = simple3D->getSunSetTime(m_fileNames[11]);

    qDebug() << "m_sunRiseTime" << m_sunRiseTime;
    qDebug() << "m_sunSetTime" << m_sunSetTime;


    graphics3D  = new Graphics3D(m_array, m_xAxisSize, m_yAxisSize, m_maxValue,
                                 m_frequences, 0, 17280, ui);
    ui->action3DRestore->setEnabled(true);


    QString file = "1.jpg";

    ui->frame->grab().save(file);

    delete simple3D;
    delete graphics3D;
}

void MainWindow::makeFft()
{    
    m_fileNames = selectFiles();

    clearGridLayout();
    DataForGraphics* fftLoadData = new FftLoadData(m_fileNames);
    fftLoadData->process();

    m_xAxisSize = fftLoadData->getXAxisSize();
    m_yAxisSize = fftLoadData->getYAxisSize();
    m_maxValue = fftLoadData->getMaxValueForLegeng();
    m_array = fftLoadData->getArrayForCreate3DGraph();
    m_frequences = fftLoadData->getFrequences();

    Graphics3D* graphics3D;
    graphics3D = new Graphics3D(m_array, m_xAxisSize, m_yAxisSize, m_maxValue,
                                m_frequences, 0, 17280, ui);
    ui->actionSpectrumRestore->setEnabled(true);


    delete fftLoadData;
    delete graphics3D;
}

void MainWindow::make2DGraph()
{
    QVector <double> timeSunRise, timeSunSet;
    m_fileNames = selectFiles();
    clearGridLayout();

    DataForGraphics* simple2D = new Simple2D(m_fileNames);
    simple2D->process();
    m_vectorOfData = simple2D->getDataFor2D();

    for(int i = 0; i < m_fileNames.size(); i++)
    {
        m_graphName  = simple2D->cutName(m_fileNames[i]);
        timeSunRise.push_back(simple2D->sunRiseSunSet(true, m_fileNames[i]));
        timeSunSet.push_back(simple2D->sunRiseSunSet(false, m_fileNames[i]));
        m_graphNames.append(m_graphName);
    }

    qDebug() << timeSunRise << timeSunSet;

    Graphics2D* graphics2D = new Graphics2D(false, m_vectorOfData,
                                            m_vectorOfData.size(),
                                            m_graphNames,
                                            timeSunRise,
                                            timeSunSet, ui);
    graphics2D->buildGraphics();
  //  for(int i = 0; i < m_fileNames.size(); i++)
  //      graphics2D->cutNight(timeSunRise, timeSunSet);

    m_graphNames.clear();

    delete graphics2D;
    delete simple2D;
}

void MainWindow::makeMeans()
{
    QVector <double> timeSunRise, timeSunSet;

    m_fileNames = selectFiles();
    m_fileNames2 = selectFiles();
    clearGridLayout();


    DataForGraphics* simple2D = new Simple2D(m_fileNames2);
    simple2D->process();
    m_vectorOfData = simple2D->getDataFor2D();

    for(int i = 0; i < m_fileNames.size(); i++)
    {
        m_graphName  = simple2D->cutName(m_fileNames[i]);
        timeSunRise.push_back(simple2D->sunRiseSunSet(true, m_fileNames[i]));
        timeSunSet.push_back(simple2D->sunRiseSunSet(false, m_fileNames[i]));
        m_graphNames.append(m_graphName);
    }

    m_graphName = simple2D->cutName(m_fileNames2[0]);
    m_graphNames.append(m_graphName);

    Mean* mean = new Mean(m_fileNames, m_fileNames2);
    mean->process();
    QVector <double> means;
    means = mean->means();
    m_vectorOfData.append(means);

    Graphics2D* graphics2D = new Graphics2D(true ,m_vectorOfData,
                                            m_vectorOfData.first().size(),
                                            m_graphNames,
                                            timeSunRise,
                                            timeSunSet, ui);

    graphics2D->buildGraphics();

    delete simple2D;
    delete mean;
    delete graphics2D;
}








