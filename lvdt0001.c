#include "stm32f4xx.h"

#define LVDT_PIN GPIO_Pin_0 
#define LVDT_PORT GPIOC 

void GPIO_Configuration(void);
void ADC_Configuration(void);

int main(void)
{
  GPIO_Configuration(); 
  ADC_Configuration(); 

  while (1)
  {
    ADC_SoftwareStartConv(ADC1); 
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); 

    uint16_t adc_val = ADC_GetConversionValue(ADC1);
    printf("ADC degeri: %d\n", adc_val); 

    for (int i=0; i<800000; i++);
  }
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // LVDT pini giriş olarak ayarlanır
  GPIO_InitStructure.GPIO_Pin = LVDT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LVDT_PORT, &GPIO_InitStructure);
}

void ADC_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);


  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);


  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_3Cycles);


  ADC_Cmd(ADC1, ENABLE);
}