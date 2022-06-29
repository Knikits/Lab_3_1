#ifndef PRINTER_H
#define PRINTER_H

#include "DataGraph.h"
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>

class Printer
{
public:
    DataGraph *date;
    QBarSeries *bar;
    QPieSeries *pie;
    Printer();
    virtual void getData (QMap<QString, int>) = 0;
    QBarSeries* BarSeries() const {return bar;}
    QPieSeries* PieSeries() const {return pie;}
};

#endif // PRINTER_H
