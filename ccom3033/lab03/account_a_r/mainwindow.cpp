// Raul Negron #801-13-4680
// Alejandro Deloach #801-13-1900
// Seccion 1PM

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_crearBtn_clicked()
{
    QString username = ui->userBox->text() ;
    QString email = ui->emailBox->text() ;
    QString cuotaText = ui->cuotaBox->text() ;

    float cuotaFloat = cuotaText.toFloat() ;

    bool compuChecked = ui->checkBox->isChecked() ;
    bool radio1Checked = ui->radio1->isChecked() ;
    bool radio2Checked = ui->radio2->isChecked() ;
    bool radio3Checked = ui->radio3->isChecked() ;
    bool radio4Checked = ui->radio4->isChecked() ;

    bool flag ;

    int academico ;

    if (radio1Checked) academico = 1 ;
    else if (radio2Checked) academico = 2 ;
    else if (radio3Checked) academico = 3 ;
    else if (radio3Checked) academico = 4 ;
    else academico = 0 ;

    bool test1, test2, test3, test4, test5 ;


    test1 = ((username).length() >= 6 && (username).length() <= 8) ;
    test2 = (email.contains('@')) ;
    test3 = (radio1Checked || radio2Checked) ;
    test4 = (compuChecked) ;
    test5 = (cuotaFloat >= 15.0) ;

    flag = (test1 && test2 && test3 && test4 && test5) ;
    QMessageBox msgBox ;
    if (flag) msgBox.setText("Bienvenido " + username + "!") ;
    else msgBox.setText("Lo sentimos. No cumplió los requisitos.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
}
