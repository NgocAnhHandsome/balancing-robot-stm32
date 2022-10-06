/*
  ******************************************************************************
  * @file		abc.c                                                              *
  * @author	Luu Ngoc Anh                                                       *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
#include "usart_lib.h" 
#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

char String_receive[100];
unsigned int count = 0;
char Data;
unsigned int Stt_receive = 0;

struct __FILE {
 int dummy;
};
FILE __stdout;
int fputc(int ch, FILE *f) {
 UsartLib_SendChar(ch);
 return ch;
}

void UsartLib_Init(unsigned int BaudRates)
{
	USART_InitTypeDef USART_Structure;
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	// config TX
	GPIO_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Structure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	// config RX
	GPIO_Structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Structure.GPIO_Pin  = GPIO_Pin_10;
	GPIO_Structure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	
	USART_Structure.USART_BaudRate = BaudRates;
	USART_Structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Structure.USART_Parity = USART_Parity_No;
	USART_Structure.USART_StopBits = USART_StopBits_1;
	USART_Structure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_Structure);
	
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ClearFlag(USART1,ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)!= RESET)
	{
		Data = USART_ReceiveData(USART1);
		if(Data != '\n')
		{
			String_receive[count] = Data;
			count ++;
		}else
		{
			Stt_receive = 1;
			String_receive[count-1] = 0;
			count = 0;
		}
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

void UsartLib_SendChar(char _varChar)
{
	USART_SendData(USART1,_varChar);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}	
void UsartLib_SendString(char *_varString)
{
	while(*_varString != NULL)
	{
		UsartLib_SendChar(*_varString++);
	}
}
void UsartLib_SendNumber(int _varNumber)
{
	char temp[20];
	sprintf(temp,"%d",_varNumber);
	UsartLib_SendString(temp); 
}	

void UsartLib_SendFloat(float a)
{
	char temp[20];
	sprintf(temp,"%f",a);
	UsartLib_SendString(temp); 	
}

unsigned char UsartLib_CompareStr(char *S1)
{
	if(strstr(S1, String_receive) != NULL) 
	{
		return 1;
	}
	else 
		return 0;
}
int UsartLib_flag(void)
{
	if(Stt_receive)
	{
		Stt_receive = 0;
		return 1;
	}else
	{
		return 0;
	}
}	

void UsartLib_Putchar_RRX(void)
{
		UsartLib_SendString(String_receive);
		UsartLib_SendString("\n");
}
void UsartLib_Gets(char *s)
{
//	while(1)
//	{
//		if(Stt_receive == 1) break;
//	}
	int i=0;
	Stt_receive = 0;
	while(1)
	{
		s[i] = String_receive[i];
		i++;
		if(String_receive[i] == NULL) break;
	}
}

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<0x2aff;j++);
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
