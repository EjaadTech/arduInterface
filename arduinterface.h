#ifndef ARDUINTERFACE_H
#define ARDUINTERFACE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QtSerialPort>
#include <qwt_plot_curve.h>


namespace Ui {
class arduinterface;
}

class arduinterface : public QMainWindow
{
    Q_OBJECT

    QVector<double> analogData;
    QVector<double> timeData;

public:
    explicit arduinterface(QWidget *parent = 0);
    ~arduinterface();

private slots:
    void readData();
    void on_btn_scanPort_clicked();
    void on_btn_openPort_clicked();
    void on_btn_closePort_clicked();

    void handleError(QSerialPort::SerialPortError error);

private:
    Ui::arduinterface *ui;
    QSerialPort *serial;
    QTimer *runTime;
    QwtPlotCurve *curve;
    char *buff;
};

#endif // ARDUINTERFACE_H
