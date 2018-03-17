// Raul Negron  #801-13-4680
// Carlos Cosme #802-06-1812
// Seccion 01 (1pm)


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>

#include <stdlib.h>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this) ;
    srand(time(NULL)) ;
}

MainWindow::~MainWindow()
{
    delete ui ;
}

void MainWindow::on_cmbCap_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "") ui->lblCap->setVisible(false) ;

    else
        ui->lblCap->setVisible(true) ;
        if (arg1 == "sheriff")      ui->lblCap->setPixmap(QPixmap(":/cap01.tiff")) ;
        else if (arg1 == "chaplin") ui->lblCap->setPixmap(QPixmap(":/cap02.tiff")) ;
        else if (arg1 == "wizard")  ui->lblCap->setPixmap(QPixmap(":/cap03.tiff")) ;
}

void MainWindow::on_cmbHead_currentIndexChanged(const QString &arg1)
{
    QString x ;
    if (arg1 == "") ui->lblHead->setVisible(false) ;

    else {
        ui->lblHead->setVisible(true) ;
        x = (arg1 == "sheriff") ? ":/head01.tiff" :
            (arg1 == "chaplin") ? ":/head02.tiff" : ":/head03.tiff" ;

    } ui->lblHead->setPixmap(QPixmap(x)) ;
}

void MainWindow::on_cmbFeet_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "") ui->lblFeet->setVisible(false) ;

    else
        ui->lblFeet->setVisible(true) ;

        if (arg1 == "sheriff")      ui->lblFeet->setPixmap(QPixmap(":/feet01.tiff")) ;
        else if (arg1 == "chaplin") ui->lblFeet->setPixmap(QPixmap(":/feet02.tiff")) ;
        else if (arg1 == "wizard")  ui->lblFeet->setPixmap(QPixmap(":/feet03.tiff")) ;
}

void MainWindow::on_btnRandom_clicked()
{
    int capNumber = rand()  % 3 ;
    int headNumber = rand() % 3 ;
    int feetNumber = rand() % 3 ;

    switch (capNumber) {
    case 0: ui->lblCap->setPixmap(QPixmap(":/cap01.tiff")) ; break ;
    case 1: ui->lblCap->setPixmap(QPixmap(":/cap02.tiff")) ; break ;
    default: ui->lblCap->setPixmap(QPixmap(":/cap03.tiff")) ;

    } switch (headNumber) {
    case 0: ui->lblHead->setPixmap(QPixmap(":/head01.tiff")) ; break ;
    case 1: ui->lblHead->setPixmap(QPixmap(":/head02.tiff")) ; break ;
    default: ui->lblHead->setPixmap(QPixmap(":/head03.tiff")) ;


    } switch (feetNumber) {
    case 0: ui->lblFeet->setPixmap(QPixmap(":/feet01.tiff")) ; break ;
    case 1: ui->lblFeet->setPixmap(QPixmap(":/feet02.tiff")) ; break ;
    default: ui->lblFeet->setPixmap(QPixmap(":/feet03.tiff")) ;
    }
}
