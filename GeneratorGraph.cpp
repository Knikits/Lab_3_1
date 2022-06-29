#include "GeneratorGraph.h"

GeneratorGraph::GeneratorGraph() {}

QChartView* GeneratorGraph::GeneratorBar(QBarSeries * barS, bool color)
{
    QChart* chart = new QChart();
    if (color) // если график черно-белый
    {
        int j = 0;
        for (auto set : barS->barSets())
        {
            set -> setColor(QColor(j,j,j));
            j = j + 25;
        }
    }
    else // если цветной график
    {
        for(auto set : barS->barSets())
        {
            set->setColor(QColor(qrand()%256, qrand()%256, qrand()%256));
        }
    }
}

QChartView* GeneratorGraph::GeneratorPie(QPieSeries * barS, bool color)
{

}

void GeneratorGraph::PDF(QChartView *chView)
{

}
