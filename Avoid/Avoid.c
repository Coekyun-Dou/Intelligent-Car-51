/**/

#include "global.h"

void AvoidSensor() {
	int speedtest2 = 50;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_HighZ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIO_P2, &GPIO_InitStructure);
	
	if ((AvoidSensorLeft == 0) && (AvoidSensorRight == 1)){
		Motor_Run (SPINTURNRIGHT, PWM_DUTY / 100 * speedtest2);

	} else if ((AvoidSensorLeft == 1) && (AvoidSensorRight == 0)){
		Motor_Run (SPINTURNLEFT, PWM_DUTY / 100 * speedtest2);

	} else if ((AvoidSensorLeft == 0) && (AvoidSensorRight == 0)){
		Motor_Run (SPINTURNRIGHT, PWM_DUTY / 100 * speedtest2);

	} else if ((AvoidSensorLeft == 1) && (AvoidSensorRight == 1)){
		Motor_Run (FORWARD, PWM_DUTY / 100 * speedtest2);

	}
}
