#include "remote_control.h"

void Remote_Init(){
	
	
	/*�����ⲿ�жϣ�ģʽΪ�½��ش���*/
	IT1 = 1;  // ���� INT1 Ϊ�½��ش���
    EX1 = 1;  // ʹ���ⲿ�ж�1
    EA = 1;   // �������ж�
//	c[9] = '\0';
}

void Start_Control(){
	/*1Ϊ���� 2Ϊѭ�� �������Ӧ���� ������м�İ���Ϊֹͣ*/
	while(1){
		switch(data_value){
			case 0x46:
				//ǰ��
				Motor_Run(FORWARD, PWM_DUTY / 100 * 50);
				DelayMs(250);
				data_value = 0x40;
				break;
			case 0x40:
				//ֹͣ
				Motor_Run(STOP, PWM_DUTY / 100 * 50);
				break;
			case 0x44:
				//ԭ����ת
				Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 50);
				DelayMs(50);
				data_value = 0x40;
				break;
			case 0x43:
				//ԭ����ת
				Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 50);
				DelayMs(50);
				data_value = 0x40;
				break;
			case 0x15:
				//����
				Motor_Run(BACKWARDS, PWM_DUTY / 100 * 50);
				DelayMs(250);
				data_value = 0x40;
				break;
			case 0x0c:
				//��������
				Start_Avoid_Obstacle();
				DelayUs(20);
				break;
			case 0x18:
				//����ѭ��
				Start_Follow_Trail();
				DelayUs(20);
				break;
			default:
				data_value = 0x40;
				break;
		}
	}
}

// �ⲿ�ж�1������
void EX1_ISR(void) interrupt 2 {
	EA = 0;
	EX1 = 0;  // �ر��ⲿ�ж�1
	
	count = 0;
	
	/*��ȡ������*/
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
			//������ͨ��
			data_bits_idx = 0;  // �û���+�����������
			//�ȴ������źŵĸߵ�ƽ���֣��ӳ�800us������Ƿ��Ǹߵ�ƽ
			while(data_bits_idx < 32){
				while(P33 == 0);//�ȴ����ָߵ�ƽ
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
//			/*������������*/
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
			//�ж��û����Ƿ���ȷ
			for(count = 0; count < 8; count++){
				if(data_bits[count] != 0 && data_bits[count + 8] != 1){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				//�û�����֤ͨ��
				count = 0;
				//��������
				flag = 0;
				for(count = 0; count < 8; count++){
					if(data_bits[count + 16] == data_bits[count + 24]){
					flag = 1;
					break;
					}
				}
				//�ж������Ƿ�ͨ������
				if(flag == 0){	
					//��ȡ16����ֵ
					data_value = 0x00;
					// �����ȡ 16 �� 23 λ			
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
	TCON |= 0x04; //�жϱ�־λ����
	EX1 = 1;  // �����ⲿ�ж�1
	EA = 1;
}

