#include "stm32f10x_gpio.h"
#include "button.h"
uint16_t vr_New1,vr_Old1,vr_New2,vr_Old2,vr_New3,vr_Old3;
uint16_t speed_control_stt = 0;
int16_t speed_negative = 0,speed_positive = 100;
void Button_Control(void)
{
    vr_Old1=vr_New1;
    vr_New1=GPIO_ReadInputDataBit(GPIOB,BUTTON_1);
    if(vr_New1==0&&vr_Old1==1)
    {
        speed_control_stt++;
    }
    delay(1);
    
    switch(speed_control_stt)
	{
		case 1:
			vr_Old2=vr_New2;
			vr_New2=GPIO_ReadInputDataBit(GPIOB,BUTTON_2);
			if(vr_New2==0&&vr_Old2==1)
			{
				speed_positive++;
			}
			vr_Old3=vr_New3;
			vr_New3=GPIO_ReadInputDataBit(GPIOB,BUTTON_3);
			if(vr_New3==0&&vr_Old3==1)
			{
				speed_positive--;
			}
			break;
		case 2:
			vr_Old2=vr_New2;
			vr_New2=GPIO_ReadInputDataBit(GPIOB,BUTTON_2);
			if(vr_New2==0&&vr_Old2==1)
			{
				speed_negative++;
			}
			vr_Old3=vr_New3;
			vr_New3=GPIO_ReadInputDataBit(GPIOB,BUTTON_3);
			if(vr_New3==0&&vr_Old3==1)
			{
				speed_negative--;
			}
			break;
		case 3:
			speed_negative =0;
			break;
	}
    
}

void delay(unsigned int time)
{
	while(time--)
	{
		for(int i = 0; i < 7998; i++);
	}
}
