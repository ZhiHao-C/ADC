#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include "bps_adc.h"
#include <stdio.h>

// 局部变量，用于保存转换计算后的电压值(模拟量) 	 
float ADC_ConvertedValueLocal[6];     
//AD值
extern uint16_t ADC_ConversionValue[6];

void delay_ms(int n)//延时函数
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
	
	printf("\r\n ----这是一个ADC多通道DMA读取实验----\r\n");

	while (1)
	{	
    
			ADC_ConvertedValueLocal[0] =(float) ADC_ConversionValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConversionValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConversionValue[2]/4096*3.3;
			ADC_ConvertedValueLocal[3] =(float) ADC_ConversionValue[3]/4096*3.3;
			ADC_ConvertedValueLocal[4] =(float) ADC_ConversionValue[4]/4096*3.3;
			ADC_ConvertedValueLocal[5] =(float) ADC_ConversionValue[5]/4096*3.3;
		
			printf("\r\n PC0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
			printf("\r\n PC1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
			printf("\r\n PC2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
			printf("\r\n PC3 value = %f V \r\n",ADC_ConvertedValueLocal[3]);
			printf("\r\n PC4 value = %f V \r\n",ADC_ConvertedValueLocal[4]);
			printf("\r\n PC5 value = %f V \r\n",ADC_ConvertedValueLocal[5]);
		
			printf("\r\n\r\n");
			delay_ms(500);		 
	}
}




