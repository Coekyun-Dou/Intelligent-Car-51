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
			//����Ҫ�����ӳٺ�ģʽ�л���ʾ�ĺ��������Ǽ���ûд
			//�����ѡ��ṹҲû�мӽ�ȥ��ֻ�����˹ؼ����߼�����
			//������ӣ���������ų�ͻ�������޷��л�ģʽ
		}
		
		if(t == 0){
			Tracking();//ѭ��
		}else if (t == 1){
			AvoidSensor();//����
		}else{
			IR_control_Init();//ң��
		}
		
	}
}
