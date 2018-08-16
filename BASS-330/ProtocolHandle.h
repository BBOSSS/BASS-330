#pragma once
#include "GlobalVariables.h"
#include "TinyFunc.h"

#define		PACKET_SIZE		128

class CProtocolHandle
{
private:

public:
	CProtocolHandle();
	~CProtocolHandle();

	BYTE SendPacket[PACKET_SIZE];	// 转换后的发送数据包
	BYTE RecvPacket[PACKET_SIZE];	// 从接收缓冲区获取的应答数据包
	BYTE ConvPacket[PACKET_SIZE];	// 转换后的接收数据包
	BYTE PureData  [PACKET_SIZE];	// 接收数据包中的数据部分	

	int SendLen;					// 转换后的发送数据包的长度
	int RecvLen;					// 从接收缓冲区获取的应答数据包的长度
	int ConvLen;					// 转换后的接收数据包的长度
	int PureLen;					// 接收数据包中的数据部分的长度

	int Package(BYTE Cmd, BYTE* SendData, int nDataLen);

	void Convert(BYTE* Packet, int &Length);		// 转换数据包中非头尾的 FF FE FD

	int UnConvert(BYTE* Packet, int Length);		// 从接收数据包还原非头尾的 FF FE FD

	BYTE GetVfy(BYTE* nData, int nDataLen);			// 模2加获取数据包的校验位
													
	bool isVaildPacket(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen);	// 判断数据包是否有效

	int GetPacket(BYTE* RecvBuffer, int RecvBufLen);				// 从接收缓冲区获取数据包 因为可能缓冲区还有数据包之外的脏数据

	int GetPureData(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen);	// 获取应答包的纯数据

	void Clear();	// 成员变量全置为0
};