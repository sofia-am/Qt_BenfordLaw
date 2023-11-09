#include <QFileDialog>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"

uint16_t fileSizeCount[9] = {0};

//char **directoryTable;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->lineEdit->setText("/home/cnet/untitled");
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
    parseDirectory(this->ui->lineEdit->text());
    for(int i = 0; i < 9; i++){
        qDebug() << fileSizeCount[i];
    }
}

void MainWindow::parseDirectory(QString path){
    //argument sets directory
    QList<QString> directoryTable;
    QDir d(path);
    qDebug() << "Inside " << path << " directory";
    QFileInfoList listado2 = d.entryInfoList();
    // starts from 2 because 0 and 1 are . and ..
    for (int i = 2; i< listado2.count(); ++i) {
        QFileInfo fi = listado2.at(i);
        // qDebug() << fi;
        if(fi.isFile()){
            fileSizeCount[fi.size()%10] += 1;
            //qDebug() << fileSize[fi.size()%10];
        }
        // create a table of directories
        if (fi.isDir()) {
            directoryTable.append(fi.absoluteFilePath());
        }
    }

    for(auto i = directoryTable.begin(); i != directoryTable.end(); i++){
        qDebug() << *i;
        parseDirectory(*i);
    }
}

