#include "public.h"
void tm0_isr() interrupt 1
{
	if(GET_BIT(UTTaskVar.Task_flag,2)){
		UTTaskVar.Com1_Rec_time++;
		if(UTTaskVar.Com1_Rec_time>2)
		{
			UTTaskVar.Com1_Rec_OK=1;
			CLR_BIT(UTTaskVar.Task_flag,2);
		}
	}
	if(GET_BIT(UTTaskVar.Task_flag,3)){
		UTTaskVar.Com2_Rec_time++;
		if(UTTaskVar.Com2_Rec_time>2)
		{
			UTTaskVar.Com2_Rec_OK=1;
			CLR_BIT(UTTaskVar.Task_flag,3);
		}
	}
}
void PCA_isr() interrupt 7
{
    CCF0 = 0; //Clear interrupt flag
    CCAP0L = PCA_Value;
    CCAP0H = PCA_Value >> 8; //Update compare value
    PCA_Value += T100Hz;
    TimeCount--;
	TimeOut++;
	if(++LedTime>104){
		//RunLed=~RunLed;
		LedTime=0;
	}
}
void Uart0_Isr() interrupt 4
{
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
		AddDataToBufferRing(&Com1BuffErRing,SBUF);
		UTTaskVar.Com1_Rec_time=0;
		SET_BIT(UTTaskVar.Task_flag,2);	//设置接收到新的数据标志
    }
}
void Uart1_Isr() interrupt 8//串口接收处理中断
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
		AddDataToBufferRing1(&Com2BuffErRing,S2BUF);
		UTTaskVar.Com2_Rec_time=0;
		SET_BIT(UTTaskVar.Task_flag,3);	//设置接收到新的数据标志
    }
}
