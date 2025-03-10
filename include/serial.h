#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Serial
{
public:
    Serial(const QString &);
    ~Serial();
    QByteArray readData();
    void sendData(const QByteArray&);
protected:
    QSerialPort *serialPort;
};

#endif // SERIAL_H
