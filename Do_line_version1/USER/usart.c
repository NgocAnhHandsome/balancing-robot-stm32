#include "usart.h"
#include "string.h"

char vr_Numberal[100][100];
char vr_Recei[1000];
char vr_GetChar;
int vr_locate = 0;
unsigned int count=0;
unsigned int Stt=0;

struct __FILE 
{
	int dummy;
};
FILE __stdout;
int fputc(int ch, FILE *f) 
{
	USART_SendChar(ch);
	return ch;
}

int USART_FlagDB(void)
{
	if(Stt==1)
	{
		Stt=0;
		return 1;
	}
	else 
		return 0;
}

unsigned int Numberal(int vr_Num, int vr_locate)
{
	unsigned int vr_number_of_digits=1;
	while(vr_Num>0)
	{
		vr_Numberal[vr_locate][vr_number_of_digits++] = vr_Num%10;
//		003 012 031
		vr_Num /= 10;
	}
	return vr_number_of_digits;
}
//123
void USART_SendNum(int vr_Num) 
{
	int vr_number_of_digits;
	
	vr_number_of_digits = Numberal(vr_Num,vr_locate)-1;
	while(vr_number_of_digits>0)
	{
		USART_SendChar(vr_Numberal[vr_locate][vr_number_of_digits]+'0');
		vr_number_of_digits--;
	}
	
}

void USART_Config(unsigned int Baurates)
{
    GPIO_InitTypeDef GPIO_Struct;
	USART_InitTypeDef USART_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin     = GPIO_Pin_10;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_IN_FLOATING;
	GPIO_Struct.GPIO_Pin     = GPIO_Pin_11;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Struct);
	
	USART_Struct.USART_BaudRate 			= Baurates;
	USART_Struct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode 				= USART_Mode_Rx|USART_Mode_Tx;
	USART_Struct.USART_Parity      			= USART_Parity_No;
	USART_Struct.USART_StopBits 			= USART_StopBits_1;
	USART_Struct.USART_WordLength 			= USART_WordLength_8b;
	USART_Init(USART3,&USART_Struct);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART3_IRQn);
	USART_Cmd(USART3,ENABLE);
}


void Delay_ms(unsigned int vr_Time)
{
	unsigned int i,j;
	for(i=0;i<vr_Time;i++)
	{
		for(j=0;j<0x2aff;j++)
		{
		
		}
	}
}

void USART_SendChar(char vr_Char)
{
	USART_SendData(USART3,vr_Char);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE)==RESET);
}

void USART_SendString(char *vr_Str)
{
	while(*vr_Str != 0)
	{
		USART_SendChar(*vr_Str++);
	}
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		vr_GetChar = USART_ReceiveData(USART3);
		if(vr_GetChar != '\n')
		{
			vr_Recei[count] = vr_GetChar;
			count++;
		}
		else
		{
			Stt=1;
			vr_Recei[count-1] = 0;
			count = 0;
		}
	}
}

int USART_Compare(char* vr_String)
{
	unsigned char status=1;
	if(strcmp(vr_String,vr_Recei)!=0)
	{
		status=0;
	}
	return status;
}
