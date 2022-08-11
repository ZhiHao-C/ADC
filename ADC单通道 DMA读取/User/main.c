#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include "bps_adc.h"
#include <stdio.h>
//uint8_t a[10]={1,2,3,4,5,6,7,8,9,10};
// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;     

extern uint16_t ADC_ConversionValue;

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
	
	printf("\r\n ----这是一个ADC单通道DMA读取实验----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConversionValue/4096*3.3; // 读取转换的AD值
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConversionValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

		delay_ms(1000);  
	}
	
}




