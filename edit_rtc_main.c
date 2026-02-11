//edit_rtc_main.c
//mini_main.c
#include<LPC214x.h>
#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"adc.h"
#include"defines.h"
#include"kpm.h"
#include"rtc.h"
#include"adc_defines.h"
#include"pin_connect_defines.h"
#include"kpm_defines.h"
#include"rtc_defines.h"
#include"lcd_defines.h"

s32 hour,min,sec,date,month,year,day,num;
u32 adcDVal,temp,ChNo=1,Key,Alarm_Ring;
u8 bell[]={0x04,0x0E,0x0E,0x0E,0x01F,0x00,0x0E,0x00};
f32 eAR;
//Menu display
volatile u8 ShowMenu=0;
//Alaram variables
u32 alarm_hour=0,alarm_min=0,ent_flag=0;
u32 Key;
u32 i;
void Alarm(void);
void edit(s32*hour,s32*min,s32*sec,s32*day,s32*date,s32*month,s32*year);
void Menu(void);
//main function
int main()
{
Init_ADC();
Init_LCD();
Init_KPM();
Init_Interrupt();
RTC_Init();
SetRTCTimeInfo(15,35,00);
IODIR0|=1<<0;
SetRTCDateInfo(29,10,2025);
SetRTCDay(1);
while(1)
{
if(ShowMenu==0)
{
/*---Line 1:Time+Day--*/
CmdLCD(0x80);
GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
GetRTCDay(&day);
CmdLCD(0x80+10);
DisplayRTCDay(day);

/*--Line 2:Date+Temperature---*/
CmdLCD(0xc0);
GetRTCDateInfo(&date,&month,&year);
DisplayRTCDate(date,month,year);
Read_ADC(ChNo,&adcDVal,&eAR);
temp=(u32) (eAR*100.0f);
CmdLCD(0xc0+12);
U32LCD(temp);
CharLCD(0xDf);
CharLCD('C');
/*Alaram Check(when seconds==0 to trigger once per minute)*/
if(HOUR==alarm_hour && MIN==alarm_min)
{
if(Alarm_Ring==0)
{
BuildCGRAM(bell,8);
CmdLCD(0x80+15);
CharLCD(0);
IOSET0=1<<0;
//stop alaram
if((IOPIN0>>22&1)==0)
{
IOCLR0=1<<0;
CmdLCD(0x80+15);
CharLCD(' ');
Alarm_Ring=1;
}
}
}
else
{
CmdLCD(0x80+15);
CharLCD(' ');
Alarm_Ring=0;
}
}
}
}

/*---Menu---*/
void Menu(void)
{
while(1)
{
CmdLCD(0x01);
StrLCD("1.Edit RTC");
CmdLCD(0xc0);
StrLCD("2.ALARM 3.EXIT");
Key=(u8)KeyScan();
//After releasing the switch
while(ColScan()==0);
CmdLCD(0x01);
CharLCD(Key);
switch(Key)
{
case '1':edit(&hour,&min,&sec,&day,&date,&month,&year);
break;
case '2':Alarm();
break;
case '3':CmdLCD(0x01);
return;
}
}
}

/*---ALARAM SET---*/
void Alarm(void)
{
alarm_hour=0;
alarm_min=0;
while(1)
{
CmdLCD(0x01);
StrLCD("SET ALARM");
CmdLCD(0Xc0);
StrLCD("1.HH2.MM3.EXIT");
Key=(u8)KeyScan();
while(ColScan()==0);
switch(Key)
{
case '1':CmdLCD(0x01);
StrLCD("ENTER HOUR(0-23)");
CmdLCD(0Xc0);
num=ReadNum();
if(num>=0 && num<24)
{
alarm_hour=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
CmdLCD(0x01);
}
break;
case '2':CmdLCD(0x01);
StrLCD("ENTER MIN(0-59)");
CmdLCD(0xc0);
num=ReadNum();
if(num>=0 && num<60)
{
alarm_min=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
CmdLCD(0x01);
}
break;
case '3':CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("ALARAM SET");
delayMS(200);
CmdLCD(0x01);
return ;
}
}
}

/*---Edit Function---*/
void edit(s32*hour,s32*min,s32*sec,s32*day,s32*date,s32*month,s32*year)
{
s32 num;
u8 Key;

while(1)
{
CmdLCD(0x01);
StrLCD("1.H2.M3.S4.D");
CmdLCD(0xc0);
StrLCD("5.DD6.MM7.Y8.E");
Key=(u8)KeyScan();
while(ColScan()==0);
switch(Key)
{
case '1':CmdLCD(0x01);
StrLCD("ENTER HOUR(0-23)");
CmdLCD(0xc0);
num=ReadNum();
if(num>=0 && num<24)
{
HOUR=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '2':CmdLCD(0x01);
StrLCD("ENTER MIN(0-59)");
CmdLCD(0xc0);
num=ReadNum();
if(num>=0 && num<60)
{
MIN=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '3':CmdLCD(0x01);
StrLCD("ENTER SEC(0-59)");
CmdLCD(0xc0);
num=ReadNum();
if(num>=0 && num<60)
{
SEC=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '4':CmdLCD(0x01);
StrLCD("ENTER DAY(0-6)");
CmdLCD(0xc0);
num=ReadNum();
if(num>=0 && num<7)
{
DOW=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '5':CmdLCD(0x01);
StrLCD("ENTER DATE(1-31)");
CmdLCD(0xc0);
num=ReadNum();
if(num>=0 && num<=31)
{
DOM=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '6':CmdLCD(0x01);
StrLCD("ENTER MONTH(1-12)");
num=ReadNum();
if(num>=1 && num<=12)
{
MONTH=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '7':CmdLCD(0x01);
StrLCD("ENTER YEAR");
CmdLCD(0xc0);
num=ReadNum();
if(num>=2000 && num<=2200)
{
YEAR=num;
}
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("Invalid Inputs");
delayMS(200);
}
break;
case '8':CmdLCD(0x01);
return;
default:CmdLCD(0x01);
StrLCD("Invalid Input");
delayS(1);
break;
}
}
}
