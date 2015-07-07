#ifndef TIMEITEMS_H
#define TIMEITEMS_H

#include "qwt3d_plot.h"
#include "simple3d.h"
#include "mainwindow.h"
#include <QTime>
#include <QDebug>

using namespace Qwt3D;


class TimeItems : public LinearScale
{
public:
    TimeItems();
    ~TimeItems();

    Scale*  clone() const;
    QString ticLabel(unsigned int idx) const;
};

#endif // TIMEITEMS_H
