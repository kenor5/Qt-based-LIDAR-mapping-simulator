#ifndef CONFIG_H
#define CONFIG_H


// initial location
#define INIT_X 0
#define INIT_Y 0

// initial direction
// 地图由多少方块组成
const int MAPWIDTH = 32;
// 每个方块的宽度
const int BLOCKWIDTH = 25;

// 地图的像素宽度
const int MAPPIXWIDTH = 400;

const double PI = 3.1415926535;

const int OFFSET_CAR_LIDAR_X = -22;
const int OFFSET_CAR_LIDAR_Y = -20;

const double OFFSET_CAR_LIDAR_GLOBAL_X = -4.8;
const double OFFSET_CAR_LIDAR_GLOBAL_Y = -5;

// 雷达视野宽度
const int LIDAR_SIGHT_WIDTH = 9;
// 雷达扫描精度
const int LIDAR_SCAN_STEP = 1;
// 雷达最远扫描距离
const int LIDAR_SCAN_DISTANCE_LIMIT = 284;
#endif // CONFIG_H
