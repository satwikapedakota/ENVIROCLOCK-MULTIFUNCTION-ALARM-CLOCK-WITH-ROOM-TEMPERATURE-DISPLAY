//adc.c
#include<lpc214x.h>
#include"adc.h"
#include"adc_defines.h"
#include"pin_connect_defines.h"
#include"pin_function.h"
#include"delay.h"
   void Init_ADC(void)
{
AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
CfgPortPinFunc(0,28,PIN_FUNC2);
}
void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR)
{
//clear any previous channel selection
AD0CR&=0XFFFFFF00;
//update req channel select,
//start analog sampling & conversion
AD0CR|=1<<chNo|1<<ADC_START_BIT;
delayUS(3);
while(((AD0GDR>>DONE_BIT)&1)==0);
AD0CR&=~(1<<ADC_START_BIT);
*adcDVal=((AD0GDR>>RESULT_BITS)&1023);
*eAR=(*adcDVal * (3.3/1023));
}
