#ifndef PRINTER_H
#define PRINTER_H

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>
#include <QMap>
#include <QString>

class Printer
{
public:
    QBarSeries *bar;
    QPieSeries *pie;
    Printer();
    virtual void getData (QMap<QString, int>) = 0;
    QBarSeries* BarSeries() const {return bar;}
    QPieSeries* PieSeries() const {return pie;}
};

#endif // PRINTER_H
