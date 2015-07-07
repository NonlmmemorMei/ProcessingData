#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QSplashScreen>
#include <QTimer>
#include <QMessageBox>

//#include "stdafx.h"
#include <stdlib.h>
#include <qthread.h>
#include <stdio.h>
#include <math.h>
#include "string.h"
#include "alglib/fasttransforms.h"


class I : public QThread
{
public:
static void sleep(unsigned long secs)
    {
        QThread::sleep(secs);
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap("E:/Projects/ProcessingDataRefactoring/resources/catpic.jpg");

    QSplashScreen *splash = new QSplashScreen(pixmap);

    splash->show();
    splash->showMessage(QObject::tr("Loading Programm..."),
                        Qt::AlignLeft | Qt::AlignTop, Qt::white);
    qApp->processEvents();
    MainWindow w;
    I::sleep(1);
    w.show();
    splash->finish(&w);

    return a.exec();
}
