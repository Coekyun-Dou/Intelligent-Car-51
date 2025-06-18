#ifndef FOLLOW_TRAIL_H  // 防止头文件被重复包含
#define FOLLOW_TRAIL_H

#include "global.h"  // 引入全局配置和其他定义，确保引用有效

#define SPEED 90
// 定义方向状态枚举类型
typedef enum {
    F_GO = 0,  // 直行
    F_LEFT,    // 左转
    F_RIGHT,    // 右转
} FOLLOW_DirectionStatus;


static FOLLOW_DirectionStatus last_statu = F_GO;


void Follow_Init(void);
FOLLOW_DirectionStatus Follow_Obstacle_Check(void);
void Start_Follow_Trail(void);

#endif