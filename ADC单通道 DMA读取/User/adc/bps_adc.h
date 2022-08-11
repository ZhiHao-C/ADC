#ifndef __BPS_ADC_H__
#define __BPS_ADC_H__

#include "stm32f10x.h" 

// ADC ���ѡ��
// ������ ADC1/2�����ʹ��ADC3���ж���ص�Ҫ�ĳ�ADC3��
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_x                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1

// ADC GPIO�궨��
// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC
#define    ADC_PIN                       GPIO_Pin_1
// ADC ͨ���궨��
#define    ADC_CHANNEL                   ADC_Channel_11

// DMA �궨��
#define DMA_CLK                         RCC_AHBPeriph_DMA1


#define DMA_Channel                     DMA1_Channel1
void ADC_Config_Init(void);
#endif
