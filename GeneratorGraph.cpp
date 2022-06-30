#include "GeneratorGraph.h"

GeneratorGraph::GeneratorGraph() {} // типо реализация конструтора класса

//Класс QChart управляет графическим представлением рядов, условных обозначений и осей диаграммы.
QChartView* GeneratorGraph::GeneratorBar(QBarSeries * barS, bool color)
{
    QChart* chart = new QChart();
    if (color) // если график черно-белый
    {
        int j = 0;
        for (auto set : barS->barSets())
        {
            set -> setColor(QColor(j,j,j)); // устанавливаем цвет
            j = j + 10; // как бы от этого зависит, насколько разные будут цвета от первого до последнего столбца
        }
    }
    else // если цветной график
    {
        for(auto set : barS->barSets())
        {
            set->setColor(QColor(rand()%255, rand()%255, rand()%255)); // устанавливаем цвет
        }
    }
    chart->addSeries(barS);
    chart->setTitle("Диаграмма"); // заголовок
    chart->setAnimationOptions(QChart::SeriesAnimations); //это свойство содержит параметры анимации для диаграммы
    QChartView *view = new QChartView(chart);
    return view;
}

QChartView* GeneratorGraph::GeneratorPie(QPieSeries * pieS, bool color)
{
    //всё аналогично, только делается всё для "пирога"
    QChart* chart = new QChart();

    //chart = gContainer.GetObject...

    if (color) // если график черно-белый
    {
        int j = 0;
        for (auto set : pieS->slices())
        {
            set -> setColor(QColor(j,j,j));
            j = j + 10;
        }
    }
    else // если цветной график
    {
        for(auto set : pieS->slices())
        {
            set->setColor(QColor(rand()%255, rand()%255, rand()%255));
        }
    }
    chart->addSeries(pieS);
    chart->setTitle("Круговой график");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *view = new QChartView(chart);
    return view;
}

void GeneratorGraph::PDF(QChartView *chView)
{
    //реализация вывода графика в PDF
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("D:/PDFresult.pdf");
    QPainter painterG;
    if (!painterG.begin(&printer)) return;
    chView->render(&painterG);
    painterG.end();
}

