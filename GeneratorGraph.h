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

class GeneratorGraph // класс генерации графиков
{
public:
    GeneratorGraph(); // конструктор класса
    QChartView *GeneratorBar(QBarSeries*, bool); // диаграммы
    QChartView *GeneratorPie(QPieSeries*, bool); // круг
    void PDF(QChartView* chView); // создание pdf
    //не успел реализовать вывод в JSON
    //void JSON(QChartView* chView);
};

#endif // GENERATORGRAPH_H
