#ifndef LETTER_H
#define LETTER_H

#include "qwt3d_plot.h"
#include "simple3d.h"
#include "mainwindow.h"
#include <QTime>
#include <QDebug>

using namespace Qwt3D;

class Letter : public LinearScale
{
public:
    Letter(QStringList, int xSize);
    ~Letter();

    Scale*          clone() const;
    QString         ticLabel(unsigned int idx) const;

public:
    int             m_xSize;
    QStringList     m_frequency;
};



#endif // LETTER_H
