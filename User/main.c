#include "global.h"                  // Device heade
#include "remote_control.h"



void main(void) {
	SysTick_Init();
	DelayMs(1);
	Motor_PWM_Init();
	OLED_Init();
	Usart1_Init(9600);
	
	/*功能初始化*/
	Follow_Init();
	Obstacle_Init();
	Remote_Init();
	
	data_value = 0x00;
	
	DelayMs(100);
	while(1){
		Start_Control();
	}
	
}
