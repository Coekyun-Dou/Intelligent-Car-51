#include "global.h"  // ??????????
volatile unsigned long sys_tick = 0;
static unsigned long last_key_time = 0;  // ????????

// ??bdata???????
unsigned char bdata ir_flags;
sbit flag = ir_flags ^ 0;          // ????
sbit repeat_flag = ir_flags ^ 1;   // ?????


unsigned int count = 0;          // ?????
unsigned char data_bits[32];     // ??32???
unsigned char data_bits_idx = 0; // ?????
unsigned char data_value = 0x40; // ????(????)
unsigned char last_data_value = 0x40; // ???????
unsigned char j = 0;             // ????


typedef enum {
    MODE_REMOTE,    // ????
    MODE_TRACING,   // ????
		MODE_AVOID
} WorkMode;

WorkMode current_mode = MODE_REMOTE; // ???????


void Remote_Init(void);
void SysTick_Init(void);
void ProcessRemoteCommand(void);
void SwitchToRemoteMode(void);
void SwitchToAvoidingMode(void);
void SwitchToTracingMode(void);
void Tracing_Control(void);
void Usart1_SendString(char *str);
void Usart1_SendHex(unsigned char hex);
void Usart1_Init(unsigned int baud);

// ???????????????interrupt??
// ???????interrupt??
// ??????????(1ms??)



void Usart1_SendString(char *str) {
    while(*str) {
        SBUF = *str++;
        while(!TI);
        TI = 0;
    }
}


void Usart1_SendHex(unsigned char hex) {
    unsigned char nibble;
    nibble = (hex >> 4) & 0x0F;
    SBUF = (nibble < 10) ? (nibble + '0') : (nibble - 10 + 'A');
    while(!TI);
    TI = 0;
    
    nibble = hex & 0x0F;
    SBUF = (nibble < 10) ? (nibble + '0') : (nibble - 10 + 'A');
    while(!TI);
    TI = 0;
}



unsigned long GetSystemTick(void) {
    return sys_tick;
}

// ???????
void Remote_Init() {
    IT1 = 1;    // ????1?????
    EX1 = 1;    // ??INT1
    EA = 1;     // ??????
}

// ??????
void ProcessRemoteCommand(void) {
    unsigned long now = GetSystemTick();
    
    // 200ms????????
    if(now - last_key_time > 200) {
        Motor_Run(STOP, 0);
        return;
    }

    switch(data_value) {
        case 0x46:  // ?? - ?????90%
            Motor_Run(FORWARD, PWM_DUTY * 0.5);
            last_key_time = now;  // ?????
            break;
            
        case 0x44:  // ??
            if(!repeat_flag) {
                Motor_Run(SPINTURNLEFT, PWM_DUTY * 0.5);
                last_key_time = now;
            } else if(now - last_key_time > 50) {
                Motor_Run(SPINTURNLEFT, PWM_DUTY * 0.5);
                last_key_time = now;
            }
            break;
            
        case 0x43:  // ??
            if(!repeat_flag) {
                Motor_Run(SPINTURNRIGHT, PWM_DUTY * 0.5);
                last_key_time = now;
            } else if(now - last_key_time > 50) {
                Motor_Run(SPINTURNRIGHT, PWM_DUTY * 0.5);
                last_key_time = now;
            }
            break;
            
        case 0x15:  // ??
            if(!repeat_flag) {
                Motor_Run(BACKWARDS, PWM_DUTY * 0.5);
                last_key_time = now;
            } else if(now - last_key_time > 50) {
                Motor_Run(BACKWARDS, PWM_DUTY * 0.5);
                last_key_time = now;
            }
            break;
            
        case 0x0c:  // ???????
            SwitchToRemoteMode();
            last_key_time = now;  // ?????
            break;
            
        case 0x18:  // ???????
            SwitchToTracingMode();
            last_key_time = now;  // ?????
            break;
				
				case 0x5e:  // ???????
            SwitchToAvoidingMode();
            last_key_time = now;  // ?????
            break;
            
        case 0x40:  // ???
        default:
            Motor_Run(STOP, 0);
            last_key_time = 0;  // ?????
            break;
    }
}


// ???????
void SwitchToRemoteMode(void) {
    current_mode = MODE_REMOTE;
    Motor_Run(STOP, 0); // ??????
    // OLED??????
    // OLED_ShowString(0, 0, "Remote Mode");
}

// ???????
void SwitchToTracingMode(void) {
    current_mode = MODE_TRACING;
    // OLED??????
    // OLED_ShowString(0, 0, "Tracing Mode");
}

void SwitchToAvoidingMode(void) {
    current_mode = MODE_AVOID;
    // OLED??????
    // OLED_ShowString(0, 0, "Tracing Mode");
}

// ????????(??????)
// ????????(??????)
void EX1_ISR(void) interrupt 2 
{
    EA = 0;     // ???
    EX1 = 0;    // ??INT1
    count = 0;

    // 1. ????? (9ms??? + 4.5ms???)
    while(P33 == 0) {  // ???????
        count++;
        DelayUs(100);  // ??100us
        if(count > 180) goto exit; // ???? (18ms)
    }
    
    if(count >= 80 && count <= 100) {  // 9ms ?0%
        count = 0;
        while(P33 == 1) {  // ???????
            count++;
            DelayUs(100);
            if(count > 90) break; // ?? (9ms)
        }
        
        // ????? (2.25ms???)
        if(count >= 20 && count <= 25) { 
            data_value = last_data_value; // ??????
            repeat_flag = 1;              // ??????
            goto exit;
        }
        
        if(count >= 40 && count <= 50) {  // 4.5ms ?0%
            // 2. ??32??? (??? + ???? + ?? + ???)
            data_bits_idx = 0;
            while(data_bits_idx < 32) {
                // ??560us?????
                unsigned int timeout = 0;
                while(P33 == 0) {
                    timeout++;
                    DelayUs(20);
                    if(timeout > 1000) goto exit; // ?? (20ms)
                }
                
                // ?????????
                count = 0;
                timeout = 0;
                while(P33 == 1) {
                    count++;
                    DelayUs(20);
                    if(timeout++ > 1000) goto exit; // ?? (20ms)
                }
                
                // ????: >56(1120us)?1, ???0
                data_bits[data_bits_idx] = (count > 56) ? 1 : 0;
                data_bits_idx++;
            }

            // 3. ?????(?8???8???)
            flag = 0;
            for(count = 0; count < 8; count++) {
                if(data_bits[count] == data_bits[count+8]) {
                    flag = 1;  // ????
                    break;
                }
            }

            if(flag == 0) {  // ???????
                // 4. ????(16-23??24-31???)
                flag = 0;
                for(count = 0; count < 8; count++) {
                    if(data_bits[count+16] == data_bits[count+24]) {
                        flag = 1;  // ????
                        break;
                    }
                }

                if(flag == 0) {  // ??????
                    // 5. ????(16-23?)
                    data_value = 0x00;
                    for(j = 0; j < 8; j++) {
                        if(data_bits[16+j] == 1) {
                            data_value |= (0x01 << j);  // LSB??
                        }
                    }
                    
                    // ???????????
                    last_data_value = data_value;
                    repeat_flag = 0;
                    
                    // ????????
                    Usart1_SendString("Key: 0x");
                    Usart1_SendHex(data_value);
                    Usart1_SendString("\r\n");
                }
            }
        }
    }

exit:
    TCON |= 0x04;  // ??INT1????
    EX1 = 1;       // ????INT1??
    EA = 1;        // ?????
}

// ????(?????)
void Tracing_Control(void) {
    if(P21 == 0 && P22 == 0) {
        Motor_Run(FORWARD, PWM_DUTY * 0.9);
    }
    else if(P21 == 0 && P22 == 1) {
        Motor_Run(TURNLEFT, PWM_DUTY * 0.9);
    }
    else if(P21 == 1 && P22 == 0) {
        Motor_Run(TURNRIGHT, PWM_DUTY * 0.9);
    }
    else {
        static int lost_track_state = 0;
        
        switch(lost_track_state) {
            case 0: // ????
                if(P20 == 1 && P22 == 1) {
                    Motor_Run(TURNRIGHT, PWM_DUTY * 0.9);
                    lost_track_state = 1;
                }
                else if(P21 == 1 && P23 == 1) {
                    Motor_Run(TURNLEFT, PWM_DUTY * 0.9);
                    lost_track_state = 2;
                }
                break;
                
            case 1: // ????????
                if(P20 == 1 && P22 == 0) {
                    lost_track_state = 0; // ????
                }
                break;
                
            case 2: // ????????
                if(P21 == 0 && P23 == 1) {
                    lost_track_state = 0; // ????
                }
                break;
        }
    }
}

// ???
void main(void) {
    // ?????
    SysTick_Init();      // ???????
    DelayMs(1);          // ????
    Motor_PWM_Init();    // ??PWM???
    OLED_Init();         // OLED???
    Remote_Init();       // ???????
    Usart1_Init(9600);   // ?????
    DelayMs(100);        // ??????
    
    // ????
    OLED_ShowString(0, 0, "Init Complete");
    OLED_ShowString(0, 2, "Mode: Tracing");
    
    // ???
    while(1) {
        // ????????????
        if(current_mode == MODE_REMOTE) {
            ProcessRemoteCommand(); // ??????
        }
        else if(current_mode == MODE_TRACING) {
            Tracking();      // ????
        }
        else if(current_mode == MODE_AVOID){
						AvoidSensor();
				}
        // ?????CPU??
        DelayMs(10);
        
        // ??????????????
        if(current_mode == MODE_TRACING && data_value == 0x0c) {
            SwitchToRemoteMode();
        }
				if(current_mode == MODE_AVOID && data_value == 0x0c) {
            SwitchToRemoteMode();
        }
    }
}