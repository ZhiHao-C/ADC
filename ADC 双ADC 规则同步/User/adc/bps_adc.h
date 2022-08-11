#ifndef __BPS_ADC_H__
#define __BPS_ADC_H__

#include "stm32f10x.h" 

// ˫ģʽʱ��ADC1��ADC2ת�������ݶ������ADC1�����ݼĴ�����
// ADC1���ڵ�ʮ��λ��ADC2���ڸ�ʮ��λ
// ˫ADCģʽ�ĵ�һ��ADC��������ADC1
#define    ADC1_CLK                       RCC_APB2Periph_ADC1

#define    ADC1_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC1_PORT                      GPIOC
#define    ADC1_PIN                       GPIO_Pin_1
#define    ADC1_CHANNEL                   ADC_Channel_11

// ˫ADCģʽ�ĵڶ���ADC��������ADC2

#define    ADC2_CLK                         RCC_APB2Periph_ADC2

#define    ADC2_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC2_PORT                      GPIOC
#define    ADC2_PIN                       GPIO_Pin_4
#define    ADC2_CHANNEL                 ADC_Channel_14

// DMA �궨��
#define DMA_CLK                         RCC_AHBPeriph_DMA1


#define DMA_Channel                     DMA1_Channel1
void ADC_Config_Init(void);
#endif
