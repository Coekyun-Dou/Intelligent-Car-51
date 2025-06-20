#include "global.h"


/**/
void Tracking()
{
	int speedtest = 120;
		//0为识别到黑线
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIO_P2, &GPIO_InitStructure);
	if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//未识别到路径
	{	
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//路径在正下方
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//十字路口
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//右偏轻微
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//右偏较多
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//右偏过多
	{
		Motor_Run(TURNRIGHT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//左偏轻微
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//左偏较多
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 1))//左偏过多
	{
		Motor_Run(TURNLEFT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//直角右转
	{
		Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//直角左转
	{
		Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 1) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//异常情况，进入弧形弯道凹口
	{
		Motor_Run(TURNRIGHT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 1))//异常情况，进入弧形弯道凹口
	{
		Motor_Run(TURNLEFT, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//异常情况
	{
		Motor_Run(TURNRIGHT, PWM_DUTY / 100 * speedtest);
		DelayMs(25);
		Motor_Run(TURNLEFT, PWM_DUTY / 100 * speedtest);
		DelayMs(25);
		Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * speedtest);
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 1) && (TrackSensorRight1 == 0) && (TrackSensorRight2 == 0))//异常情况，可能是类似十字的岔口
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}else if((TrackSensorLeft1 == 0) && (TrackSensorLeft2 == 0) && (TrackSensorRight1 == 1) && (TrackSensorRight2 == 0))//异常情况，可能是类似十字的岔口
	{
		Motor_Run(FORWARD, PWM_DUTY / 100 * speedtest);
		
	}
}


