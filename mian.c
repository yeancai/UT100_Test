#include "public.h"
/*code is far away from bug with the animal protecting
  *  ��������������
  *�����ߩ��������ߩ�
  *������������������
  *������������������
  *�����ש������ס���
  *������������������
  *���������ߡ�������
  *������������������
  *������������������
  *�����������������ޱ���
  *��������������������BUG��
  *����������������������
  *���������������������ǩ�
  *������������������������
  *���������������ש�����
  *���������ϩϡ����ϩ�
  *���������ߩ������ߩ�
  *
  *




      **
      *
      *----------Dragon be here!----------

              ��������������
            �����ߩ��������ߩ�
            ������������������
            ������������������
            �����ש������ס���
            ������������������
            ���������ߡ�������
            ������������������
            ������������������
                    ����������
                    ����������
                    ������������������
                    �����������������ǩ�
                    ��������������������
                    �����������ש�����
                      ���ϩϡ����ϩ�
                      ���ߩ������ߩ�
          ���������������޳�û������������ *

      **

                 ��������������
               �����ߩ��������ߩ�
               ������������������
               ������������������
               ������������������
               ������������������
               ��...���С�...����
               ������������������
               ������������������
                       ������������Code is far away from bug with the animal protecting
                       ���������� ���ޱ���,������bug
                       ����������
                       ����������
                       ����������
                       ����������
                       ������������������
                       �����������������ǩ�
                       ��������������������
                       �����������ש�����
                         ���ϩϡ����ϩ�
                         ���ߩ������ߩ� *

      **
      *������������������������������+ +
      *�������������������ߩ��������ߩ� + +
      *��������������������������������
      *�������������������������������� ++ + + +
      *              ��  ????��????  ��+
      *�������������������������������� +
      *�����������������������ߡ�������
      *�������������������������������� + +
      *��������������������������������
      *����������������������������
      *���������������������������� + + + +
      *������������������������������������Code is far away from bug with the animal protecting
      *���������������������������� + �����������ޱ���,������bug
      *����������������������������
      *��������������������������������+
      *���������������������� �� ���������� + +
      *�������������������� ������������ �ǩ�
      *�������������������� ���������� ������
      *�����������������������������ש����� + + + +
      *�����������������������ϩϡ����ϩ�
      *�����������������������ߩ������ߩ�+ + + +
      */


//1ֻ�� == one sheep
//2ֻ�� == two sheeps
//3ֻ�� == three sheeps
//4ֻ�� == four sheeps
//5ֻ�� == five sheeps
//6ֻ�� == six sheeps
//7ֻ�� == seven sheeps
//8ֻ�� == eight sheeps
//9ֻ�� == nine sheeps
//10ֻ�� == ten sheeps
//11ֻ�� == eleven sheeps
//12ֻ�� == twelve sheeps
//13ֻ�� == thirteen sheeps
//14ֻ�� == fourteen sheeps
//15ֻ�� == fifteen sheeps
//16ֻ�� == sixteen sheeps
//17ֻ�� == seventeen sheeps
//18ֻ�� == eighteen sheeps
//19ֻ�� == nineteen sheeps
//20ֻ�� == twenty sheeps
//21ֻ�� == twenty one sheeps
//22ֻ�� == twenty two sheeps
//23ֻ�� == twenty three sheeps
//24ֻ�� == twenty four sheeps
//25ֻ�� == twenty five sheeps
//26ֻ�� == twenty six sheeps
//27ֻ�� == twenty seven sheeps
//28ֻ�� == twenty eight sheeps
//29ֻ�� == twenty nine sheeps
//30ֻ�� == thirty sheeps
//�����˯�˰ɣ����ˣ���Ҫ�ٸ�����Ĵ����ˣ�˯����~~


/**
 *      ����
 *       ||
 *       ||
 *      \  /
 *       \/
 *      ����
 * ������ = rand(20,25))��    ��==============
 *       ||                                                                 ||
 *       ||                                                                 ||
 *       ||        ף�����п���������                         ||
 *       ||            ��Զ����                                       ||
 *       ||                                                                 ||
 *      \  /                                                                ||
 *       \/                                                                 ||
 *�� 20 <= ���� <= 25��        ===============
 *       ||
 *       ||
 *      \  /
 *       \/
 *     ����״̬
 */
void Timer0Init(void)		//1΢��@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xF5;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}
void STCInit(void)
{
	IE2 = IE2|0x01; //Enable UART2 interrupt
	ES=1; //�������ж�
	CR = 1;//PCA timer start run
	ET0=1;//��ʱ��0 �ж�
	EA=1;
}
void Uart0Init(int BaudRate)     //@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ

    switch(BaudRate)
    {
    case 2400:
        TL1 = 0x70;		//�趨��ʱ��ֵ
		TH1 = 0x70;		//�趨��ʱ����װֵ
        break;
    case 4800:
      	TL1 = 0xB8;		//�趨��ʱ��ֵ
		TH1 = 0xB8;		//�趨��ʱ����װֵ
        break;
    case 9600:
        TL1 = 0xDC;		//�趨��ʱ��ֵ
		TH1 = 0xDC;		//�趨��ʱ����װֵ
        break;
    case 19200:
        TL1 = 0xEE;		//�趨��ʱ��ֵ
		TH1 = 0xEE;		//�趨��ʱ����װֵ
        break;
    default://Ĭ�ϲ�����9600
        TL1 = 0xDC;		//�趨��ʱ��ֵ
		TH1 = 0xDC;		//�趨��ʱ����װֵ
        break;
    }
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TI = 0;
	TR1 = 1;		//������ʱ��1
}

void Uart1Init(int BaudRate)     //@11.0592MHz
{
	AUXR &= 0xF7;		//�����ʲ�����
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
    switch(BaudRate)
    {
    case 2400:
        BRT = 0x70;		//�趨���������ʷ�������װֵ
        break;
    case 4800:
      	BRT = 0xB8;		//�趨���������ʷ�������װֵ
        break;
    case 9600:
        BRT = 0xDC;		//�趨���������ʷ�������װֵ
        break;
    case 19200:
        BRT = 0xEE;		//�趨���������ʷ�������װֵ
        break;
    default://Ĭ�ϲ�����9600
        BRT = 0xDC;		//�趨���������ʷ�������װֵ
        break;
    }
	S2CON &= ~S2TI;
	AUXR |= 0x10;		//�������������ʷ�����
}
void PCA_Inti(void)
{
    CCON = 0;                       //Initial PCA control register
    //PCA timer stop running
    //Clear CF flag
    //Clear all module interrupt flag
    CL = 0;                         //Reset PCA base timer
    CH = 0;
    CMOD = 0x00;                    //Set PCA timer clock source as Fosc/12
    //Disable PCA timer overflow interrupt
    PCA_Value = T100Hz;
    CCAP0L = PCA_Value;
    CCAP0H = PCA_Value >> 8;            //Initial PCA module-0
    PCA_Value += T100Hz;
	TimeCount=0;
    TimeOut=0;
	LedTime=0;
	
    CCAPM0 = 0x49;                  //PCA module-0 work in 16-bit timer mode and enable PCA interrupt
}
void Delay5000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 211;
	j = 30;
	k = 11;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

data volatile unsigned int LedTime;//��ʱ����
data volatile int TimeCount;//ʱ�����
data volatile unsigned int TimeOut;//��ʱ����
data volatile unsigned int PCA_Value;//PCA timer overflow interrupt
data volatile UT100TaskVar UTTaskVar;
data volatile BUFFERRING Com1BuffErRing,Com2BuffErRing;
data volatile unsigned char Com1_Rec_Buff[Com1_Rec_Buff_MaxLen];//���ڽ������ݻ���
volatile unsigned char Com2_Rec_Buff[Com2_Rec_Buff_MaxLen];//���ڽ������ݻ���
volatile unsigned char ComBuff[Com2_Rec_Buff_MaxLen];//���ڶ�̬�ڴ�����
void main(){
	UPS_Test=Alarm=UPS_ShutDown=0;
	memset(&UTTaskVar,0,sizeof(UTTaskVar));
	Timer0Init();
	PCA_Inti();
	Uart0Init(2400);
	Uart1Init(2400);
	STCInit();
	//��ʼ������1������,����������������
	InitBufferRing(&Com1BuffErRing,Com1_Rec_Buff,sizeof(Com1_Rec_Buff),0);
	//��ʼ������2������,����������������
	InitBufferRing(&Com2BuffErRing,Com2_Rec_Buff,sizeof(Com2_Rec_Buff),0);
	Delay5000ms();
	UPS_Test=Alarm=UPS_ShutDown=1;
	while(1){
		PollUps();
		if(UTTaskVar.Com1_Rec_OK==1){
			//�ظ���λ����ѯָ��
			RcvDev();
		}
		
		if(UTTaskVar.PollIndex==1){
			if(UTTaskVar.Com2_Rec_OK==0)
			{
				if(TimeOut>100){
					TimeOut=0;//���ָ�0 �ᵼ�����ϵ���
					SET_BIT(UTTaskVar.Task_flag,4);//�ɷ�����һ����ѯָ��
					Alarm=0;
					}
			}
			if(UTTaskVar.Com2_Rec_OK==1)
			{
				Verify();
			}
		}else{
		SET_BIT(UTTaskVar.Task_flag,4);//�ɷ�����һ����ѯָ��
		TimeOut=0;
		}
	}
}