#include "global.h"                  // Device heade
int t=0;

void main(void) {
	SysTick_Init();
	DelayMs(1);
	Motor_PWM_Init();
	OLED_Init();
	Usart1_Init(9600);
	DelayMs(100);
	
	while(1){
		if(key == 0){
			t++;
			if(t > 2){
				t = 0;
			}
			//这里要加入延迟和模式切换显示的函数，但是简化了没写
			//下面的选择结构也没有加进去，只保留了关键的逻辑部分
			//如果不加，会产生引脚冲突错误导致无法切换模式
		}
		
		if(t == 0){
			Tracking();//循迹
		}else if (t == 1){
			AvoidSensor();//避障
		}else{
			IR_control_Init();//遥控
		}
		
	}
}
