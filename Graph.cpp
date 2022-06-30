#include "Graph.h"

void Graph::getData(QMap<QString, int> map)
{
    bar = new QBarSeries();
    pie = new QPieSeries();
    QStringList category;
    int count = 0;
    for (auto i = map.begin(); i != map.end(); i++)
    {
        if (count > 20) break; // берём первые 20 данных из бд
        //if (count > 100) break; // берём первые 100 данных из бд
        QBarSet* barS = new QBarSet(i.key());
        pie->append(i.key(), i.value());
        category.append(i.key());
        *barS << i.value();
        bar->append(barS);
        count++;
    }
}
