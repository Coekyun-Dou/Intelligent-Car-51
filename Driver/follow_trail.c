#include "follow_trail.h"

/*��Ƭ�����ų�ʼ��*/
void Follow_Init(){
	//�ⲿ����1�������2
	GPIO_InitTypeDef left_first_gpio_config = {GPIO_HighZ, GPIO_Pin_0};
	GPIO_InitTypeDef left_second_gpio_config = {GPIO_HighZ, GPIO_Pin_1};
	
	GPIO_InitTypeDef right_first_gpio_config = {GPIO_HighZ, GPIO_Pin_3};
	GPIO_InitTypeDef right_second_gpio_config = {GPIO_HighZ, GPIO_Pin_2};
	
	/*��ʼ������Ϊ����ģʽ*/
	GPIO_Init(GPIO_P2, &left_first_gpio_config);
	GPIO_Init(GPIO_P2, &left_second_gpio_config);
	GPIO_Init(GPIO_P2, &right_first_gpio_config);
	GPIO_Init(GPIO_P2, &right_second_gpio_config);
}

/*��⵱ǰ·��λ��*/
FOLLOW_DirectionStatus Follow_Obstacle_Check(){
	
	/*��ȡ������Ϣ*/
	bit left_first_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_0);
	bit left_second_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_1);
	bit right_first_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_3);
	bit right_second_statu = GPIO_ReadInputDataBit(GPIO_P2, GPIO_Pin_2);
	
	/*�жϷ���*/
	if((left_second_statu == 0) || (right_second_statu == 0)){
		//ֱ��
		last_statu = F_GO;
		return F_GO;
	}else if(right_first_statu == 0){
		//��ת
		last_statu = F_RIGHT;
		return F_RIGHT;
	}else if(left_first_statu == 0){
		//��ת
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