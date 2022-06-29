#ifndef GENERATORGRAPH_H
#define GENERATORGRAPH_H

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>
#include <QPainter>
#include <QPdfWriter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

class GeneratorGraph
{
public:
    GeneratorGraph();
    QChartView *GeneratorBar(QBarSeries*, bool);
    QChartView *GeneratorPie(QPieSeries*, bool);
    void PDF(QChartView* chView);
    //void JSON(QChartView* chView);
};

#endif // GENERATORGRAPH_H
