#include "avoid_obstacle.h"

/*��Ƭ�����ų�ʼ��*/
void Obstacle_Init(){
	int left_pin_statu = 0;
	int right_pin_statu = 0;
	GPIO_InitTypeDef left_gpio_config = {GPIO_HighZ, GPIO_Pin_6};
	GPIO_InitTypeDef right_gpio_config = {GPIO_HighZ, GPIO_Pin_7};
	
	/*��ʼ������Ϊ����ģʽ*/
	left_pin_statu = GPIO_Init(GPIO_P2, &left_gpio_config);
	right_pin_statu = GPIO_Init(GPIO_P2, &right_gpio_config);
}


/*��⵱ǰ�ϰ���*/
DirectonStatus Obstacle_Check(){
	
	/*��ȡ������Ϣ*/
	bit left_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_6);
	bit right_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_7);
	
	/*�жϷ���*/
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

/*���Ϲ���*/
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