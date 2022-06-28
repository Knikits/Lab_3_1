#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "IOCContainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    isChartOpen = false;

    ui->setupUi(this);
    ui->tableWidget_2->setColumnCount(5);

    QStringList name_column;
    name_column << "" << "Name" << "Size" << "Type" << "Date Modifed";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_column);
    ui->tableWidget_2->horizontalHeader()->resizeSection(0, 1);


}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked() // при нажатии на кнопку, открывается дистрибутив и выбирается папка
{
    //QString str = QFileDialog::getExistingDirectory();
    //qDebug() << str;
}



MainWindow::~MainWindow()
{
    delete ui;
}
