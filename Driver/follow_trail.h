#ifndef FOLLOW_TRAIL_H  // ��ֹͷ�ļ����ظ�����
#define FOLLOW_TRAIL_H

#include "global.h"  // ����ȫ�����ú��������壬ȷ��������Ч

#define SPEED 90
// ���巽��״̬ö������
typedef enum {
    F_GO = 0,  // ֱ��
    F_LEFT,    // ��ת
    F_RIGHT,    // ��ת
} FOLLOW_DirectionStatus;


static FOLLOW_DirectionStatus last_statu = F_GO;


void Follow_Init(void);
FOLLOW_DirectionStatus Follow_Obstacle_Check(void);
void Start_Follow_Trail(void);

#endif