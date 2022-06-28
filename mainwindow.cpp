#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "IOCContainer.h"
#include "qdebug.h"
#include "QDateTime"
#include "QtSql"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    isChartOpen = false;

    ui->setupUi(this);
    ui->tableWidget_2->setColumnCount(4);

    QStringList name_column;
    name_column << "Name" << "Size" << "Type" << "Date Modifed";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_column);
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked() // при нажатии на кнопку, открывается дистрибутив и выбирается папка
{
    QString strs = QFileDialog::getExistingDirectory(this);
    QDir directory(strs); // QDir обеспечивает доступ к каталогов и их содержимому
    directory.setFilter(QDir::Files); // функция-фильтр
    QFileInfoList files = directory.entryInfoList(); // получаем список файлов директории
    for (int i = 0; i < files.size(); i++)
    {
        QFileInfo filesInfo = files.at(i);
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 0, new QTableWidgetItem(filesInfo.fileName()));
        float size = filesInfo.size();
        int count = 0;
        while (size > 1024)
        {
            size/=1024;
            count++;
        }
        QString str;
        str = QString::number(size);
        switch(count)
        {
            case 0:
                str += "B";
                break;
            case 1:
                str += "KB";
                break;
            case 2:
                str += "MB";
                break;
            case 3:
                str += "GB";
                break;
            case 4:
                str += "TB";
                break;
        }
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 1, new QTableWidgetItem(str));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 2, new QTableWidgetItem(filesInfo.suffix()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 3, new QTableWidgetItem(filesInfo.lastModified().toString()));
    }
    qDebug() << strs;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_2_cellClicked(int row, int column)
{
    QString str = QFileDialog::getOpenFileName();
    QSqlDatabase dateBase = QSqlDatabase::addDatabase("QSQLITE");
    dateBase.setDatabaseName(str);
    if (!dateBase.open())
    {
        qDebug() << "База данных не может быть открыта!";
        return;
    }
    QSqlQuery query(dateBase);

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable(str);

    if (!query.exec("SELECT * FROM " + str))
    {
        qDebug() << "Не получается сборка";
        return;
    }
    else
    {
        QBarSeries *series = new QBarSeries();
        QBarSet *set = new QBarSet(query.value(0).toString());
    }

    QMap<QString, int> map;
}

