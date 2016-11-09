void Com1_Send_Byte(unsigned char Byte);
void Com1_Send_Buff(unsigned char *s,int Len);
void Com2_Send_Byte(unsigned char Byte);
void Com2_Send_Buff(unsigned char *s,int Len);
unsigned short Uart0CheckCRC16(unsigned char *puchMsg, unsigned char usDataLen) ;