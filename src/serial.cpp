#include "include/serial.h"
#include "include/logprinter.h"
#include <QDebug>
#include <QException>

Serial::Serial(const QString &name)
{

//    qDebug() << "start init" ;
//    try{
//    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
//    {
//        qDebug() << "start of info";
//         qDebug() << "Port Name: " << serialPortInfo.portName();
//         qDebug() << "Description: " << serialPortInfo.description();
//          qDebug() << "Manufacturer: " << serialPortInfo.manufacturer();
//          qDebug() << "end of info";
//        // 实例化串口对象
////        QSerialPort serial;
////        serial.setPort(serialPortInfo);

////        // 打开串口
////        if (serial.open(QIODevice::ReadWrite))
////        {

////            // 设置串口参数
////            serial.setBaudRate(QSerialPort::Baud9600);
////            serial.setDataBits(QSerialPort::Data8);
////            serial.setParity(QSerialPort::NoParity);
////            serial.setStopBits(QSerialPort::OneStop);

////            // 读取串口数据
////            QByteArray data = serial.readAll();


////            // 写入串口数据
////            QByteArray writeData = "Hello, Serial Port!";
////            serial.write(writeData);


////            // 关闭串口
////            serial.close();

////        }
//    }


//    serialPort = new QSerialPort(name);
//    if (serialPort && serialPort->open(QIODevice::ReadWrite)) {

//        serialPort->setBaudRate(QSerialPort::Baud9600);
//        serialPort->setDataBits(QSerialPort::Data8);
//        serialPort->setParity(QSerialPort::NoParity);
//        serialPort->setStopBits(QSerialPort::OneStop);
//        serialPort->setFlowControl(QSerialPort::NoFlowControl);
//    }else {
//        qDebug() << "serial port open error ";

//    }
//    }catch(QException &e) {
//        qDebug() << e.what();
//    }
}

Serial::~Serial()
{
    delete serialPort;
}

QByteArray Serial::readData()
{
    return this->serialPort->readAll();
}
