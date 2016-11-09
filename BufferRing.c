#include "public.h"

/*
 * 初始化环形缓冲区
 * pBuff		:	缓冲环控制指针
 * pBase		:	缓冲区的缓冲指针
 * nSize		:	缓冲区的长度
 * bOverlay		:	1表示缓冲区满覆盖旧数据，0表示缓冲区满丢弃数据
 * @return		：	none
 */
void InitBufferRing(PBUFFERRING pBuff, unsigned char *pBase, unsigned int nSize, unsigned int bOverlay)
{
	memset(pBuff, 0, sizeof(*pBuff));
	pBuff->pBase = pBase;
	pBuff->nSize = nSize;
	pBuff->bOverlay = bOverlay;
}

/*
 * 增加一个数据到环形缓冲区
 * pBuff		:	缓冲环控制指针
 * data			:	追加的数据
 * @return		：	none
 */
void AddDataToBufferRing(PBUFFERRING pBuff, unsigned char Data)
{
	/*
	 * 检测是否为满
	 */
	if (pBuff->bFull)
	{
		/*
		 * 缓冲满，检测是否覆盖旧数据
		 */
		if (!pBuff->bOverlay)
		{
			/*
			 * 不覆盖旧数据的话则丢弃新数据
			 */
			return;
		}
	}
	/*
	 * 增加数据到缓冲中
	 */
	pBuff->pBase[pBuff->nTail] = Data;
	pBuff->nTail++;
	if (pBuff->nTail == pBuff->nSize)
	{
		pBuff->nTail = 0;
	}

	/*
	 * 缓冲区满并且允许覆盖最旧数据
	 */
	if (pBuff->bFull)
	{
		/*
		 * 删除最旧的数据
		 */
		pBuff->nHead = pBuff->nTail;
	}
	/*
	 * 检测是否环形缓冲区满
	 */
	else if (pBuff->nTail == pBuff->nHead)
	{
		/*
		 * 环形缓冲区满
		 */
		pBuff->bFull = 1;
	}
}
/*
 * 增加一个数据到环形缓冲区
 * pBuff		:	缓冲环控制指针
 * data			:	追加的数据
 * @return		：	none
 */
void AddDataToBufferRing1(PBUFFERRING pBuff, unsigned char Data)
{
	/*
	 * 检测是否为满
	 */
	if (pBuff->bFull)
	{
		/*
		 * 缓冲满，检测是否覆盖旧数据
		 */
		if (!pBuff->bOverlay)
		{
			/*
			 * 不覆盖旧数据的话则丢弃新数据
			 */
			return;
		}
	}
	/*
	 * 增加数据到缓冲中
	 */
	pBuff->pBase[pBuff->nTail] = Data;
	pBuff->nTail++;
	if (pBuff->nTail == pBuff->nSize)
	{
		pBuff->nTail = 0;
	}

	/*
	 * 缓冲区满并且允许覆盖最旧数据
	 */
	if (pBuff->bFull)
	{
		/*
		 * 删除最旧的数据
		 */
		pBuff->nHead = pBuff->nTail;
	}
	/*
	 * 检测是否环形缓冲区满
	 */
	else if (pBuff->nTail == pBuff->nHead)
	{
		/*
		 * 环形缓冲区满
		 */
		pBuff->bFull = 1;
	}
}
/*
 * 从环形缓冲区中读走一个数据
 * pBuff		:	缓冲环控制指针
 * @return		：	读取到的数据 -1表示缓冲没有数据
 */
unsigned int QuaryBufferRing(PBUFFERRING pBuff)
{
	int Size;
	if (pBuff->bFull == 1)
	{
		return pBuff->nSize;
	}
	Size = pBuff->nTail - pBuff->nHead;
	if (Size < 0)
	{
		Size += pBuff->nSize;
	}
	return Size;
}
#if 0
/*
 * 从环形缓冲区中读走一个数据
 * pBuff		:	缓冲环控制指针
 * @return		：	读取到的数据 -1表示缓冲没有数据
 */
int GetDataFromBufferRing(PBUFFERRING pBuff)
{
	int Data = -1;

	if ((pBuff->nHead != pBuff->nTail) || (pBuff->bFull == 1))	//两个指针相等时缓冲区为空
	{
		Data = pBuff->pBase[pBuff->nHead];
		pBuff->nHead++;
		if (pBuff->nHead == pBuff->nSize)
		{
			pBuff->nHead = 0;
		}
	}
	pBuff->bFull = 0;

	return Data;
}
#endif
/*
 * 从环形缓冲区中读走数据
 * pBuff		:	缓冲环控制指针
 * pDat			:	读取数据保存的缓冲地址
 * nLen			:	读取数据的长度
 * @return		：	实际读取的数据个数
 */
int GetDataFromBufferRingEx(PBUFFERRING pBuff, unsigned char *pDat, unsigned int len)
{
	int nCurLen, nWLen, nRd = 0;

	/*
	 * 当前缓冲的数据长度
	 */
	memset(pDat,0,len);
	nCurLen = QuaryBufferRing(pBuff);
	if (nCurLen > 0)
	{
		if (len > nCurLen)
		{
			len = nCurLen;
		}
		nWLen = pBuff->nSize - pBuff->nHead;
		if (pDat != NULL)
		{
			if (nWLen >= len)
			{
				memcpy(pDat, (char *) &pBuff->pBase[pBuff->nHead], len);
			}
			else
			{
				memcpy(pDat, (char *) &pBuff->pBase[pBuff->nHead], nWLen);
				memcpy(&pDat[nWLen], (char *) &pBuff->pBase[0], len - nWLen);
			}
		}
		pBuff->nHead += len;
		if (pBuff->nHead >= pBuff->nSize)
		{
			pBuff->nHead -= pBuff->nSize;
		}
		pBuff->bFull = 0;
		nRd = len;
	}

	return nRd;
}
#if 0
/*
 * 正向读取数据但是不移动指针（查看缓冲中的数据）
 * pBuff		:	缓冲环控制指针
 * nOffset		:	要查看数据的在缓冲中的起始偏移
 * pDat			:	读取数据保存的缓冲地址
 * nLen			:	读取数据的长度
 */
int PeekDataFromBufferRing(PBUFFERRING pBuff, int nOffset, unsigned char *pDat, int nLen)
{
	unsigned int nDatLen, nHead;
	int nRd = 0, nMaxRd;

	nDatLen = QuaryBufferRing(pBuff);

	if (nLen > nDatLen)
	{
		nLen = nDatLen;
	}
	nMaxRd = (nDatLen - nOffset);
	if (nLen > nMaxRd)
	{
		nLen = nMaxRd;
	}

	if (nLen > 0)
	{
		nHead = pBuff->nHead + nOffset;
		if (nHead >= pBuff->nSize)
		{
			nHead -= pBuff->nSize;
		}
		for (; nRd < nLen; nRd++)
		{
			pDat[nRd] = pBuff->pBase[nHead];
			nHead++;
			if (nHead >= pBuff->nSize)
			{
				nHead = 0;
			}
		}
	}

	return nRd;
}

/*
 * 反向读取数据但是不移动指针（查看缓冲中的数据）
 * pBuff		:	缓冲环控制指针
 * nOffset		:	要查看数据的在缓冲中的起始偏移
 * pDat			:	读取数据保存的缓冲地址
 * nLen			:	读取数据的长度
 */
int PeekRDataFromBufferRing(PBUFFERRING pBuff, int nOffset, unsigned char *pDat, int nLen)
{
	unsigned int nDatLen, nTail;
	int nRd = 0, nMaxRd;

	nDatLen = QuaryBufferRing(pBuff);

	if (nLen > nDatLen)
	{
		nLen = nDatLen;
	}
	nMaxRd = (nDatLen - nOffset);
	if (nLen > nMaxRd)
	{
		nLen = nMaxRd;
	}
	if (nLen > 0)
	{
		nTail = pBuff->nTail - nOffset - 1;
		if ((int) nTail < 0)
		{
			nTail += pBuff->nSize;
		}
		for (; nRd < nLen; nRd++)
		{
			pDat[nRd] = pBuff->pBase[nTail];
			nTail--;
			if ((int) nTail < 0)
			{
				nTail = pBuff->nSize - 1;
			}
		}
	}

	return nRd;
}

int IsBufferRingFull(PBUFFERRING pBuff)
{
	return pBuff->bFull;
}
#endif
/*
 * 清空缓冲环数据
 * pBuff		:	缓冲环控制指针
 */
void FlushBufferRing(PBUFFERRING pBuff)
{
	pBuff->nHead = pBuff->nTail;
	pBuff->bFull = 0;
}