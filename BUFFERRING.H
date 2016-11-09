
/*
*$Id: BufferRing.h 204 2010-07-25 09:33:24Z chenwin7 $
*$Rev: 204 $
*/

#ifndef __BUFFERRING_H
#define __BUFFERRING_H
#ifdef __cplusplus
extern "C" {
#endif
/*
 * ���λ���ṹ����
 */
typedef struct _bufferring
{
	/*
	 * ����ͷλ��
	 */
	volatile unsigned int nHead;
	/*
	 * ����βλ��
	 */
	volatile unsigned int nTail;
	/*
	 * ����ĳ���
	 */
	volatile unsigned int nSize;
	/*
	 * �����־���Ƿ�����
	 */
	volatile unsigned char bFull;
	/*
	 * ����洢���ԣ���֮���Ƿ񸲸Ǿ�����
	 */
	volatile unsigned char bOverlay;
	/*
	 * �������ַ
	 */
	volatile unsigned char *pBase;
} BUFFERRING, *PBUFFERRING;

void InitBufferRing(PBUFFERRING pBuff, unsigned char *pBase, unsigned int nSize, unsigned int bOverlay);
void AddDataToBufferRing(PBUFFERRING pBuff, unsigned char Data);
void AddDataToBufferRing1(PBUFFERRING pBuff, unsigned char Data);
unsigned int QuaryBufferRing(PBUFFERRING pBuff);
int GetDataFromBufferRingEx(PBUFFERRING pBuff, unsigned char *pDat, unsigned int len);
//int GetDataFromBufferRing(PBUFFERRING pBuff);
int IsBufferRingFull(PBUFFERRING pBuff);
#if 0
int PeekDataFromBufferRing(PBUFFERRING pBuff, int nOffset, unsigned char *pDat, int nLen);
int PeekRDataFromBufferRing(PBUFFERRING pBuff, int nOffset, unsigned char *pDat, int nLen);
#endif
void FlushBufferRing(PBUFFERRING pBuff);

#ifdef __cplusplus
}
#endif

#endif							/* __BUFFERRING_H */