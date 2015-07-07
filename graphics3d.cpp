#include "graphics3d.h"


Graphics3D::Graphics3D(double *data, int xSize, int ySize,
                       int maxValue, const QStringList freq,
                       double beginTime, double endTime,
                       Ui::MainWindow *ui, QObject *parent)
    :QObject(parent)
{
    m_freq = freq;
    m_data = data;
    m_xSize = xSize;
    m_ySize = ySize;
    m_beginTime = beginTime;
    m_endTime = endTime;
    m_majors = setNumberMajors();
    m_maxValueOfColorLegeng = maxValue;

    ui->gridLayoutForGraphics->setContentsMargins(10,10,5,5);
    surf = new Qwt3D::SurfacePlot(ui->frame);
    ui->gridLayoutForGraphics->addWidget(surf, 0, 0);

    double *z = m_data;
    double *x = (double *)malloc((m_xSize+m_ySize)*sizeof(double));
    double *y = x + m_xSize;

    for (int i = 0; i < m_xSize; i++)
            x[i] = i;
    for (int i = 0; i < m_ySize; i++)
            y[i] = i;

    QFunc3D func(surf, x, y, z, m_xSize, m_ySize);

    func.setDomain(0, m_xSize, m_beginTime, m_endTime);
    func.setMesh(m_xSize, m_endTime);
    func.create();

    free((void *)x);
    free((void *)z);

    surf->setCoordinateStyle(Qwt3D::FRAME);  // Qwt3D::FRAME;
    surf->setPlotStyle(Qwt3D::FILLEDMESH);
    surf->setMeshColor(Qwt3D::RGBA(0,0,0,0));

    m_labs << "frequency" << "time" << "value";

    surf->legend()->setLimits(0, m_maxValueOfColorLegeng);
    surf->showColorLegend(true);
    surf->coordinates()->setNumberFont("Arial", 6);

    surf->coordinates()->setLabelFont("Arial", 13);

  //  surf->coordinates()->setLineSmooth(true);
    surf->coordinates()->setLineWidth(1);
    surf->coordinates()->setAxesColor(Qwt3D::RGBA(0, 0, 0, 2));

    surf->coordinates()->setAutoScale(false);

    for (int i = 0; i != (int)surf->coordinates()->axes.size(); i++)
    {
        if(i == 0 || i == 3 || i == 4 || i == 5)  // x
        {
            surf->coordinates()->axes[i].setMajors(m_majors);
            surf->coordinates()->axes[i].setScale(new Letter(m_freq, m_xSize));
        }
            if(i == 1 || i == 6 || i == 7 || i == 8) // y
            {
                 surf->coordinates()->axes[i].setMajors(24);
                 surf->coordinates()->axes[i].setMinors(720);
                 surf->coordinates()->axes[i].setScale(new TimeItems);
            }
                if(i == 2 || i == 9 || i == 10 || i == 11) // z
                {
                    surf->coordinates()->axes[i].setMajors(5);
                    surf->coordinates()->axes[i].setMinors(4);
                }
    }

    surf->coordinates()->setGridLinesColor(Qwt3D::RGBA(0, 0, 0, 2));

    surf->updateGL();

    surf->coordinates()->adjustNumbers(6);
    surf->coordinates()->adjustLabels(70);
    double majl = (surf->coordinates()->second()-surf->coordinates()->first()).length() / 10000;

    surf->coordinates()->setTicLength(majl,0.4*majl);
    surf->updateGL();

    rotateLabel = new QLabel(ui->statusBar);
    ui->statusBar->addWidget(rotateLabel,0);
        shiftLabel = new QLabel(ui->statusBar);
        ui->statusBar->addWidget(shiftLabel,0);
            scaleLabel = new QLabel(ui->statusBar);
            ui->statusBar->addWidget(scaleLabel,0);
                zoomLabel = new QLabel(ui->statusBar);
                ui->statusBar->addWidget(zoomLabel,0);

    connect(surf,                   SIGNAL(rotationChanged(double,double,double)), this, SLOT(procRotate(double,double,double)));
    connect(surf,                   SIGNAL(rotationChanged(double,double,double)), this, SLOT(showRotate(double,double,double)));
    connect(surf,                   SIGNAL(vieportShiftChanged(double,double)),    this, SLOT(showShift(double,double)));
    connect(surf,                   SIGNAL(scaleChanged(double,double,double)),    this, SLOT(showScale(double,double,double)));
    connect(surf,                   SIGNAL(zoomChanged(double)),                   this, SLOT(showZoom(double)));
    connect(ui->action3DRestore,    SIGNAL(triggered()),                           this, SLOT(on_actionRestore_triggered()));
    on_actionRestore_triggered();
    showShift(0,0);   


    //QImage image = mpPlot->grabFrameBuffer( );
      //QPixmap image = mpPlot->renderPixmap( );
//    glReadBuffer( GL_COLOR_BUFFER_BIT );
//    glReadPixels();
//    QPixmap image = surf->grab();
//    if( !image.save( "1.jpg", "JPG" ) )
//         //QMessageBox::warning("Error saving image." );
//        qDebug() << "error saving image";

    //surf->makeCurrent();
   // surf->renderPixmap(1000, 1000).save("111.jpg", "JPG");

    QImage img = surf->grabFrameBuffer();

    img.save("file.jpg");


}

void Graphics3D::on_actionRestore_triggered()
{
    surf->setRotation(35,0,-20);
    surf->setViewportShift(0,0);
    surf->setScale(500,2,3000);
    surf->setZoom(0.95);

    surf->updateData();
    surf->updateGL();
}

void Graphics3D::procRotate(double x, double y, double z)
{
    x *= M_PI/180;
    y *= M_PI/180;
    z *= M_PI/180;

    int gl = Qwt3D::NOSIDEGRID;

    double sp = cos(x)*sin(z) + sin(x)*sin(y)*cos(z);
    if (sp < 0) gl |= Qwt3D::LEFT;
    if (sp > 0) gl |= Qwt3D::RIGHT;

    sp = cos(x)*cos(z) - sin(x)*sin(y)*sin(z);
    if (sp < 0) gl |= Qwt3D::FRONT;
    if (sp > 0) gl |= Qwt3D::BACK;

    sp = -sin(x)*cos(y);
    if (sp < 0) gl |= Qwt3D::FLOOR;
    if (sp > 0) gl |= Qwt3D::CEIL;

    surf->coordinates()->setGridLines(true,false,gl);
}

void Graphics3D::showRotate(double x, double y, double z)
{
    rotateLabel->setText(" Angles (" +
                                     QString::number(x,'g',3) + ", " +
                                     QString::number(y,'g',3) + ", " +
                                     QString::number(z,'g',3) + ")  ");
}

void Graphics3D::showShift(double x, double y)
{
    shiftLabel->setText(" Shifts (" +
                                    QString::number(x,'g',3) + ", " +
                                    QString::number(y,'g',3) + ")  ");
}

void Graphics3D::showScale(double x, double y, double z)
{
    scaleLabel->setText(" Scales (" +
                                    QString::number(x,'g',3) + ", " +
                                    QString::number(y,'g',3) + ", " +
                                    QString::number(z,'g',3) + ")  ");
}

void Graphics3D::showZoom(double z)
{
    zoomLabel->setText("{Zoom "  +
                                    QString::number(z,'g',3) + "  ");
}

int Graphics3D::setNumberMajors()
{
    m_majors = m_xSize - 1;
    return m_majors;
}






