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
    chart->addSeries(barS);
    chart->setTitle("График диаграммный");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *view = new QChartView(chart);
    return view;
}

QChartView* GeneratorGraph::GeneratorPie(QPieSeries * pieS, bool color)
{
    QChart* chart = new QChart();
    if (color) // если график черно-белый
    {
        int j = 0;
        for (auto set : pieS->slices())
        {
            set -> setColor(QColor(j,j,j));
            j = j + 25;
        }
    }
    else // если цветной график
    {
        for(auto set : pieS->slices())
        {
            set->setColor(QColor(qrand()%256, qrand()%256, qrand()%256));
        }
    }
    chart->addSeries(pieS);
    chart->setTitle("График круговой");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *view = new QChartView(chart);
    return view;
}

void GeneratorGraph::PDF(QChartView *chView)
{
    QPrinter printerGrayColor;
    printerGrayColor.setOutputFormat(QPrinter::PdfFormat);
    printerGrayColor.setOutputFileName("D:/ChartInPdf.pfpdf");
    QPainter painterG;
    if (!painterG.begin(&printerGrayColor))
    {
        qDebug() << "###ERROR file not create";
        return;
    }
    chView->render(&painterG);
    painterG.end();
}
