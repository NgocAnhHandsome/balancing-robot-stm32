#include "motor.h"
#include "usart.h"
void MotorInit(void)
{
	// Config GPIO motor A
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// Config GPIO motor B
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	// Config PWM Motor A
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period        = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler     = PRESCALER -1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_InitStructure);
	TIM_Cmd(TIM1, ENABLE);

	TIM_OCInitTypeDef PWM;
	PWM.TIM_OCMode = TIM_OCMode_PWM1;
	PWM.TIM_OutputState = TIM_OutputState_Enable;
	PWM.TIM_Pulse = 0;
	PWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM1, &PWM);
	TIM_OC2Init(TIM1, &PWM);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	// Config PWM Motor B
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period        = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler     = PRESCALER -1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);
	TIM_Cmd(TIM4, ENABLE);

	PWM.TIM_OCMode = TIM_OCMode_PWM1;
	PWM.TIM_OutputState = TIM_OutputState_Enable;
	PWM.TIM_Pulse = 0;
	PWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM4, &PWM);
	TIM_OC4Init(TIM4, &PWM);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

void MotorRight(int16_t speed)
{
	speed = PERIOD*speed/100;
	if(speed < 0)
	{
	TIM4->CCR3 = 0;
	TIM4->CCR4 = -speed;
	}else if(speed > 0)
	{
	TIM4->CCR3 = speed;
	TIM4->CCR4 =0;		
	}else
	{
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;		
	}
}//-100000 100000
void MotorLeft(int16_t speed)
{
	speed = PERIOD*speed/100;
	if(speed < 0)
	{
	TIM1->CCR2 = -speed;
	TIM1->CCR3 = 0;
	}else if(speed > 0)
	{
	TIM1->CCR2 = 0;
	TIM1->CCR3 = speed;		
	}else
	{
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;		
	}	
}
void MotorStop()
{
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;	
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;	
}
