#ifndef AVOID_OBSTACLE_H  // 防止头文件被重复包含
#define AVOID_OBSTACLE_H

#include "global.h"  // 引入全局配置和其他定义，确保引用有效

#define SPEED 90

// 定义方向状态枚举类型
typedef enum {
    A_GO = 0,  // 直行
    A_LEFT,    // 左转
    A_RIGHT    // 右转
} DirectonStatus;

// 函数声明
void Obstacle_Init(void);              // 初始化传感器引脚
DirectonStatus Obstacle_Check(void);   // 检测障碍物状态
void Start_Avoid_Obstacle(void);       // 启动避障功能

#endif

