#include "follow_trail.h"

/*单片机引脚初始化*/
void Follow_Init(){
	//外部的是1靠里的是2
	GPIO_InitTypeDef left_first_gpio_config = {GPIO_HighZ, GPIO_Pin_0};
	GPIO_InitTypeDef left_second_gpio_config = {GPIO_HighZ, GPIO_Pin_1};
	
	GPIO_InitTypeDef right_first_gpio_config = {GPIO_HighZ, GPIO_Pin_3};
	GPIO_InitTypeDef right_second_gpio_config = {GPIO_HighZ, GPIO_Pin_2};
	
	/*初始化引脚为输入模式*/
	GPIO_Init(GPIO_P2, &left_first_gpio_config);
	GPIO_Init(GPIO_P2, &left_second_gpio_config);
	GPIO_Init(GPIO_P2, &right_first_gpio_config);
	GPIO_Init(GPIO_P2, &right_second_gpio_config);
}

/*检测当前路线位置*/
FOLLOW_DirectionStatus Follow_Obstacle_Check(){
	
	/*读取引脚信息*/
	bit left_first_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_0);
	bit left_second_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_1);
	bit right_first_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_3);
	bit right_second_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_2);
	
	/*判断方向*/
	if((left_second_statu == 0) || (right_second_statu == 0)){
		//直行
		last_statu = F_GO;
		return F_GO;
	}else if(right_first_statu == 0){
		//右转
		last_statu = F_RIGHT;
		return F_RIGHT;
	}else if(left_first_statu == 0){
		//左转
		last_statu = F_LEFT;
		return F_LEFT;
	}else{
		return last_statu;
	}
}

void Start_Follow_Trail(){
		switch(Follow_Obstacle_Check()){
		case F_GO:
			Motor_Run(FORWARD, PWM_DUTY / 100 * (SPEED * 0.9));
			DelayMs(1);
			break;
		case F_LEFT:
			Motor_Run(TURNLEFT, PWM_DUTY / 100 * SPEED);
			DelayMs(1);
			break;
		case F_RIGHT:
			Motor_Run(TURNRIGHT, PWM_DUTY / 100 * SPEED);
			DelayMs(1);
			break;
	}
}