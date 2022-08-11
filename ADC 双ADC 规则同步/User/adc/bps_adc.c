#include "bps_adc.h"
uint32_t ADC_ConversionValue;

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开 ADC IO端口时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	
	// 配置 ADC IO 引脚模式
	// 必须为模拟输入
	GPIO_InitStructure.GPIO_Pin = ADC1_PIN|ADC2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// 初始化 ADC IO
	GPIO_Init(GPIOC, &GPIO_InitStructure);				
}

static void DMA_Config(void)
{
	
	DMA_InitTypeDef DMA_InitStruct;
	RCC_AHBPeriphClockCmd(DMA_CLK,ENABLE);

	// 复位DMA控制器
	DMA_DeInit(DMA_Channel);
	
	// 配置 DMA 初始化结构体
	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStruct.DMA_PeripheralBaseAddr=(ADC1_BASE+0x4c);
	
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConversionValue;
	
	// 数据源来自外设
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	/*
	这个DMA_BufferSize 就是要传输的次数。
	这个并不是指buf的字节大小，而是指DMA的传输次数，一次传输可以是：1字节，2字节，4字节。
	每次ADC采样后，就通过DMA把数据放在内存中，
	从DMA_MemoryBaseAddr+0地址开始放，
	直到DMA_MemoryBaseAddr+DMA_BufferSize-1，此时CNDTR变成0，传输结束。
	*/
	DMA_InitStruct.DMA_BufferSize = 1;
	
	// 外设寄存器是否自增
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址固定
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	// 循环传输模式
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;	

	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(DMA_Channel, &DMA_InitStruct);
	
	// 使能 DMA 通道
	DMA_Cmd(DMA_Channel , ENABLE);
}

static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	
/*****************************        初始化第一个ADC1             ****************************/
	// 打开ADC时钟
	RCC_APB2PeriphClockCmd ( ADC1_CLK, ENABLE );
	// ADC 模式配置
	// 使用两个ADC配置且配置为规则同步
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	// 禁止扫描模式，多通道需要，单通道不需要
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// 连续转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// 不用外部触发转换，软件开启即可
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// 转换结果右对齐
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	// 转换通道1个
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	// 初始化ADC
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	/*****************************        初始化第二个ADC2             ****************************/
		// 打开ADC时钟
	RCC_APB2PeriphClockCmd ( ADC2_CLK, ENABLE );
	// ADC 模式配置
	// 使用两个ADC配置且配置为规则同步
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	// 禁止扫描模式，多通道需要，单通道不需要
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// 连续转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// 不用外部触发转换，软件开启即可
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// 转换结果右对齐
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	// 转换通道1个
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	// 初始化ADC
	ADC_Init(ADC2, &ADC_InitStructure);
	/* 使能ADCx_2的外部触发转换 */
  ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	
	
	// 配置ADC时钟为PCLK2的8分频，即9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// 配置 ADC 通道转换顺序和采样时间
	ADC_RegularChannelConfig(ADC1, ADC1_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC2, ADC2_CHANNEL, 1, ADC_SampleTime_55Cycles5);

	
	//DMA请求
	ADC_DMACmd(ADC1,ENABLE);

	
	// 开启ADC ，并开始转换
	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC2, ENABLE);
	
	// 初始化ADC 校准寄存器  
	ADC_ResetCalibration(ADC1);
	ADC_ResetCalibration(ADC2);
	// 等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADC1));
	while(ADC_GetResetCalibrationStatus(ADC2));
	
	// ADC开始校准
	ADC_StartCalibration(ADC1);
	ADC_StartCalibration(ADC2);
	// 等待校准完成
	while(ADC_GetCalibrationStatus(ADC1));
	while(ADC_GetCalibrationStatus(ADC2));
	
	// 由于没有采用外部触发，所以使用软件触发ADC转换 
	//只要触发ADC1因为双重模式下ADC1是主ADC2是从，ADC2的命令从ADC1的多用复路触发器
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	
	
}


void ADC_Config_Init(void)
{
	ADCx_GPIO_Config();
	DMA_Config();
	ADCx_Mode_Config();
}




