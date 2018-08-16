/******************************************************************
 ** 文件名 : RingBuffer.h
 ** 2015-2017 高新兴科技集团股份有限公司 Co.Ltd
 
 ** 创建人: 朱炽冲
 ** 日  期: 2013-02-25
 ** 描  述: 环形缓冲区功能的头文件
 ** 版  本: V1.0

 ** 修改人:
 ** 日  期:
 ** 修改描述:
 ** 版  本: 
******************************************************************/
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/*****************************************************************
* 包含头文件(如非特殊需要，H文件不建议包含其它H文件)
******************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @ingroup C_RingBuffer
 * 
 * @{ 
 */ 
 
/*****************************************************************
* 宏定义
******************************************************************/
#define    min(a,b)      (((a) < (b)) ? (a) : (b))
#define    max(a,b)		 (((a) > (b)) ? (a) : (b)) 

/*****************************************************************
* 结构、枚举定义
******************************************************************/
/** @brief 缓冲区数据结构*/		
struct RingBuffer
{
	unsigned char	 *pBuffer;			//< 缓冲区
	unsigned char	 *pHead;			//< 数据开始指针
	unsigned char	 *pTail;			//< 数据结束指针
	unsigned char	 *pEndbuffer;		//< 缓冲区尾部
	int 			 nBufferLen;		//< 缓冲区长度
	HANDLE			 lock;				//< 锁
};

/*****************************************************************
* 全局变量声明
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/
int InitRingBuffer(struct RingBuffer *pRingBuffer, int nBufferLen);
int DeInitRingBuffer(struct RingBuffer *pRingBuffer);
int RingBufferRead(unsigned char *pBuffer, int nLen,struct RingBuffer *pRingBuffer);
int RingBufferWrite(unsigned char *pBuffer, int nLen, struct RingBuffer *pRingBuffer);
int RingBufferReadMax(struct RingBuffer *pRingBuffer);
int RingBufferWriteMax(struct RingBuffer *pRingBuffer);
int RingBufferReadAdj(struct RingBuffer *pRingBuffer, int nSize);
int RingBufferWriteAdj(struct RingBuffer *pRingBuffer, int nSize);
int RingBufferFlush(struct RingBuffer *pRingBuffer);
int RingBufferLen(struct RingBuffer *pRingBuffer);
int RingBufferEmptyLen(struct RingBuffer *pRingBuffer);

/* @} C_RingBuffer */

#ifdef __cplusplus
}
#endif
 
#endif

