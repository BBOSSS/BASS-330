#pragma once
#include "GlobalVariables.h"
#include "TinyFunc.h"

#define		PACKET_SIZE		128

struct ItemAttri	 // 通道属性结构体
{
    BYTE	No;		 // 通道号
	BYTE	Type;	 // 0-无测点   1-三相   2-交流   3-直流   4-温度   5-湿度   6-电流  7-模拟   8-火情   9-烟雾  10-盗情
                     // 11-水浸    12-门禁  13-油机  14-空调  15-红外  16-整流  17-数字  18-其它  19-机器  20-扩展
    int 	Uplimit; // 上限	开关量 : 0，表示低电平告警,1：表示高电平告警
	int 	Dnlimit; // 下限	开关量的下限无意义
	int 	Tol;	 // 公差
	int 	Adj;	 // 调较值
	BYTE	Upout;	 // 上限输出
	BYTE	Dnout;	 // 下限输出
};

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

	void PacketItemAttriData(ItemAttri ItemValue, BYTE* SendData);	// 打包通道属性的数据

	void Clear();	// 成员变量全置为0
};