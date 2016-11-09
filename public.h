#include "stc12c5a60s2.h"
#include <intrins.h>
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include "Uart.h"
#include "BufferRing.h"
#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define FOSC    11059200L
#define T100Hz  (FOSC / 12 / 100)
void RcvDev();
void PollUps();
void Verify();
/****************************************************************
						指示灯引脚定义 
*****************************************************************/
sbit UPS_Test=P3^3; //测试指示灯
sbit Alarm=P1^4; //告警指示灯
sbit UPS_ShutDown=P1^5; //关机指示灯
/****************************************************************
						位操作定义      
*****************************************************************/
#define SET_BIT(data,bit)           (data |= (0x01l<<(bit)))
#define GET_BIT(data,bit)           ((data&(0x01l<<(bit))) == (0x01l<<(bit)))
#define CLR_BIT(data,bit)           (data &= (~(0x01l<<(bit))))
#define SET_BIT_EX(data,bit)		SET_BIT(data[(bit)/8], ((bit)%8))
#define CLR_BIT_EX(data,bit)		CLR_BIT(data[(bit)/8], ((bit)%8)) //清除位  左到右 
#define GET_BIT_EX(data,bit)		GET_BIT(data[(bit)/8], ((bit)%8))
#define ARRAYLEN(x)				(sizeof(x)/sizeof(x[0]))
/****************************************************************
						串口接收长度定义
*****************************************************************/
#define Com1_Rec_Buff_MaxLen 20
#define Com2_Rec_Buff_MaxLen 150
/****************************************************************
						任务结构体定义 
*****************************************************************/
typedef struct _UT100TaskVar
{
	unsigned char Task_flag;//任务控制位   2 串口1数据接收标志位 3 串口2数据接收标志位
	unsigned char PollIndex;//查询命令的索引
	unsigned int PollScale;//查询状态数据和其他数据的比例（用于查询比例的计算）
	unsigned int  UpsOffLineCount;//保存判断设备断线的查询次数
	unsigned int  Com1_Rec_time;
	unsigned char Com1_Rec_OK;
	unsigned int  Com2_Rec_time;
	unsigned char Com2_Rec_OK;
} UT100TaskVar, *PUT100TaskVar;

extern data volatile unsigned int LedTime;//超时计数
extern data volatile unsigned int PCA_Value;//PCA timer overflow interrupt
extern data volatile UT100TaskVar UTTaskVar;
extern data volatile BUFFERRING Com1BuffErRing,Com2BuffErRing;
extern data volatile unsigned char Com1_Rec_Buff[Com1_Rec_Buff_MaxLen];//串口接受数据缓存
extern volatile unsigned char Com2_Rec_Buff[Com2_Rec_Buff_MaxLen];//串口接受数据缓存
extern volatile unsigned char ComBuff[Com2_Rec_Buff_MaxLen];//串口动态内存区域
extern data volatile int TimeCount;//时间计数
extern data volatile unsigned int TimeOut;//超时计数