#ifndef REMOTE_CONTROL_H  // ��ֹͷ�ļ����ظ�����
#define REMOTE_CONTROL_H

#include "global.h"
#include "follow_trail.h"
#include "avoid_obstacle.h"

//������
static uint8_t data_value;
static uint8_t data_bits_idx;  // �û���+�����������
static uint8_t data_bits[32] = {0};  // �洢�û���+������
static int count; //������
static uint8_t flag;
static uint8_t j;

static char c[9];

void Remote_Init(void);                // ��ʼ��ң������ع���
void EX1_ISR(void);        // �ⲿ�ж�1������
void Start_Control(void);	//��ʼ����

extern void DelayMs(uint16_t ms);
extern void DelayUs(uint16_t us);

#endif