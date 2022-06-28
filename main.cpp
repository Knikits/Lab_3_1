#include "mainwindow.h"
#include <QtCharts/QChart>
#include <QApplication>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    string type = "TypeGraph";
    string To = "SomePath";
    Printer printGraphA;
    DataGraph dataGraph = printGraphA.getData();
    GeneratorGraph generatorGraph;
    Graph graph;
    graph = generatorGraph.getGraph(dataGraph, "TypeGraph");
    graph.PrintPdf(To);
*/
    MainWindow w;
    w.show();
    return a.exec();
}
