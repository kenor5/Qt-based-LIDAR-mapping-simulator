#include "include/lidar.h"
#include "include/config.h"
#include "include/logprinter.h"
#include <cmath>
#include <QDebug>
#include <cstring>

Lidar::Lidar()
{
    originMap = new RMap(LIDAR_SIGHT_WIDTH, LIDAR_SIGHT_WIDTH, false, 40, 40);

    lidarMap = new RMap(100, 100, false, 4, 4);

    bMap = new RMap(400, 400, false, 1, 1);

    memset(distance, INF, 360);

    this->clearMap();
    this->reMap();
}

//根据车子的坐标（x，y）和障碍物的地图 map 更新雷达看到的障碍物
void Lidar::update_lidarMap(int cx, int cy,RMap &map)
{
    this->clearMap();

    for (int i = 0; i < LIDAR_SIGHT_WIDTH; i++)
    {
        for (int j = 0; j < LIDAR_SIGHT_WIDTH; j++)
        {
            int col = cx - LIDAR_SIGHT_WIDTH/2 + i;
            int row = cy - LIDAR_SIGHT_WIDTH/2 + j;
            if (col < 0 || col > MAPWIDTH-1)
                originMap->addIN(i, j);
            else if (row < 0 || row > MAPWIDTH-1)
                originMap->addIN(i, j);
            else if (map.query(col, row))
                originMap->addIN(i, j);

        }
        std::string str = "";
        for (int j = 0; j < LIDAR_SIGHT_WIDTH; j++)
            str += std::to_string(int(originMap->query(i, j)));
        LogPrinter::getLogPrinter()->printLog(str);
    }

    int x_0 = 200;//中心点
    int y_0 = 200;//中心点
    int mindis = INF;

    for (int cnt = 0; cnt < 360; cnt += LIDAR_SCAN_STEP)
    {
        double angle = PI * cnt/180;
        int x = 0;
        int y = 0;
        int m, n;
        int cur_distance = INF;

        for (int i = 0; i < LIDAR_SCAN_DISTANCE_LIMIT; i += 1)
        {
            x = x_0 + i * cos(angle) + 8;
            y = y_0 + i * sin(angle) + 8;

            if (x > MAPPIXWIDTH || y > MAPPIXWIDTH || x < 0 || y < 0)
                break;

            if (originMap->query(x / 50, y / 50))
            {
                //这里的调整与小车的长和宽有关
                m = (x - car_y + cy * 50 + 20) / 4;
                n = (y - car_x + cx * 50 + 20) / 4;

                this->lidarMap->addIN(m, n);
                cur_distance = DIS(m,n,lidarMap->getCol()/2, lidarMap->getRow()/2);
                break;
            }
        }
        distance[cnt] = cur_distance;
        mindis = MIN(cur_distance, mindis);
    }
    LogPrinter::getLogPrinter()->printLog("print distance");
    LogPrinter::getLogPrinter()->printLog(std::to_string(mindis));
}


void Lidar::buildMap()
{
    //没有移动或者移动很小（比如原地旋转导致的移动）则不更新地图
    if ((car_x + 3) / BLOCKWIDTH == (last_x + 1) / BLOCKWIDTH && (car_y + 3) / BLOCKWIDTH == (last_y + 1) / BLOCKWIDTH)
        return;

    //把雷达扫描的障碍物更新到地图中，
    int fix = 0;
    for (int i = 0; i < lidarMap->getCol(); i++)
    {
        for (int j = 0; j < lidarMap->getRow(); j++)
        {
            //模拟界面中的障碍物坐标
            int x = car_x + 4 * (i - 50);
            int y = car_y + 4 * (j - 50);
            //转化为保存的地图中的坐标
            x = x / 4.0 + OFFSET_CAR_LIDAR_GLOBAL_X;
            y = y / 4.0 + OFFSET_CAR_LIDAR_GLOBAL_Y;
            if (x >= 0 && x < bMap->getCol() && y >= 0 && y < bMap->getRow())
            {
                if (lidarMap->query(i, j))
                    bMap->addIN(y, x);
                else if (fabs(i - lidarMap->getCol() / 2) < fix && fabs(j - lidarMap->getRow() / 2) < fix)
                    bMap->deleteOUT(y, x);
            }
        }
    }
}

void Lidar::reBuildMap()
{
    this->reMap();
}

void Lidar::update_carInfo(int x, int y, double angle)
{
    last_x = car_x;
    last_y = car_y;
    this->car_x = x;
    this->car_y = y;
    this->car_angle = angle;
}

void Lidar::clearMap()
{
    originMap->clear();
    lidarMap->clear();
}

void Lidar::reMap()
{
    bMap->clear();
}

int *Lidar::getDistanceList()
{
    return this->distance;
}

RMap *Lidar::getLidarMap()
{
    return this->lidarMap;
}

RMap *Lidar::getLidarMapTurn()
{
    RMap *Tmap = new RMap(lidarMap->getRow(), lidarMap->getCol(), false, lidarMap->getBlockWidth(), lidarMap->getBlockHeight());
    Tmap->clear();

    int x_0 = lidarMap->getMapWidth()/2;//中心点
    int y_0 = lidarMap->getMapHeight()/2;

    for (int i = 0; i <= lidarMap->getRow(); i++)
    {
        for (int j = 0; j <= lidarMap->getCol(); j++)
        {
            if (lidarMap->query(i, j) == 1)
            {
                double xm = i * lidarMap->getBlockWidth() + OFFSET_CAR_LIDAR_X;
                double ym = j * lidarMap->getBlockHeight() + OFFSET_CAR_LIDAR_Y;
                int x = x_0 + (xm - x_0) * cos(car_angle) + (ym - y_0) * sin(car_angle);
                int y = y_0 + (ym - y_0) * cos(car_angle) - (xm - x_0) * sin(car_angle);
                Tmap->addIN(y / lidarMap->getBlockWidth(), x / lidarMap->getBlockHeight());
            }
        }
    }
    return Tmap;
}

RMap *Lidar::getMap()
{
    return this->bMap;
}

int Lidar::getCar_x()
{
    return this->car_x;
}

int Lidar::getCar_y()
{
    return this->car_y;
}

double Lidar::getCarAngle()
{
    return this->car_angle;
}
