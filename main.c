//main.c
#include<LPC214x.h>
#include"types.h"
#include"delay.h"
#include"main.h"
#include"main_defines.h"

//volatile
extern volatile u8 ShowMenu;

void EINT1_isr(void) __irq;
void Init_Interrupt(void)
{
//configure p0.3 as EINT1(func 3)
cfgPortPinFunc(0,1,EINT0_0_1);
//PINSEL0=(PINSEL0&~(3U<<6))|(3U<<6);//bits7:6=11->EINT1
//edge sensitive,falling edge
VICIntEnable=1<<14;
VICVectCntl0=(1<<5)|14;
VICVectAddr0=(u32)EINT1_isr;
EXTMODE=1<<0;
}

//isr handler
void Menu(void);
void EINT1_isr(void) __irq
{
Menu();
//ShowMenu=1;
EXTINT=1<<0;
VICVectAddr=0;
}
