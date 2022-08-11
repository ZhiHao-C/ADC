#include "bps_adc.h"
uint32_t ADC_ConversionValue;

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	
	// ���� ADC IO ����ģʽ
	// ����Ϊģ������
	GPIO_InitStructure.GPIO_Pin = ADC1_PIN|ADC2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// ��ʼ�� ADC IO
	GPIO_Init(GPIOC, &GPIO_InitStructure);				
}

static void DMA_Config(void)
{
	
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(DMA_CLK,ENABLE);

	// ��λDMA������
	DMA_DeInit(DMA_Channel);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStruct.DMA_PeripheralBaseAddr=(ADC1_BASE+0x4c);
	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConversionValue;
	
	// ����Դ��������
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	/*
	���DMA_BufferSize ����Ҫ����Ĵ�����
	���������ָbuf���ֽڴ�С������ָDMA�Ĵ��������һ�δ�������ǣ�1�ֽڣ�2�ֽڣ�4�ֽڡ�
	ÿ��ADC�����󣬾�ͨ��DMA�����ݷ����ڴ��У�
	��DMA_MemoryBaseAddr+0��ַ��ʼ�ţ�
	ֱ��DMA_MemoryBaseAddr+DMA_BufferSize-1����ʱCNDTR���0�����������
	*/
	DMA_InitStruct.DMA_BufferSize = 1;
	
	// ����Ĵ����Ƿ�����
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	// ѭ������ģʽ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(DMA_Channel, &DMA_InitStruct);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(DMA_Channel , ENABLE);
}

static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	
/*****************************        ��ʼ����һ��ADC1             ****************************/
	// ��ADCʱ��
	RCC_APB2PeriphClockCmd ( ADC1_CLK, ENABLE );
	// ADC ģʽ����
	// ʹ������ADC����������Ϊ����ͬ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	// ת��ͨ��1��
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	// ��ʼ��ADC
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	/*****************************        ��ʼ���ڶ���ADC2             ****************************/
		// ��ADCʱ��
	RCC_APB2PeriphClockCmd ( ADC2_CLK, ENABLE );
	// ADC ģʽ����
	// ʹ������ADC����������Ϊ����ͬ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	// ת��ͨ��1��
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	// ��ʼ��ADC
	ADC_Init(ADC2, &ADC_InitStructure);
	/* ʹ��ADCx_2���ⲿ����ת�� */
  ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	
	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ���� ADC ͨ��ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1, ADC1_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC2, ADC2_CHANNEL, 1, ADC_SampleTime_55Cycles5);

	
	//DMA����
	ADC_DMACmd(ADC1,ENABLE);

	
	// ����ADC ������ʼת��
	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC2, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC1);
	ADC_ResetCalibration(ADC2);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC1));
	while(ADC_GetResetCalibrationStatus(ADC2));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC1);
	ADC_StartCalibration(ADC2);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC1));
	while(ADC_GetCalibrationStatus(ADC2));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	//ֻҪ����ADC1��Ϊ˫��ģʽ��ADC1����ADC2�Ǵӣ�ADC2�������ADC1�Ķ��ø�·������
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	
	
}


void ADC_Config_Init(void)
{
	ADCx_GPIO_Config();
	DMA_Config();
	ADCx_Mode_Config();
}




