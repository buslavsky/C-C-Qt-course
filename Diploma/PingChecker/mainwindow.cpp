#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QProcess>
#include <QElapsedTimer>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Network ping scanner and monitoring tool");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tbStartScanning_clicked()
{
    bool startIpAddrCorrect;
    bool endIpAddrCorrect;
    bool subnetAndSequenceAreCorrectSame;
    bool sequenceIsCorrect;
    QString startIpAddr = ui->leStartIpAddr->text().trimmed();
    QString endIpAddr = ui->leEndtIpAddr->text().trimmed();


    QHostAddress startAddress(startIpAddr);
    if (QAbstractSocket::IPv4Protocol == startAddress.protocol())
    {
        qDebug("Valid IPv4 start address.");
        startIpAddrCorrect = true;
        ui->leStartIpAddr->setStyleSheet("");

    } else {
        qDebug("Valid IPv4 start address.");
        startIpAddrCorrect = false;
        ui->leStartIpAddr->setStyleSheet("background-color: red;");
    }

    QHostAddress endAddress(endIpAddr);
    if (QAbstractSocket::IPv4Protocol == endAddress.protocol())
    {
        qDebug("Valid IPv4 end address.");
        endIpAddrCorrect = false;
        ui->leEndtIpAddr->setStyleSheet("");
    } else {
        qDebug("Valid IPv4 end address.");
        endIpAddrCorrect = false;
        ui->leEndtIpAddr->setStyleSheet("background-color: red;");
    }


    subnetAndSequenceAreCorrectSame = this->subnetAndSequenceCorrectnessCheck(startIpAddr, endIpAddr);
    sequenceIsCorrect = this->subnetAndSequenceCorrectnessCheck(startIpAddr, endIpAddr);

    if (startIpAddrCorrect && endIpAddrCorrect && subnetAndSequenceAreCorrectSame)
    {
        QStringList server_octets = startIpAddr.split(".");
        uint32_t s11 = server_octets.at(0).toUInt();
        uint32_t s12 = server_octets.at(1).toUInt();
        uint32_t s13 = server_octets.at(2).toUInt();
        uint32_t s14 = server_octets.at(3).toUInt();

        QStringList server_octets2 = endIpAddr.split(".");
        uint32_t s21 = server_octets2.at(0).toUInt();
        uint32_t s22 = server_octets2.at(1).toUInt();
        uint32_t s23 = server_octets2.at(2).toUInt();
        uint32_t s24 = server_octets2.at(3).toUInt();

        for (int i = s14; i <= s24; i++) {


            this->pingTimeResponce("")
        }
    }
}



bool MainWindow::subnetAndSequenceCorrectnessCheck(QString startIP, QString endIP)
{
    bool result = true;

    QStringList server_octets = startIP.split(".");
    uint32_t s11 = server_octets.at(0).toUInt();
    uint32_t s12 = server_octets.at(1).toUInt();
    uint32_t s13 = server_octets.at(2).toUInt();
    uint32_t s14 = server_octets.at(3).toUInt();

    uint32_t serverIPnum = (s11 << 24) | (s12 << 16) | (s13 << 8) | s14;
    uint32_t serverIPnums = (s11 << 24) | (s12 << 16) | (s13 << 8);

    QStringList server_octets2 = endIP.split(".");
    uint32_t s21 = server_octets2.at(0).toUInt();
    uint32_t s22 = server_octets2.at(1).toUInt();
    uint32_t s23 = server_octets2.at(2).toUInt();
    uint32_t s24 = server_octets2.at(3).toUInt();

    uint32_t serverIPnum2 = (s21 << 24) | (s22 << 16) | (s23 << 8) | s24;
    uint32_t serverIPnums2 = (s21 << 24) | (s22 << 16) | (s23 << 8);

    if ((serverIPnums == serverIPnums2) && (s14 < s24))
    {
        result = true;
        ui->lblScanInfo->setText("IP addresses are in one network");
        ui->leStartIpAddr->setStyleSheet("");
        ui->leEndtIpAddr->setStyleSheet("");

    } else {
        result = false;
        ui->lblScanInfo->setText("IP addresses are in different networks!!! \nOr start addres is less than end address! ");
        ui->leStartIpAddr->setStyleSheet("background-color: yellow;");
        ui->leEndtIpAddr->setStyleSheet("background-color: yellow;");
    }



    return result;
}

void MainWindow::on_tbStartMonitoring_clicked()
{
    bool monIpAddrCorrect;
    bool monIpAddReachable;

    QString monIpAddr = ui->leIpAddrToMonitor->text().trimmed();

    QHostAddress startAddress(monIpAddr);
    if (QAbstractSocket::IPv4Protocol == startAddress.protocol())
    {
        qDebug("Valid IPv4 address to monitor.");
        monIpAddrCorrect = true;
        ui->leIpAddrToMonitor->setStyleSheet("");

    } else {
        qDebug("Valid IPv4 address to monitor.");
        monIpAddrCorrect = false;
        ui->leIpAddrToMonitor->setStyleSheet("background-color: red;");
    }

}

uint32_t MainWindow::pingTimeResponce(QString hostName)
{
    uint32_t pingCount = 5;
    int exitCode = 0; // 0 - true, 1 - false

    QElapsedTimer timer;
    QString pingWaitTime = "5";
    QProcess pingProcess;
    #ifdef __linux__
        exitCode = pingProcess.execute("ping", QStringList() << "-c" << QString::number(pingCount, 10) << "-W" << pingWaitTime << hostName);
    #else
        exitCode = pingProcess.execute("ping", QStringList() << "-n" << QString::number(pingCount, 10) << "-w" << pingWaitTime.append("000") << hostName);
        //pingProcess.start("ping", QStringList() << "-n" << "1" << hostName);
    #endif
        qint64 pingResponce = timer.nsecsElapsed();

    return static_cast<uint32_t>(pingResponce/1000000);
}
