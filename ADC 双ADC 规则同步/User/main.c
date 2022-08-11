#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include "bps_adc.h"
#include <stdio.h>

// �ֲ����������ڱ���ת�������ĵ�ѹֵ(ģ����) 	 
float ADC2_ConvertedValueLocal_high;  
float ADC1_ConvertedValueLocal_low;
//ADֵ
extern uint32_t ADC_ConversionValue;

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

	while(1)
	{
		ADC1_ConvertedValueLocal_low=(float)(ADC_ConversionValue&0xffff)/4096*3.3;
		ADC2_ConvertedValueLocal_high=(float)(ADC_ConversionValue>>16)/4096*3.3;
		
		printf("\r\n PC1 value = %f V \r\n",ADC1_ConvertedValueLocal_low);
		printf("\r\n PC4 value = %f V \r\n",ADC2_ConvertedValueLocal_high);
		delay_ms(1000);
	}

}




