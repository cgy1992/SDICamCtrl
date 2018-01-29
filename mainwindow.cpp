#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctrlcmd.h"

#include <QByteArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_haveCtrlRes = false;

    m_serialPort = new QSerialPort(this);
    //设置串口名
    m_serialPort->setPortName("com9");
    //打开串口
    if(!m_serialPort->open(QIODevice::ReadWrite))
        qDebug() << "failed to open serial port";
    //设置波特率
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    //设置数据位数
    m_serialPort->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    m_serialPort->setParity(QSerialPort::NoParity);
    //设置停止位
    m_serialPort->setStopBits(QSerialPort::OneStop);
    //设置流控制
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    connect(m_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
    ui->labelState->setText(QStringLiteral("已就绪"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendCmd()
{
    unsigned char *ptr = (unsigned char *)&m_ctrlCmd;
    m_serialPort->write((char *)ptr, sizeof(m_ctrlCmd));
    ui->labelState->setText(QStringLiteral("命令已发送"));
    qDebug("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
           ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14]);
}

void MainWindow::sendCmdForTest()
{
    unsigned char ptr[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    int bytes = m_serialPort->write((char *)ptr, sizeof(ptr));
    ui->labelState->setText(QStringLiteral("命令已发送") + QString::number(sizeof(ptr)));
    int i;
    char buff[512];
    sprintf(buff, "%d bytes(S):", bytes);
    for(i = 0; i < bytes; i++)
        sprintf(buff, "%s %02x ", buff, ptr[i]);
    qDebug(buff);
}

void MainWindow::readData()
{
    unsigned char buff[64];
    int bytes = m_serialPort->read((char *)buff, sizeof(buff));

    //////////////// debug info //////////////
#if 1
    int i;
    char str[512];
    sprintf(str, "%d bytes(R):", bytes);
    for(i = 0; i < bytes; i++)
        sprintf(str, "%s %02x ", str, buff[i]);
    qDebug(str);
#endif
    //////////////////////////////////////////

    m_serialData.putData(buff, bytes);
    if(m_serialData.haveAvaiablePkt())
    {
        qDebug() << "got an available pkt";
        m_serialData.popPktData((unsigned char *)&m_ctrlRes);
        m_haveCtrlRes = true;
        switch(m_ctrlRes.info)
        {
        case INFO_RECEIVE_OK:
            ui->labelState->setText(QStringLiteral("接收正常"));
            break;
        case INFO_RECEIVE_FAIL:
            ui->labelState->setText(QStringLiteral("接收异常"));
            break;
        case INFO_SERV_READY:
            ui->labelState->setText(QStringLiteral("分划软件就绪"));
            break;
        default:
            ui->labelState->setText(QStringLiteral("反馈信息不可识别"));
        }
    }
}

void MainWindow::fillGroup1()
{
    m_ctrlCmd.setHAngle(ui->lineEditHAngle->text().toUShort());
    m_ctrlCmd.setHSpeed(ui->lineEditHSpeed->text().toUShort());
    m_ctrlCmd.setVAngle(ui->lineEditVAngle->text().toUShort());
    m_ctrlCmd.setVSpeed(ui->lineEditVSpeed->text().toUShort());
    m_ctrlCmd.restBullet = ui->lineEditBullet->text().toUInt();
    m_ctrlCmd.gunZero = ui->comboBoxGun->currentIndex();
    m_ctrlCmd.trigger = ui->comboBoxTrigger->currentIndex();
}

void MainWindow::on_pushButton_01_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x01;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_02_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x02;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_03_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x03;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_04_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x04;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_06_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x06;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_07_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x07;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_09_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x09;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_0a_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x0a;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_0b_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x0b;
    m_ctrlCmd.pack();
    sendCmd();
}

void MainWindow::on_pushButton_0c_clicked()
{
    fillGroup1();
    m_ctrlCmd.keyboard = 0x0c;
    m_ctrlCmd.pack();
    sendCmd();
}
