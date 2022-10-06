#include "stm32f10x.h"                  // Device header
#include "motor.h"

int8_t           Dir_M2, Dir_M3; 
int              Count_TOP2 = 0, Count_BOT2 = 0, Count_TOP3= 0, Count_BOT3 = 0;
volatile int     Count_timer2 = 0, Count_timer3 = 0;                    
volatile int32_t Step2 = 0, Step3 = 0, blink = 0;
volatile uint32_t Ms_Count = 0, u20u_Count = 0;

void MotorInit(void)
{
	// Conig PIN_out
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = Dir_L|Dir_R|Enable;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = Step_L|Step_R;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// Config TIMER
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision      = 0;
	TIM_InitStructure.TIM_CounterMode        = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period             = PERIOD - 1;
	TIM_InitStructure.TIM_Prescaler          = PRESCALER -1;
	TIM_InitStructure.TIM_RepetitionCounter  = 0;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM_Cmd(TIM4,ENABLE);
	GPIO_ResetBits(GPIOA, Enable);
}

void TIM4_IRQHandler(void){
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)!=RESET)
	{
		u20u_Count++;
		if(u20u_Count == 1000)
		{
			u20u_Count = 0;
			Ms_Count++;
		}
		
  if (Dir_M2 != 0) {
    Count_timer2++;
    if (Count_timer2 <= Count_TOP2) GPIO_WriteBit(GPIOA, Step_L, 1);
    else GPIO_WriteBit(GPIOA, Step_L, 0);;
    if (Count_timer2 > Count_BOT2) {
      Count_timer2 = 0;
      if (Dir_M2 > 0)Step2++;
      else if (Dir_M2 < 0)Step2--;
    }
  }

  if (Dir_M3 != 0) {
    Count_timer3++;
    if (Count_timer3 <= Count_TOP3)GPIO_WriteBit(GPIOA, Step_R, 1);
    else GPIO_WriteBit(GPIOA, Step_R, 0);
    if (Count_timer3 > Count_BOT3) {
      Count_timer3 = 0;
      if (Dir_M3 > 0)Step3++;
      else if (Dir_M3 < 0)Step3--;
    }
  }		
//		blink = !blink;
//		GPIO_WriteBit(GPIOA, Step_L, blink);
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}


void Speed_L(int x) {
  if (x < 0) {
    Dir_M2 = -1;
		GPIO_WriteBit(GPIOA, Dir_L, 0);
		Count_BOT2 = -x;
  }
  else if (x > 0) {
    Dir_M2 = 1;
		GPIO_WriteBit(GPIOA, Dir_L, 1);
		Count_BOT2 = x;
  }
  else Dir_M2 = 0;
  
  Count_TOP2 = Count_BOT2 / 2;
}

void Speed_R(int x) {
  if (x < 0) {
    Dir_M3 = -1;
		Count_BOT3 = -x;
		GPIO_WriteBit(GPIOA, Dir_R, 0);
  }
  else if (x > 0) {
    Dir_M3 = 1;
		Count_BOT3 = x;
		GPIO_WriteBit(GPIOA, Dir_R, 1);
  }
  else Dir_M3 = 0;
  Count_TOP3 = Count_BOT3 / 2;
}

uint32_t SystickMillis()
{
	return Ms_Count;
}