#ifndef GRAPH_H
#define GRAPH_H

#include "Printer.h"
#include <QAbstractSeries>
#include <QBarSeries>
#include <QPieSeries>

class Graph : public Printer // класс Graph является наследником класса Printer
{
public:
    //Класс QMap - это шаблонный класс, который предоставляет ассоциативный массив.
    // Используем переопределение , чтобы предотвратить непреднамеренное наследование в коде.
    void getData (QMap<QString, int>) override;
};

#endif // GRAPH_H
