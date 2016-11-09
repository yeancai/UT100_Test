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
						ָʾ�����Ŷ��� 
*****************************************************************/
sbit UPS_Test=P3^3; //����ָʾ��
sbit Alarm=P1^4; //�澯ָʾ��
sbit UPS_ShutDown=P1^5; //�ػ�ָʾ��
/****************************************************************
						λ��������      
*****************************************************************/
#define SET_BIT(data,bit)           (data |= (0x01l<<(bit)))
#define GET_BIT(data,bit)           ((data&(0x01l<<(bit))) == (0x01l<<(bit)))
#define CLR_BIT(data,bit)           (data &= (~(0x01l<<(bit))))
#define SET_BIT_EX(data,bit)		SET_BIT(data[(bit)/8], ((bit)%8))
#define CLR_BIT_EX(data,bit)		CLR_BIT(data[(bit)/8], ((bit)%8)) //���λ  ���� 
#define GET_BIT_EX(data,bit)		GET_BIT(data[(bit)/8], ((bit)%8))
#define ARRAYLEN(x)				(sizeof(x)/sizeof(x[0]))
/****************************************************************
						���ڽ��ճ��ȶ���
*****************************************************************/
#define Com1_Rec_Buff_MaxLen 20
#define Com2_Rec_Buff_MaxLen 150
/****************************************************************
						����ṹ�嶨�� 
*****************************************************************/
typedef struct _UT100TaskVar
{
	unsigned char Task_flag;//�������λ   2 ����1���ݽ��ձ�־λ 3 ����2���ݽ��ձ�־λ
	unsigned char PollIndex;//��ѯ���������
	unsigned int PollScale;//��ѯ״̬���ݺ��������ݵı��������ڲ�ѯ�����ļ��㣩
	unsigned int  UpsOffLineCount;//�����ж��豸���ߵĲ�ѯ����
	unsigned int  Com1_Rec_time;
	unsigned char Com1_Rec_OK;
	unsigned int  Com2_Rec_time;
	unsigned char Com2_Rec_OK;
} UT100TaskVar, *PUT100TaskVar;

extern data volatile unsigned int LedTime;//��ʱ����
extern data volatile unsigned int PCA_Value;//PCA timer overflow interrupt
extern data volatile UT100TaskVar UTTaskVar;
extern data volatile BUFFERRING Com1BuffErRing,Com2BuffErRing;
extern data volatile unsigned char Com1_Rec_Buff[Com1_Rec_Buff_MaxLen];//���ڽ������ݻ���
extern volatile unsigned char Com2_Rec_Buff[Com2_Rec_Buff_MaxLen];//���ڽ������ݻ���
extern volatile unsigned char ComBuff[Com2_Rec_Buff_MaxLen];//���ڶ�̬�ڴ�����
extern data volatile int TimeCount;//ʱ�����
extern data volatile unsigned int TimeOut;//��ʱ����