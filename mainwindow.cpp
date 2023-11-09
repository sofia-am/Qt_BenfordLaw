#include <QFileDialog>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"

uint16_t fileSize[9] = {0};
QMap directoryList{QString, bool};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->lineEdit->setText("/home/cnet/untitled1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    qDebug() << "Abrir directorio";
    QString dir = QFileDialog::getExistingDirectory(this, "Seleccione un directorio", "/home");
    this->ui->lineEdit->setText(dir);
}

void MainWindow::on_pushButton_clicked()
{
    //get text from lineEdit widget
    QDir d(this->ui->lineEdit->text());

    QFileInfoList listado2 = d.entryInfoList();
    uint16_t maskedDigit;
    //qDebug() << listado2;
    for (int i = 0; i< listado2.count(); ++i) {
        QFileInfo fi = listado2.at(i);
        qDebug() << fi;
        if(fi.isFile()){
            fileSize[fi.size()%10] += 1;
            //qDebug() << fileSize[fi.size()%10];
        }
        if (fi.isDir()) {
            qDebug() << "Directorio" << i << fi.absoluteFilePath();

        }
    }
}


