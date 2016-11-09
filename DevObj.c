#include "public.h"
void RcvDev(){
	unsigned char ComLen;
	ComLen=GetDataFromBufferRingEx(&Com1BuffErRing,ComBuff,sizeof(Com1_Rec_Buff));
	if(strcmp(ComBuff,"Q1\r")==0){
			Com1_Send_Buff("(226.0 185.0 220.0 032 23.5 2.25 50.0 00000000\r",strlen("(226.0 185.0 220.0 032 23.5 2.25 50.0 00000000\r"));
		}else if(strcmp(ComBuff,"I\r")==0){
			Com1_Send_Buff("#Vnata Co., LTD  V50C       Ver 1.00  \r",strlen("#Vnata Co., LTD  V50C       Ver 1.00  \r"));
		}else if(strcmp(ComBuff,"F\r")==0){
			Com1_Send_Buff("#220.0 120 222.0 50.0\r",strlen("#220.0 120 222.0 50.0\r"));
		}else if(ComBuff[0]==0x54&&ComBuff[3]==0x0D){
			UPS_Test=0;
		}else if(ComBuff[0]==0x53&&ComBuff[3]==0x0D){
			UPS_ShutDown=0;
		}else if(strcmp(ComBuff,"C\r")==0){
			UPS_ShutDown=1;
		}else if(strcmp(ComBuff,"CT\r")==0){
			UPS_Test=1;
		}
	FlushBufferRing(&Com1BuffErRing);//清除串口1数据
	UTTaskVar.Com1_Rec_OK=0;
}
void PollUps(){
	unsigned char PollBuff[][5]={
										{"Q1\r"},
										{"T01\r"},
										{"CT\r"},
										{"S01\r"},
										{"C\r"}
									};
	if(TimeCount<0&&GET_BIT(UTTaskVar.Task_flag,4)){
		TimeCount = 1000/10;//查询时间重置
		Com2_Send_Buff(PollBuff[UTTaskVar.PollIndex],strlen(PollBuff[UTTaskVar.PollIndex]));
		UTTaskVar.PollIndex++;
		if(UTTaskVar.PollIndex==ARRAYLEN(PollBuff)) UTTaskVar.PollIndex=0;
	}
}
void Verify(){
	unsigned char ComLen;
	ComLen=GetDataFromBufferRingEx(&Com2BuffErRing,ComBuff,sizeof(Com2_Rec_Buff));
	if(strcmp(ComBuff,"(226.0 185.0 220.0 032 23.5 2.25 50.0 00000000\r")==0){
	Alarm=1;
	}else{
	Alarm=0;
	}
	FlushBufferRing(&Com2BuffErRing);//清除串口1数据
	UTTaskVar.Com2_Rec_OK=0;
	TimeOut=0;
}