#include "remote_control.h"

void Remote_Init(){
	
	
	/*开启外部中断，模式为下降沿触发*/
	IT1 = 1;  // 设置 INT1 为下降沿触发
    EX1 = 1;  // 使能外部中断1
    EA = 1;   // 开启总中断
//	c[9] = '\0';
}

void Start_Control(){
	/*1为避障 2为循迹 方向键对应方向 方向键中间的按键为停止*/
	while(1){
		switch(data_value){
			case 0x46:
				//前进
				Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
				DelayMs(250);
				data_value = 0x40;
				break;
			case 0x40:
				//停止
				Motor_Run(STOP, PWM_DUTY / 100 * 50);
				break;
			case 0x44:
				//原地左转
				Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 50);
				DelayMs(50);
				data_value = 0x40;
				break;
			case 0x43:
				//原地右转
				Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 50);
				DelayMs(50);
				data_value = 0x40;
				break;
			case 0x15:
				//后退
				Motor_Run(BACKWARDS, PWM_DUTY / 100 * 50);
				DelayMs(250);
				data_value = 0x40;
				break;
			case 0x0c:
				//开启避障
				Start_Avoid_Obstacle();
				DelayUs(20);
				break;
			case 0x18:
				//开启循迹
				Start_Follow_Trail();
				DelayUs(20);
				break;
			default:
				data_value = 0x40;
				break;
		}
	}
}

// 外部中断1服务函数
void EX1_ISR(void) interrupt 2 {
	EA = 0;
	EX1 = 0;  // 关闭外部中断1
	
	count = 0;
	
	/*读取引导码*/
	while(P33 == 0){
		count++;
		DelayUs(100);	
	}
	
	if(count >= 49){
		count = 0;
		while(P33 == 1){
			count++;
			DelayUs(100);
		}
		if(count >= 22){
			//引导码通过
			data_bits_idx = 0;  // 用户码+数据码的索引
			//等待数据信号的高电平出现，延迟800us，检测是否还是高电平
			while(data_bits_idx < 32){
				while(P33 == 0);//等待出现高电平
				count = 0;
				while(P33 == 1){
					count++;
					DelayUs(100);
				}
				if(count > 8){
					data_bits[data_bits_idx] = 1;
				}
				else{
					data_bits[data_bits_idx] = 0;
				}
				data_bits_idx++;
			}
//			/*检验数据内容*/
//			j = 0;
//			for(;j < 8;j++){
//				c[j] = data_bits[j] + '0';
//			}
//			OLED_ShowString(1, 1, c);
//			for(; j < 16; j++){
//				c[j - 8] = data_bits[j] + '0';
//			}
//			OLED_ShowString(2, 1, c);
//			for(; j < 24; j++){
//				c[j - 16] = data_bits[j] + '0';
//			}
//			OLED_ShowString(3, 1, c);
//			for(; j < 32; j++){
//				c[j - 24] = data_bits[j] + '0';
//			}
//			OLED_ShowString(4, 1, c);
//			DelayMs(5000);
//			OLED_Clear();
			flag = 0;
			//判断用户码是否正确
			for(count = 0; count < 8; count++){
				if(data_bits[count] != 0 && data_bits[count + 8] != 1){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				//用户码验证通过
				count = 0;
				//检验数据
				flag = 0;
				for(count = 0; count < 8; count++){
					if(data_bits[count + 16] == data_bits[count + 24]){
					flag = 1;
					break;
					}
				}
				//判断数据是否通过检验
				if(flag == 0){	
					//获取16进制值
					data_value = 0x00;
					// 逆序读取 16 到 23 位			
					for(j = 16; j < 24; j++){
						if(data_bits[j] == 1){
							data_value |= (0x01 << j - 16);
						}
					}
//					c[0] = data_value / 16 + '0';
//					c[1] = data_value % 16 + '0';
//					c[2] = '\0';
//					OLED_ShowString(4, 1, c);
				}
			}
		}
	}
	TCON |= 0x04; //中断标志位清零
	EX1 = 1;  // 开启外部中断1
	EA = 1;
}

