#ifndef REMOTE_CONTROL_H  // 防止头文件被重复包含
#define REMOTE_CONTROL_H

#include "global.h"
#include "follow_trail.h"
#include "avoid_obstacle.h"

//解码结果
static uint8_t data_value;
static uint8_t data_bits_idx;  // 用户码+数据码的索引
static uint8_t data_bits[32] = {0};  // 存储用户码+数据码
static int count; //计数器
static uint8_t flag;
static uint8_t j;

static char c[9];

void Remote_Init(void);                // 初始化遥控器相关功能
void EX1_ISR(void);        // 外部中断1服务函数
void Start_Control(void);	//开始控制

extern void DelayMs(uint16_t ms);
extern void DelayUs(uint16_t us);

#endif