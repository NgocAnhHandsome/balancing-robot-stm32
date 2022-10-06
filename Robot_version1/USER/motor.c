#include "motor.h"

void Motor_Init(void)
{
	// MotorR Pin Out
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = Step_R;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = Dir_R;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//MotorL Pin Out
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin  = Step_L;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = Dir_L;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//PWM MotorR
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period        = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler     = PRESCALER -1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);
	TIM_Cmd(TIM4, ENABLE);

	TIM_OCInitTypeDef PWM;
	PWM.TIM_OCMode = TIM_OCMode_PWM1;
	PWM.TIM_OutputState = TIM_OutputState_Enable;
	PWM.TIM_Pulse =10000;
	PWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM4, &PWM);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InitStructure.TIM_ClockDivision = 0;
	TIM_InitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period        = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler     = PRESCALER -1;
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	TIM_Cmd(TIM2, ENABLE);

	PWM.TIM_OCMode = TIM_OCMode_PWM1;
	PWM.TIM_OutputState = TIM_OutputState_Enable;
	PWM.TIM_Pulse =10000;
	PWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &PWM);
	//TIM_OC4Init(TIM4, &PWM);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);	
	//ENA
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = ENA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, ENA);
}
void Speed_L(int Speed)
{
	if(Speed < 0)
	{
		GPIO_ResetBits(GPIOA,Dir_L);
		Speed = -Speed*20;
		TIM2->CCR3 = Speed/2;
		TIM2->ARR = Speed;
	}else if(Speed > 0)
	{
		GPIO_SetBits(GPIOA,Dir_L);
		Speed = Speed*20;
		TIM2->CCR3 = Speed/2;
		TIM2->ARR = Speed;		
	}else{
		TIM2->CCR3 = 0;
	}
}
void Speed_R(int Speed)
{
	if(Speed < 0)
	{
		GPIO_ResetBits(GPIOB,Dir_R);
		Speed = -Speed*20;
		TIM4->CCR3 = Speed/2;
		TIM3->ARR = Speed;
	}else if(Speed > 0)
	{
		GPIO_SetBits(GPIOB,Dir_R);
		Speed = Speed*20;
		TIM4->CCR3 = Speed/2;
		TIM4->ARR = Speed;		
	}else{
		TIM4->CCR3 = 0;
	}
}
