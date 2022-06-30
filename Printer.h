#ifndef PRINTER_H
#define PRINTER_H

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>
#include <QMap>
#include <QString>

class Printer // абстрактный класс печати
{
public:
    //Класс QBarSeries представляет ряд данных в виде вертикальных столбцов,
    //сгруппированных по категориям.
    //Класс QPieSeries представляет данные в виде круговых диаграмм.
    QBarSeries *bar;
    QPieSeries *pie;
    QBarSeries* BarSeries() const {return bar;}
    QPieSeries* PieSeries() const {return pie;}
    Printer(); // конструктор класса
    virtual void getData (QMap<QString, int>) = 0; //виртуальный метод getData
};

#endif // PRINTER_H
