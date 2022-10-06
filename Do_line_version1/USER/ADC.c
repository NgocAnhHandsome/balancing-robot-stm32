#include "ADC.h"
#include <stm32f10x.h>
#include "usart.h"
uint16_t DLCD[8]; //mang luu gia tri adc
uint16_t Re[8];
uint16_t vrui_value[9]; 
NVIC_InitTypeDef nvic;
int stt = 0;
unsigned int Checking(void)
{
	Re[0]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	Re[1]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
	Re[2]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
	Re[3]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
	Re[4]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
	Re[5]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
	Re[6]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	Re[7]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
	for(int i=0;i<8;i++)
	{
		printf("%d ",DLCD[i]);
	}
	printf("\n");
	if(Re[0] == 1 && Re[1] == 1 && Re[2] == 1 &&Re[3] == 0 &&Re[4] == 0 &&Re[5] == 1 &&Re[6] == 1 &&Re[7] == 1 )
	{
		stt=1;
		return stt;
	}
	else if(Re[0] == 1  && Re[1] == 1 &&Re[2] == 1&&(Re[5] == 0 ||Re[6] == 0||Re[7] == 0) )
	{
		stt=2;
		return stt;
	}
	else if((Re[0] == 0 || Re[1] == 0 || Re[2] == 0 )  &&Re[5] == 1&&Re[6] == 1&&Re[7] == 1 )
	{
		stt=3;
		return stt;
	}
		//white 1 black 0
	else if(Re[0] == 0 && Re[1] == 0 && Re[2] == 0  &&Re[5] == 0 &&Re[6] == 0 &&Re[7] == 0 )
	{
		stt=0;
		return stt;
	}
	return stt;
}


void GPIO_DMA_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /// mode Analog In
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
//void test(void)
//{
//	Re[0]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
//	Re[1]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
//	Re[2]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
//	Re[3]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
//	Re[4]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
//	Re[5]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
//	Re[6]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
//	Re[7]=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
//}
void Adc_config(void)
	{
	ADC_InitTypeDef adc;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_ScanConvMode = ENABLE;
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_NbrOfChannel = 8;
	ADC_Init(ADC1,&adc);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
		
	ADC_TempSensorVrefintCmd(DISABLE);
		
	ADC_ResetCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

void DMA_Config(void)
{
	DMA_InitTypeDef dma;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1);
	dma.DMA_PeripheralBaseAddr = (u32) &ADC1 -> DR;
	dma.DMA_MemoryBaseAddr = (u32) &DLCD;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_BufferSize = 8;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_High;
	dma.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &dma);
	
//	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
//	
//	
//	//Enable DMA1 channel IRQ Channel */
//	nvic.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//	nvic.NVIC_IRQChannelPreemptionPriority = 0;
//	nvic.NVIC_IRQChannelSubPriority = 0;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

