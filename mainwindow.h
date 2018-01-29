#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "serialdata.h"
#include "ctrlcmd.h"
#include "ctrlres.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void fillGroup1();
    void sendCmd();
    void sendCmdForTest();

private slots:
    void readData();
    
    void on_pushButton_01_clicked();

    void on_pushButton_02_clicked();

    void on_pushButton_03_clicked();

    void on_pushButton_04_clicked();

    void on_pushButton_06_clicked();

    void on_pushButton_07_clicked();

    void on_pushButton_09_clicked();

    void on_pushButton_0a_clicked();

    void on_pushButton_0b_clicked();

    void on_pushButton_0c_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serialPort;

    CtrlCmd m_ctrlCmd;
    CtrlRes m_ctrlRes;
    bool m_haveCtrlRes;
    SerialData m_serialData;
};

#endif // MAINWINDOW_H
