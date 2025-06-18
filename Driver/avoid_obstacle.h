#ifndef AVOID_OBSTACLE_H  // ��ֹͷ�ļ����ظ�����
#define AVOID_OBSTACLE_H

#include "global.h"  // ����ȫ�����ú��������壬ȷ��������Ч

#define SPEED 90

// ���巽��״̬ö������
typedef enum {
    A_GO = 0,  // ֱ��
    A_LEFT,    // ��ת
    A_RIGHT    // ��ת
} DirectonStatus;

// ��������
void Obstacle_Init(void);              // ��ʼ������������
DirectonStatus Obstacle_Check(void);   // ����ϰ���״̬
void Start_Avoid_Obstacle(void);       // �������Ϲ���

#endif

