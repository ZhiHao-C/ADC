#ifndef __BPS_ADC_H__
#define __BPS_ADC_H__

#include "stm32f10x.h" 

// 双模式时，ADC1和ADC2转换的数据都存放在ADC1的数据寄存器，
// ADC1的在低十六位，ADC2的在高十六位
// 双ADC模式的第一个ADC，必须是ADC1
#define    ADC1_CLK                       RCC_APB2Periph_ADC1

#define    ADC1_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC1_PORT                      GPIOC
#define    ADC1_PIN                       GPIO_Pin_1
#define    ADC1_CHANNEL                   ADC_Channel_11

// 双ADC模式的第二个ADC，必须是ADC2

#define    ADC2_CLK                         RCC_APB2Periph_ADC2

#define    ADC2_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC2_PORT                      GPIOC
#define    ADC2_PIN                       GPIO_Pin_4
#define    ADC2_CHANNEL                 ADC_Channel_14

// DMA 宏定义
#define DMA_CLK                         RCC_AHBPeriph_DMA1


#define DMA_Channel                     DMA1_Channel1
void ADC_Config_Init(void);
#endif
