#include "global.h" 

static uint32_t time=0;

uint32_t IR_time=0;
uint32_t IR_state=0;
uint8_t IR_Data[4];
uint8_t IR_pData=0;
uint8_t IR_DataFlag=0;
uint8_t IR_RepeatFlag=0;
uint8_t IR_Address=0;
uint8_t IR_Command=0;

uint8_t Address;
uint8_t Command;


void IR_control_Init(void){
	IT1=1;
	IE1=0;
	EX1=1;
	EA=1;
	PX0=0;
	Timer2_myInit();
	while(1){
		if(IR_getDataFlag() || IR_getRepeatFlag()){
			Address=IR_getAddress();
			Command=IR_getCommand();
			if(Command==0x15){//后退
				Motor_Run(BACKWARDS, PWM_DUTY / 100 * 30);
				DelayMs(1000);
				Motor_Run(STOP, PWM_DUTY / 100 * 20);
			}else if(Command==0x46){//前进
				Motor_Run(FORWARD, PWM_DUTY / 100 * 30);
				DelayMs(1000);
				Motor_Run(STOP, PWM_DUTY / 100 * 20);
			}else if(Command==0x44){//左转
				Motor_Run(SPINTURNLEFT, PWM_DUTY / 100 * 30);
				DelayMs(1000);
				Motor_Run(STOP, PWM_DUTY / 100 * 20);
			}else if(Command==0x43){//右转
				Motor_Run(SPINTURNRIGHT, PWM_DUTY / 100 * 30);
				DelayMs(1000);
				Motor_Run(STOP, PWM_DUTY / 100 * 20);
			}else if(Command==0x40){//停止-中间按钮
				Motor_Run(STOP, PWM_DUTY / 100 * 20);
			}
		}
	}
}

void Int1_Routine(void)interrupt 2
{
	if(IR_state==0){
		Timer2_settime(0);
		Timer2_run(1);
		IR_state=1;
	}else if(IR_state==1){
		IR_time=Timer2_gettime();
		Timer2_settime(0);
		if(IR_time>13500-1120 && IR_time<13500+1120){
			IR_state=2;
			OLED_ShowString(4, 7, "yees");
		}else if(IR_time>11250-500 && IR_time<11250+500){
			IR_RepeatFlag=1;
			Timer2_run(0);
			IR_state==0;
			OLED_ShowString(3, 1, "world");
		}else{
			IR_state==1;
			OLED_ShowString(2, 7, "start!");
		}
	}else if(IR_state==2){
		IR_time=Timer2_gettime();
		Timer2_settime(0);
		if(IR_time>1120-500 && IR_time<1120+500){
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));
			IR_pData++;
		}else if(IR_time>2250-500 && IR_time<2250+500){
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));
			IR_pData++;
		}else{
			IR_pData=0;
			IR_state==1;
		}
		if(IR_pData>=32){
			IR_pData=0;
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3])){
				IR_Address=IR_Data[0];
				IR_Command=IR_Data[2];
				IR_DataFlag=1;
			}
			Timer2_run(0);
			IR_state=0;
		}
	}
}


void Timer2_myInit(void){
//	TIM_InitTypeDef time_str;
//	//time_str.TIM_Mode=TIM_16BitAutoReload;		//????,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
//	time_str.TIM_Polity=PolityHigh;		//?????	PolityHigh,PolityLow
//	time_str.TIM_Interrupt=ENABLE;	//????		ENABLE,DISABLE
//	time_str.TIM_ClkSource=TIM_CLOCK_1T;	//???		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//	time_str.TIM_ClkOut=ENABLE;		//???????,	ENABLE,DISABLE
//	time_str.TIM_Value=61183;		//????
//	time_str.TIM_Run=DISABLE;		//????		ENABLE,DISABLE
//	Timer_Inilize(Timer2,&time_str);
		AUXR &= 0xFB;		//?????12T??
		T2L = 0xEE;		//??????
		T2H = 0xFF;		//??????__10us
		IE2|=0x04;
		EA=1;
		//AUXR |= 0x10;		//???2????
		
}

void Timer2_Routine(void)interrupt 12
{
		//??????????10us
		time=time+10;
}


void Timer2_run(int Flag){
	if(Flag==1){AUXR |= 0x10;}
	else{AUXR &= 0xEF;}
}

void Timer2_settime(uint32_t value){
	time=0;
}

uint32_t Timer2_gettime(void){
	//return ((T2H<<8) | T2L);
	return time;
}

uint8_t IR_getDataFlag(void){
	if(IR_DataFlag){
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}

uint8_t IR_getRepeatFlag(void){
	if(IR_RepeatFlag){
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}

uint8_t IR_getAddress(void){
	return IR_Address;
}

uint8_t IR_getCommand(void){
	return IR_Command;
}

