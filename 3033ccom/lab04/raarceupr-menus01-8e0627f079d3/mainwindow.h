#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cmbCap_currentIndexChanged(const QString &arg1);

    void on_cmbHead_currentIndexChanged(const QString &arg1);

    void on_cmbFeet_currentIndexChanged(const QString &arg1);

    void on_btnRandom_clicked();

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
