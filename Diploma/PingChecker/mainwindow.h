#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool subnetAndSequenceCorrectnessCheck(QString startIP, QString endIP);

    bool scanIsInProgress = false;

    bool monitoringIsInProgress = false;



    uint32_t pingTimeResponce(QString hostName);

private slots:
    void on_tbStartScanning_clicked();

    void on_tbStartMonitoring_clicked();

    void on_tbStopScanning_clicked();

    void on_tbSetDefaults_clicked();

    void on_tbClearLog_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
