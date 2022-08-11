#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include "bps_adc.h"
#include <stdio.h>
//uint8_t a[10]={1,2,3,4,5,6,7,8,9,10};
// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;     

extern uint16_t ADC_ConversionValue;

void delay_ms(int n)//��ʱ����
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
	
	printf("\r\n ----����һ��ADC��ͨ��DMA��ȡʵ��----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConversionValue/4096*3.3; // ��ȡת����ADֵ
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConversionValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

		delay_ms(1000);  
	}
	
}




