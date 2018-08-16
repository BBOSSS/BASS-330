/******************************************************************
 ** �ļ��� : RingBuffer.c
 ** 2015-2017 �����˿Ƽ����Źɷ����޹�˾ Co.Ltd
 
 ** ������: ����
 ** ��  ��: 2013-02-25
 ** ��  ��: ʵ�ֻ��λ��������ܣ���ͷ��д����β����,֧��һ���̶߳���һ���߳�д
            ���Ҫ֧�ֶ���߳�д���������ⲿ�û����ơ�
 ** ��  ��: V1.0

 ** �޸���:
 ** ��  ��:
 ** �޸�����:
 ** ��  ��: 
******************************************************************/

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include "StdAfx.h"
#include "RingBuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @addtogroup TOP
 * @{ 
 */ 
 
/** 
 * @defgroup C_RingBuffer ���λ���
 * 
 * @brief \n
 * \n
 * @{ 
 */ 
 
/*****************************************************************
* �궨��(���ڵ�ǰC�ļ�ʹ�õĺ궨��д�ڵ�ǰC�ļ��У�������д��H�ļ���)
******************************************************************/

/*****************************************************************
* �ṹ����(���ڵ�ǰC�ļ�ʹ�õĽṹ��д�ڵ�ǰC�ļ��У�������д��H�ļ���)
******************************************************************/

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ��̬��������
******************************************************************/

/*****************************************************************
* �ⲿ�������������ȫ�ֱ���û����������H�ļ�����������ʱ���ڴ˴�������
*�����������H�ļ���������ֻ�������H�ļ����ɣ�
******************************************************************/

/*****************************************************************
* ��̬��������
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/

/*****************************************************************
* ��������
*ע�⣬��д���������ȶ������еľֲ������ȣ���������
*�������м�����µı����Ķ��塣
******************************************************************/
/******************************************************************/
/**
* ��ջ�����\n 

* @param[in/out] pRingBuffer �������ṹָ��
* @return ���ز������
*   - 1   �ɹ�
*   - -1  ʧ��

* @author:         
* @date           

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferFlush(struct RingBuffer *pRingBuffer)
{
     /*�����Ϸ����ж�*/
     if( NULL == pRingBuffer )
     {
         return -1;
     }
     /*����*/
     WaitForSingleObject(pRingBuffer->lock, INFINITE);

     pRingBuffer->pHead = pRingBuffer->pBuffer;
     pRingBuffer->pTail = pRingBuffer->pBuffer;
     
     /*����*/
     ReleaseMutex(pRingBuffer->lock);

     return 1;
}

/******************************************************************/
/**
* ��ȡ���������ݳ���\n 

* @param[in] pRingBuffer �������ṹָ��

* @return
*  - ��-1 �������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferLen(struct RingBuffer *pRingBuffer)
{
    int nDataLen;

    if( NULL == pRingBuffer )
    {
        return -1;
    }

    WaitForSingleObject(pRingBuffer->lock, INFINITE);
    nDataLen = (pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));
    ReleaseMutex(pRingBuffer->lock);

    return nDataLen;
}

/******************************************************************/
/**
* ��ȡ���������ݳ���\n 

* @param[in] pRingBuffer �������ṹָ��

* @return
*  - ��-1 �������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferEmptyLen(struct RingBuffer *pRingBuffer)
{
    int nDataLen;

    if( NULL == pRingBuffer )
    {
        return -1;
    }

    WaitForSingleObject(pRingBuffer->lock, INFINITE);
    nDataLen = (pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->nBufferLen  - (pRingBuffer->pHead - pRingBuffer->pTail))
           :(pRingBuffer->pTail - pRingBuffer->pHead);
    ReleaseMutex(pRingBuffer->lock);

    return nDataLen;

}

/******************************************************************/
/**
* ��ȡ���ɶ�����\n 

* @param[in] pRingBuffer  Ringbufָ��

* @return
*  - ��-1 ����ʵ�ʿɶ���������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadMax(struct RingBuffer *pRingBuffer)
{
    int nReadMax;
    int nDataLen;
    int nLineLen;

    if(NULL == pRingBuffer)
    {
        return -1;
    }

    WaitForSingleObject(pRingBuffer->lock, INFINITE);
    nDataLen = ( pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));

	nLineLen = pRingBuffer->pEndbuffer - pRingBuffer->pTail;

	nReadMax = min(nLineLen, nDataLen);

    ReleaseMutex(pRingBuffer->lock);

    return nReadMax;
}

/******************************************************************/
/**
* ��ȡ����д����\n 

* @param[in] pRingBuffer  Ringbufָ��

* @return
*  - ��-1 ����ʵ�ʿ�д��������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteMax(struct RingBuffer *pRingBuffer)
{
    int nWriteMax;
    int nWriteLen;
    int nLineLen;
    int nDataLen;

    if(NULL == pRingBuffer)
    {
        return -1;
    }
    WaitForSingleObject(pRingBuffer->lock, INFINITE);
    nDataLen = ( pRingBuffer->pHead >= pRingBuffer->pTail) ? (pRingBuffer->pHead - pRingBuffer->pTail)
           :(pRingBuffer->nBufferLen + (pRingBuffer->pHead - pRingBuffer->pTail));

	nWriteLen = pRingBuffer->nBufferLen - nDataLen - 1;

	nLineLen = pRingBuffer->pEndbuffer - pRingBuffer->pHead;

    nWriteMax = min(nWriteLen, nLineLen);
    ReleaseMutex(pRingBuffer->lock);

	return nWriteMax;
}

/******************************************************************/
/**
* �����λ���������\n 

* @param[out] pBuffer      ���ݽ��ջ���
* @param[in]  nLen         ���ݽ��ջ��峤��
* @param[in]  pRingBuffer  ���λ�������

* @return
*  - ��-1 ���سɹ���ȡ�����ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferRead(unsigned char *pBuffer, int nLen,struct RingBuffer *pRingBuffer)
{
	 int nReadByte;
     int nReadLen;
     unsigned char *pData;

     /*�����Ϸ����ж�*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }
	
     /*ѭ����ȡ������*/
	 nReadByte = 0;
     pData = pBuffer;

	 while (nLen > 0) 
     {
		  nReadLen = RingBufferReadMax(pRingBuffer);
		  nReadLen = min(nReadLen, nLen);
		  if (nReadLen <= 0) 
          {
			  break;
		  }

		  memcpy(pData, pRingBuffer->pTail, nReadLen);
		  pData += nReadLen;
		  nLen -= nReadLen;
		  nReadByte += nReadLen;

          /*����β��*/
          WaitForSingleObject(pRingBuffer->lock, INFINITE);
          pRingBuffer->pTail += nReadLen;
		  if(pRingBuffer->pTail >= pRingBuffer->pEndbuffer)
          {
			  pRingBuffer->pTail  = pRingBuffer->pBuffer;
		  }
          ReleaseMutex(pRingBuffer->lock);
	 }
	 return nReadByte;
}

/******************************************************************/
/**
* ���λ�����д��ֻ֧��һ���߳�д\n 

* @param[in]  pBuffer      Ҫд�뻷�λ�����������
* @param[in]  nLen         Ҫд�����ݵ��ֽ���
* @param[in]  pRingBuffer  ���λ�������

* @return
*  - ��-1 ���سɹ�д������ݳ���
*  - -1   ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWrite(unsigned char *pBuffer, int nLen, struct RingBuffer *pRingBuffer)
{
	 int nWriteByte;
     int nWriteLen;
     int nDataLen;
     unsigned char *pData;
 
     /*�����Ϸ����ж�*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }

     /*д����������*/
	 nWriteByte = 0;
     pData = pBuffer;

     nDataLen = RingBufferLen(pRingBuffer);
     if(0 == nDataLen)
     {
          RingBufferFlush(pRingBuffer);
     }

	 while (nLen > 0) 
     {
		nWriteLen = RingBufferWriteMax(pRingBuffer);
		nWriteLen = min(nWriteLen, nLen);

		if (nWriteLen <= 0) 
        {
			return nWriteByte;
		}

		memcpy(pRingBuffer->pHead,pData, nWriteLen);
		pData += nWriteLen;
		nLen -= nWriteLen;
		nWriteByte += nWriteLen;
        /*����ͷ��*/
        WaitForSingleObject(pRingBuffer->lock, INFINITE);
        pRingBuffer->pHead += nWriteLen;
		if (pRingBuffer->pHead >= pRingBuffer->pEndbuffer) 
        {
			 pRingBuffer->pHead = pRingBuffer->pBuffer;
		}
        ReleaseMutex(pRingBuffer->lock);
	}

	return nWriteByte;

}

/******************************************************************/
/**
* ������λ��\n 

* @param[in]  pRingBuffer  ���λ�������
* @param[in]  nSize        �Ѷ�����

* @return
*  - 1   �ɹ�
*  - -1  ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadAdj(struct RingBuffer *pRingBuffer, int nSize)
{

    /*�Ϸ����ж�*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }
    /*������λ��*/
    WaitForSingleObject(pRingBuffer->lock, INFINITE);
	pRingBuffer->pTail += nSize;
	if(pRingBuffer->pTail >= pRingBuffer->pEndbuffer) 
    {
		pRingBuffer->pTail -= pRingBuffer->nBufferLen;
	}
    ReleaseMutex(pRingBuffer->lock);
    return 1;
}

/******************************************************************/
/**
* ����дλ��\n 

* @param[in]  pRingBuffer  ���λ�������
* @param[in]  nSize        ��д����

* @return
*  - 0   �ɹ�
*  - -1  ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteAdj(struct RingBuffer *pRingBuffer, int nSize)
{
    /*�Ϸ����ж�*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }

    /*����дλ��*/
    WaitForSingleObject(pRingBuffer->lock, INFINITE);
    pRingBuffer->pHead += nSize;
	if ( pRingBuffer->pHead >= pRingBuffer->pEndbuffer)
    {
		pRingBuffer->pHead -= pRingBuffer->nBufferLen;
	}
	ReleaseMutex(pRingBuffer->lock);
    return 1;
}

/******************************************************************/
/**
* ��ʼ�����λ�����\n 

* @param[in]  pRingBuffer  ���λ�������
* @param[in]  nBufferLen   ���ݻ���������

* @return
*  - 1  ���سɹ���ȡ�����ݳ���
*  - -1 ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int InitRingBuffer(struct RingBuffer *pRingBuffer, int nBufferLen)
{
     /*�����Ϸ����ж�*/
     if(NULL == pRingBuffer)
     {
          return (-1);
     }

     /*��̬���ٻ�����*/
	 pRingBuffer->pBuffer = (unsigned char *)malloc(nBufferLen); 
     if(NULL == pRingBuffer->pBuffer)
	 {
          return (-1);
	 }
	 pRingBuffer->nBufferLen = nBufferLen;
     pRingBuffer->pHead = pRingBuffer->pBuffer;
     pRingBuffer->pTail = pRingBuffer->pBuffer;
     pRingBuffer->pEndbuffer = &pRingBuffer->pBuffer[nBufferLen];

     pRingBuffer->lock = CreateMutex(NULL, FALSE, NULL);

	 return (1);

}

/******************************************************************/
/**
* �ͷŻ��λ�����,���øú���ʱ������ȷ��û���������߳�ʹ�øû���\n
* ����Դͨ����ϵͳ���������̺߳���á�\n 

* @param[in]  pRingBuffer  ���λ�������

* @return
*  - 1  ���سɹ���ȡ�����ݳ���
*  - -1 ʧ��

* @author:        ����
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int DeInitRingBuffer(struct RingBuffer *pRingBuffer)
{

     /*�����Ϸ����ж�*/
     if(NULL == pRingBuffer)
     {
          return (-1);
     }

     /*��ջ���������*/
     RingBufferFlush(pRingBuffer);

	 /*�ͷŶ�̬���ٻ�����*/
	 if(pRingBuffer->pBuffer != NULL)
	 {
		  free(pRingBuffer->pBuffer);
		  pRingBuffer->pBuffer = NULL;

	 }

	 CloseHandle(pRingBuffer->lock);
	 pRingBuffer->lock = NULL;
	 return(1);
}

/* @} C_RingBuffer */ 
/* @} TOP */

#ifdef __cplusplus
}
#endif

