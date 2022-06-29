#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList name_column;
    name_column << "Name" << "Size" << "Type" << "Date Modifed";
    ui->tableWidget->setHorizontalHeaderLabels(name_column);
    connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(createGraph()));
}

void MainWindow::on_pushButton_clicked()
{
    if (chartView != nullptr)
    {
    GeneratorGraph().PDF(chartView);
    }
    else qDebug() << "Ошибка";
}

void MainWindow::on_pushButton_2_clicked()
{
    QString strs = QFileDialog::getExistingDirectory(this);
    QDir directory(strs); // QDir обеспечивает доступ к каталогов и их содержимому
    directory.setFilter(QDir::Files); // функция-фильтр
    QFileInfoList files = directory.entryInfoList(); // получаем список файлов директории
    for (int i = 0; i < files.size(); i++)
    {
        QFileInfo filesInfo = files.at(i);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(filesInfo.fileName()));
        float size = filesInfo.size();
        int count = 0;
        while (size > 1024)
        {
            size = size / 1024;
            count++;
        }
        QString str;
        str = QString::number(size);
        switch(count)
        {
            case 0:
                str = str + "B";
                break;
            case 1:
                str = str + "KB";
                break;
            case 2:
                str = str + "MB";
                break;
            case 3:
                str = str + "GB";
                break;
            case 4:
                str = str + "TB";
                break;
        }
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(str));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(filesInfo.suffix()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(filesInfo.lastModified().toString()));

        //qDebug() << strs;

        // отправляем данные в бд
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
        dataBase.setDatabaseName(filesInfo.absolutePath() + "/" + filesInfo.fileName());
        if (!dataBase.open())
        {
            qDebug() << filesInfo.absolutePath();
            return;
        }
        QSqlQuery query(dataBase);
        QString tableName = "";
        for (int j = 0; filesInfo.fileName()[j] != "."; j++)
        {
            tableName = tableName + filesInfo.fileName()[j];
        }
        if (!query.exec("SELECT * FROM " + tableName))
        {
            qDebug() << "Не возможно сформировать таблицу!";
            return;
        }

        QMap<QString, int> map;
        while (query.next())
        {
            map.insert(query.value(0).toString(), query.value(1).toInt());
        }
        dataList.append(new Graph());
        dataList[i]->getData(map);
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (ui->comboBox->currentIndex() == 0)
    {
        QBarSeries * series = dataList[row]->BarSeries();
        chartView = GeneratorGraph().GeneratorBar(series, ui->checkBox->checkState());
        chartView->setParent(ui->horizontalFrame_2);
        chartView->show();
    }
    else
    {
        QPieSeries * series = dataList[row]->PieSeries();
        chartView = GeneratorGraph().GeneratorPie(series, ui->checkBox->checkState());
        chartView->setParent(ui->horizontalFrame_2);
        chartView->show();
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


