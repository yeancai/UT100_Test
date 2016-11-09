#include "public.h"

/*
 * ��ʼ�����λ�����
 * pBuff		:	���廷����ָ��
 * pBase		:	�������Ļ���ָ��
 * nSize		:	�������ĳ���
 * bOverlay		:	1��ʾ�����������Ǿ����ݣ�0��ʾ����������������
 * @return		��	none
 */
void InitBufferRing(PBUFFERRING pBuff, unsigned char *pBase, unsigned int nSize, unsigned int bOverlay)
{
	memset(pBuff, 0, sizeof(*pBuff));
	pBuff->pBase = pBase;
	pBuff->nSize = nSize;
	pBuff->bOverlay = bOverlay;
}

/*
 * ����һ�����ݵ����λ�����
 * pBuff		:	���廷����ָ��
 * data			:	׷�ӵ�����
 * @return		��	none
 */
void AddDataToBufferRing(PBUFFERRING pBuff, unsigned char Data)
{
	/*
	 * ����Ƿ�Ϊ��
	 */
	if (pBuff->bFull)
	{
		/*
		 * ������������Ƿ񸲸Ǿ�����
		 */
		if (!pBuff->bOverlay)
		{
			/*
			 * �����Ǿ����ݵĻ�����������
			 */
			return;
		}
	}
	/*
	 * �������ݵ�������
	 */
	pBuff->pBase[pBuff->nTail] = Data;
	pBuff->nTail++;
	if (pBuff->nTail == pBuff->nSize)
	{
		pBuff->nTail = 0;
	}

	/*
	 * �������������������������
	 */
	if (pBuff->bFull)
	{
		/*
		 * ɾ����ɵ�����
		 */
		pBuff->nHead = pBuff->nTail;
	}
	/*
	 * ����Ƿ��λ�������
	 */
	else if (pBuff->nTail == pBuff->nHead)
	{
		/*
		 * ���λ�������
		 */
		pBuff->bFull = 1;
	}
}
/*
 * ����һ�����ݵ����λ�����
 * pBuff		:	���廷����ָ��
 * data			:	׷�ӵ�����
 * @return		��	none
 */
void AddDataToBufferRing1(PBUFFERRING pBuff, unsigned char Data)
{
	/*
	 * ����Ƿ�Ϊ��
	 */
	if (pBuff->bFull)
	{
		/*
		 * ������������Ƿ񸲸Ǿ�����
		 */
		if (!pBuff->bOverlay)
		{
			/*
			 * �����Ǿ����ݵĻ�����������
			 */
			return;
		}
	}
	/*
	 * �������ݵ�������
	 */
	pBuff->pBase[pBuff->nTail] = Data;
	pBuff->nTail++;
	if (pBuff->nTail == pBuff->nSize)
	{
		pBuff->nTail = 0;
	}

	/*
	 * �������������������������
	 */
	if (pBuff->bFull)
	{
		/*
		 * ɾ����ɵ�����
		 */
		pBuff->nHead = pBuff->nTail;
	}
	/*
	 * ����Ƿ��λ�������
	 */
	else if (pBuff->nTail == pBuff->nHead)
	{
		/*
		 * ���λ�������
		 */
		pBuff->bFull = 1;
	}
}
/*
 * �ӻ��λ������ж���һ������
 * pBuff		:	���廷����ָ��
 * @return		��	��ȡ�������� -1��ʾ����û������
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
 * �ӻ��λ������ж���һ������
 * pBuff		:	���廷����ָ��
 * @return		��	��ȡ�������� -1��ʾ����û������
 */
int GetDataFromBufferRing(PBUFFERRING pBuff)
{
	int Data = -1;

	if ((pBuff->nHead != pBuff->nTail) || (pBuff->bFull == 1))	//����ָ�����ʱ������Ϊ��
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
 * �ӻ��λ������ж�������
 * pBuff		:	���廷����ָ��
 * pDat			:	��ȡ���ݱ���Ļ����ַ
 * nLen			:	��ȡ���ݵĳ���
 * @return		��	ʵ�ʶ�ȡ�����ݸ���
 */
int GetDataFromBufferRingEx(PBUFFERRING pBuff, unsigned char *pDat, unsigned int len)
{
	int nCurLen, nWLen, nRd = 0;

	/*
	 * ��ǰ��������ݳ���
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
 * �����ȡ���ݵ��ǲ��ƶ�ָ�루�鿴�����е����ݣ�
 * pBuff		:	���廷����ָ��
 * nOffset		:	Ҫ�鿴���ݵ��ڻ����е���ʼƫ��
 * pDat			:	��ȡ���ݱ���Ļ����ַ
 * nLen			:	��ȡ���ݵĳ���
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
 * �����ȡ���ݵ��ǲ��ƶ�ָ�루�鿴�����е����ݣ�
 * pBuff		:	���廷����ָ��
 * nOffset		:	Ҫ�鿴���ݵ��ڻ����е���ʼƫ��
 * pDat			:	��ȡ���ݱ���Ļ����ַ
 * nLen			:	��ȡ���ݵĳ���
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
 * ��ջ��廷����
 * pBuff		:	���廷����ָ��
 */
void FlushBufferRing(PBUFFERRING pBuff)
{
	pBuff->nHead = pBuff->nTail;
	pBuff->bFull = 0;
}