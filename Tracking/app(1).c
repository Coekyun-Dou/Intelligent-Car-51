#include "global.h"


/**/
void Tracking()
{
	int speedtest = 120;
		//0Ϊʶ�𵽺���
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIO_P2, &GPIO_InitStructure);
	if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//δʶ��·��
	{	
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//·�������·�
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//ʮ��·��
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//��ƫ��΢
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//��ƫ�϶�
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//��ƫ����
	{
		Motor_Run(TURNRIGHT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//��ƫ��΢
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//��ƫ�϶�
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//��ƫ����
	{
		Motor_Run(TURNLEFT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//ֱ����ת
	{
		Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//ֱ����ת
	{
		Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//�쳣��������뻡���������
	{
		Motor_Run(TURNRIGHT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//�쳣��������뻡���������
	{
		Motor_Run(TURNLEFT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//�쳣���
	{
		Motor_Run(TURNRIGHT, PWM_DUTY / 100 * speedtest);
		DelayMs(25);
		Motor_Run(TURNLEFT, PWM_DUTY / 100 * speedtest);
		DelayMs(25);
		Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * speedtest);
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//�쳣���������������ʮ�ֵĲ��
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//�쳣���������������ʮ�ֵĲ��
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}
}


