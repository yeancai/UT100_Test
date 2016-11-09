
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
 * 环形缓冲结构定义
 */
typedef struct _bufferring
{
	/*
	 * 缓冲头位置
	 */
	volatile unsigned int nHead;
	/*
	 * 缓冲尾位置
	 */
	volatile unsigned int nTail;
	/*
	 * 缓冲的长度
	 */
	volatile unsigned int nSize;
	/*
	 * 缓冲标志，是否满等
	 */
	volatile unsigned char bFull;
	/*
	 * 缓冲存储属性，满之后是否覆盖旧数据
	 */
	volatile unsigned char bOverlay;
	/*
	 * 缓冲基地址
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
