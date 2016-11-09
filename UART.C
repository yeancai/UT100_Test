#include "public.h"

void Com1_Send_Byte(unsigned char Byte)
{
	SBUF = Byte;
	while(!TI);
	TI = 0;
}
void Com2_Send_Byte(unsigned char Byte)
{
	S2BUF = Byte;
	while(!(S2CON&S2TI));
	S2CON &= ~S2TI;
}
void Com1_Send_Buff(unsigned char *s,int Len)
{
    int i;
    for(i=0; i<Len; i++)
    {
        Com1_Send_Byte(*s++);    //Send current char and increment string ptr
    }
}
void Com2_Send_Buff(unsigned char *s,int Len)
{
    int i;
    for(i=0; i<Len; i++)
    {
        Com2_Send_Byte(*s++);    //Send current char and increment string ptr
    }
}

