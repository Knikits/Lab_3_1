#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graph.h"
#include "GeneratorGraph.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QtSql>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPainter>
#include <QPdfWriter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QStyle>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableWidget_cellClicked(int row, int column);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QList<Printer*> dataList;
    QChartView* chartView;
};
#endif // MAINWINDOW_H
