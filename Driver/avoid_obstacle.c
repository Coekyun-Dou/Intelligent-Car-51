#include "avoid_obstacle.h"

/*单片机引脚初始化*/
void Obstacle_Init(){
	int left_pin_statu = 0;
	int right_pin_statu = 0;
	GPIO_InitTypeDef left_gpio_config = {GPIO_HighZ, GPIO_Pin_6};
	GPIO_InitTypeDef right_gpio_config = {GPIO_HighZ, GPIO_Pin_7};
	
	/*初始化引脚为输入模式*/
	left_pin_statu = GPIO_Init(GPIO_P2, &left_gpio_config);
	right_pin_statu = GPIO_Init(GPIO_P2, &right_gpio_config);
}


/*检测当前障碍物*/
DirectonStatus Obstacle_Check(){
	
	/*读取引脚信息*/
	bit left_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_6);
	bit right_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_7);
	
	/*判断方向*/
	if(left_statu == 1 && right_statu == 0){
		return A_GO;
	}else if(left_statu == 0 && right_statu == 0){
		return A_LEFT;
	}else if(left_statu == 1 && right_statu == 1){
		return A_RIGHT;
	}else{
		return A_RIGHT;
	}
}

/*避障功能*/
void Start_Avoid_Obstacle(){
	switch(Obstacle_Check()){
		case A_GO:
			Motor_Run(FORWARD, PWM_DUTY / 100 * SPEED);
			DelayMs(100);
			break;
		case A_LEFT:
			Motor_Run(TURNLEFT, PWM_DUTY / 100 * SPEED);
			DelayMs(100);
			break;
		case A_RIGHT:
			Motor_Run(TURNRIGHT, PWM_DUTY / 100 * SPEED);
			DelayMs(115);
			Motor_Run(FORWARD, PWM_DUTY / 100 * SPEED);
			DelayMs(25);
			break;
	}

}