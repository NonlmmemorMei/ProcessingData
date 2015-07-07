#-------------------------------------------------
#
# Project created by QtCreator 2014-07-08T14:54:32
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ProcessingDataRefactoring
TEMPLATE = app

include(qwtplot3d.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    cut.cpp \
    concatenator.cpp \
    correlation.cpp \
    qcustomplot.cpp \
    simple3d.cpp \
    graphics3d.cpp \
    letter.cpp \
    qfunc3d.cpp \
    timeitems.cpp \
    sunrisesunsettime.cpp \
    dataforgraphics.cpp \
    fft.cpp \
    fftloaddata.cpp \
    dataforcalculation.cpp \
    graphics2d.cpp \
    simple2d.cpp \
    alglib/alglibinternal.cpp \
    alglib/alglibmisc.cpp \
    alglib/ap.cpp \
    alglib/dataanalysis.cpp \
    alglib/diffequations.cpp \
    alglib/fasttransforms.cpp \
    alglib/integration.cpp \
    alglib/interpolation.cpp \
    alglib/linalg.cpp \
    alglib/optimization.cpp \
    alglib/solvers.cpp \
    alglib/specialfunctions.cpp \
    alglib/statistics.cpp \
    mean.cpp

HEADERS  += mainwindow.h \
    cut.h \
    concatenator.h \
    correlation.h \
    qcustomplot.h \
    simple3d.h \
    graphics3d.h \
    letter.h \
    qfunc3d.h \
    timeitems.h \
    sunrisesunsettime.h \
    dataforgraphics.h \
    fft.h \
    fftloaddata.h \
    dataforcalculation.h \
    graphics2d.h \
    simple2d.h \
    alglib/alglibinternal.h \
    alglib/alglibmisc.h \
    alglib/ap.h \
    alglib/dataanalysis.h \
    alglib/diffequations.h \
    alglib/fasttransforms.h \
    alglib/integration.h \
    alglib/interpolation.h \
    alglib/linalg.h \
    alglib/optimization.h \
    alglib/solvers.h \
    alglib/specialfunctions.h \
    alglib/statistics.h \
    alglib/stdafx.h \
    mean.h

FORMS    += mainwindow.ui
