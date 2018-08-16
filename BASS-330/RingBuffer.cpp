/******************************************************************
 ** 文件名 : RingBuffer.c
 ** 2015-2017 高新兴科技集团股份有限公司 Co.Ltd
 
 ** 创建人: 朱炽冲
 ** 日  期: 2013-02-25
 ** 描  述: 实现环形缓冲区功能，从头部写，从尾部读,支持一个线程读，一个线程写
            如果要支持多个线程写，必须由外部用户控制。
 ** 版  本: V1.0

 ** 修改人:
 ** 日  期:
 ** 修改描述:
 ** 版  本: 
******************************************************************/

/*****************************************************************
* 包含头文件
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
 * @defgroup C_RingBuffer 环形缓冲
 * 
 * @brief \n
 * \n
 * @{ 
 */ 
 
/*****************************************************************
* 宏定义(仅在当前C文件使用的宏定义写在当前C文件中，否则需写在H文件中)
******************************************************************/

/*****************************************************************
* 结构定义(仅在当前C文件使用的结构体写在当前C文件中，否则需写在H文件中)
******************************************************************/

/*****************************************************************
* 全局变量定义
******************************************************************/

/*****************************************************************
* 静态变量定义
******************************************************************/

/*****************************************************************
* 外部变量声明（如果全局变量没有在其它的H文件声明，引用时需在此处声明，
*如果已在其它H文件声明，则只需包含此H文件即可）
******************************************************************/

/*****************************************************************
* 静态变量定义
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/

/*****************************************************************
* 函数定义
*注意，编写函数需首先定义所有的局部变量等，不允许在
*函数的中间出现新的变量的定义。
******************************************************************/
/******************************************************************/
/**
* 清空缓冲区\n 

* @param[in/out] pRingBuffer 缓冲区结构指针
* @return 返回操作结果
*   - 1   成功
*   - -1  失败

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
     /*参数合法性判断*/
     if( NULL == pRingBuffer )
     {
         return -1;
     }
     /*加锁*/
     WaitForSingleObject(pRingBuffer->lock, INFINITE);

     pRingBuffer->pHead = pRingBuffer->pBuffer;
     pRingBuffer->pTail = pRingBuffer->pBuffer;
     
     /*解锁*/
     ReleaseMutex(pRingBuffer->lock);

     return 1;
}

/******************************************************************/
/**
* 获取缓冲区数据长度\n 

* @param[in] pRingBuffer 缓冲区结构指针

* @return
*  - 非-1 返回数据长度
*  - -1   失败

* @author:        朱炽冲
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
* 获取缓冲区数据长度\n 

* @param[in] pRingBuffer 缓冲区结构指针

* @return
*  - 非-1 返回数据长度
*  - -1   失败

* @author:        朱炽冲
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
* 获取最大可读长度\n 

* @param[in] pRingBuffer  Ringbuf指针

* @return
*  - 非-1 返回实际可读的最大数据长度
*  - -1   失败

* @author:        朱炽冲
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
* 获取最大可写长度\n 

* @param[in] pRingBuffer  Ringbuf指针

* @return
*  - 非-1 返回实际可写的最大数据长度
*  - -1   失败

* @author:        朱炽冲
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
* 读环形缓冲区数据\n 

* @param[out] pBuffer      数据接收缓冲
* @param[in]  nLen         数据接收缓冲长度
* @param[in]  pRingBuffer  环形缓冲数据

* @return
*  - 非-1 返回成功读取的数据长度
*  - -1   失败

* @author:        朱炽冲
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

     /*参数合法性判断*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }
	
     /*循环读取缓冲区*/
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

          /*更新尾部*/
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
* 环形缓冲区写，只支持一个线程写\n 

* @param[in]  pBuffer      要写入环形缓冲区的数据
* @param[in]  nLen         要写入数据的字节数
* @param[in]  pRingBuffer  环形缓冲数据

* @return
*  - 非-1 返回成功写入的数据长度
*  - -1   失败

* @author:        朱炽冲
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
 
     /*参数合法性判断*/
     if( NULL == pBuffer || NULL == pRingBuffer )
	 {
		 return -1;
	 }

     /*写缓冲区数据*/
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
        /*更新头部*/
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
* 调整读位置\n 

* @param[in]  pRingBuffer  环形缓冲数据
* @param[in]  nSize        已读长度

* @return
*  - 1   成功
*  - -1  失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferReadAdj(struct RingBuffer *pRingBuffer, int nSize)
{

    /*合法性判断*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }
    /*调整读位置*/
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
* 调整写位置\n 

* @param[in]  pRingBuffer  环形缓冲数据
* @param[in]  nSize        已写长度

* @return
*  - 0   成功
*  - -1  失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int RingBufferWriteAdj(struct RingBuffer *pRingBuffer, int nSize)
{
    /*合法性判断*/
    if(NULL == pRingBuffer)
    {
        return -1;
    }

    /*调整写位置*/
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
* 初始化环形缓冲区\n 

* @param[in]  pRingBuffer  环形缓冲数据
* @param[in]  nBufferLen   数据缓冲区长度

* @return
*  - 1  返回成功读取的数据长度
*  - -1 失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int InitRingBuffer(struct RingBuffer *pRingBuffer, int nBufferLen)
{
     /*参数合法性判断*/
     if(NULL == pRingBuffer)
     {
          return (-1);
     }

     /*动态开辟缓冲区*/
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
* 释放环形缓冲区,调用该函数时，必须确保没有在其它线程使用该缓冲\n
* 区资源通常在系统结束所有线程后调用。\n 

* @param[in]  pRingBuffer  环形缓冲数据

* @return
*  - 1  返回成功读取的数据长度
*  - -1 失败

* @author:        朱炽冲
* @date           2013-02-25

* @par Modification History
* @par Author:
* @par Date:
* @par Description:
*/
/******************************************************************/
int DeInitRingBuffer(struct RingBuffer *pRingBuffer)
{

     /*参数合法性判断*/
     if(NULL == pRingBuffer)
     {
          return (-1);
     }

     /*清空缓冲区数据*/
     RingBufferFlush(pRingBuffer);

	 /*释放动态开辟缓冲区*/
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

