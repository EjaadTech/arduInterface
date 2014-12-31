#include "arduinterface.h"
#include "ui_arduinterface.h"

#define SERIALDATASIZE 100  // 4x8 analog data + 8x, + \r\n
#define SERIALDATACOUNT 9   // 8x analog data + 1x new line
#define PLOTSIZE 100

arduinterface::arduinterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::arduinterface)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    buff = new char[SERIALDATASIZE];
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom, "Time");
    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "Volatge (v)");
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, 3.5 );

    for(int a=0; a<PLOTSIZE; a++){
        timeData.append(a);
        analogData.append(qSin(a)*2+2);
    }

    curve = new QwtPlotCurve;
    curve->setSamples(timeData,analogData);
    curve->attach(ui->qwtPlot);
    ui->qwtPlot->replot();

}

arduinterface::~arduinterface()
{
    delete ui;
}

void arduinterface::on_btn_scanPort_clicked()
{
    ui->cbox_portList->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString s = info.portName();
        ui->cbox_portList->addItem(s);
    }
    if(QSerialPortInfo::availablePorts().count()>0)
        ui->btn_openPort->setEnabled(true);
    else
        ui->btn_openPort->setEnabled(false);
}

void arduinterface::on_btn_openPort_clicked()
{
    serial->setPortName(ui->cbox_portList->currentText());
    serial->setBaudRate(9600);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->plainTextEdit->setEnabled(true);
            ui->btn_scanPort->setEnabled(false);
            ui->btn_openPort->setEnabled(false);
            ui->btn_closePort->setEnabled(true);
            ui->plainTextEdit->clear();
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
}

void arduinterface::on_btn_closePort_clicked()
{
    serial->close();
    ui->btn_scanPort->setEnabled(true);
    ui->btn_openPort->setEnabled(true);
    ui->btn_closePort->setEnabled(false);
}

void arduinterface::readData(){
    if(serial->readLine(buff,SERIALDATASIZE)>0){
        QString t(buff);
        t.replace("\r\n","\n");
        ui->plainTextEdit->appendPlainText(t);
        QStringList data(t.split(','));
        if(data.count()==SERIALDATACOUNT){
            ui->vslide_a_1->setValue(data.at(0).toInt());
            ui->vslide_a_2->setValue(data.at(1).toInt());
            ui->vslide_a_3->setValue(data.at(2).toInt());
            ui->vslide_a_4->setValue(data.at(3).toInt());
            ui->vslide_a_5->setValue(data.at(4).toInt());
            ui->vslide_a_6->setValue(data.at(5).toInt());
            ui->vslide_a_7->setValue(data.at(6).toInt());
            ui->vslide_a_8->setValue(data.at(7).toInt());

            for(int a=0; a<PLOTSIZE-1; a++)
                analogData.replace(a, analogData.at(a+1));
            analogData.replace(PLOTSIZE-1,data.at(0).toDouble()/1024.0*3.3);

            curve->setSamples(timeData,analogData);

            ui->qwtPlot->replot();

        }
    }
}

void arduinterface::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        //on_btn_closePort_clicked();
        ui->btn_scanPort->setEnabled(true);
        ui->btn_closePort->setEnabled(false);
    }
}
