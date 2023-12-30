#ifndef CONFIG_H
#define CONFIG_H

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b
#define DIS(a,b,c,d) sqrt((a-c)*(a-c)+(b-d)*(b-d))
// 频率
const int FREQ = 10;
// 无限远
const int INF = 0x7fffffff;

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

// 小车一次移动的像素数量
const int CAR_MOVE_STEP = 5;
// 一次转动的角度
const int CAR_TURN_STEP = 1;

const int CAR_MAX_VOL = 30;
const int CAR_MIN_VOL = -30;
const int CAR_MAX_DIR = 30;
const int CAR_MIN_DIR = -30;

#endif // CONFIG_H
