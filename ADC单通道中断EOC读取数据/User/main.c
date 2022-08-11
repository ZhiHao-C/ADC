#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include "bps_adc.h"
#include <stdio.h>
//uint8_t a[10]={1,2,3,4,5,6,7,8,9,10};
uint16_t ADC_ConversionValue;
float ADC_ConvertedValueLocal;
void delay_ms(int n)//ÑÓÊ±º¯Êý
{
	int i;
	while (n--)
	{
		for(i=0;i<5520;i++);
	}
}



int main()
{
	USART_Config();
	ADC_Config_Init();
	
	
	while (1)
	{
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConversionValue); 
		ADC_ConvertedValueLocal=(float)ADC_ConversionValue/4096*3.3;
		printf("\r\n The current AD value = %f  V \r\n", ADC_ConvertedValueLocal); 
		delay_ms(200);
	}
	
}



void ADC1_2_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC_x, ADC_IT_EOC))
	{
		ADC_ConversionValue=ADC_GetConversionValue(ADC_x);
		ADC_ClearITPendingBit(ADC_x, ADC_IT_EOC);
	}
	
}

