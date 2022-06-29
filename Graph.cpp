#include "Graph.h"

Graph::Graph() {}

void Graph::getData(QMap<QString, int> map)
{
    bar = new QBarSeries();
    pie = new QPieSeries();
    QStringList category;
    int count = 0;
    for (auto elem = map.begin(); elem != map.end(); elem++)
    {
        count++;
        if (count > 20) break;
        QBarSet* barS = new QBarSet(elem.key());
        pie->append(elem.key(), elem.value());
        category.append(elem.key());
        *barS << elem.value();
        bar->append(barS);
    }
}
