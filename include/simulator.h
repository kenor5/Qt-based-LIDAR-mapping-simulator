#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QTimerEvent>

#include "include/car.h"
#include "include/rmap.h"
#include "include/serial.h"


//仿真环境
class Simulator : public QWidget
{
    Q_OBJECT
public:
    static Simulator *getSimulator(QWidget *parent = nullptr);

    void moveCar();

    void clearMap();

    void creatNewMap();

    bool saveMap(std::string filepath);

    bool loadMap(std::string filepath);

    void reBuildMap();

    void setMouseClick();

    // 接受角度和速度并设置
    void receiveAndSet();
    // 发送 Distance 数组
    void sendDistance();

protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void timerEvent(QTimerEvent *event);

private:
    QLabel *carLabel;//显示小车的控件

    QImage carImage;

    Car *car;

    RMap *map;

    Serial *serial;

    bool click;

    int timerID;

    void drawMap(QPainter &painter);//绘制Map

    //TODO 使用GUI程序画小车
    //void drawCar(QPainter &painter);

    explicit Simulator(QWidget *parent = nullptr);

    static Simulator *ptr;
};


#endif // SIMULATOR_H
