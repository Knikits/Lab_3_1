#ifndef GRAPH_H
#define GRAPH_H

#include "printer.h"
#include <memory>

#include <QAbstractSeries>
#include <QBarSeries>
#include <QPieSeries>

class Graph : public Printer
{
public:
    Graph();
    void getData (QMap<QString, int>) override;
};

#endif // GRAPH_H
