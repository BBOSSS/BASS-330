#include "stdafx.h"
#include "ProtocolHandle.h"
#include "BASS-330.h"
#include "BASS-330Dlg.h"

// 构造函数
CProtocolHandle::CProtocolHandle() 
{
	memset(SendPacket, 0, PACKET_SIZE);
	memset(RecvPacket, 0, PACKET_SIZE);
	memset(ConvPacket, 0, PACKET_SIZE);
	memset(PureData,   0, PACKET_SIZE);

	SendLen = 0;
	RecvLen = 0;
	ConvLen = 0;
	PureLen = 0;
}
// 析构函数
CProtocolHandle::~CProtocolHandle() {}

// 打包发送的指令和数据部分 源地址:0.0.0.0 目的地址设为广播地址:FF.FF.FF.FF
int CProtocolHandle::Package(BYTE Cmd, BYTE* SendData, int nDataLen)
{
	BYTE Buffer[PACKET_SIZE] = {0};

	Buffer[0] = 0xFF;		// 包头

	Buffer[1] = 0xFF;		// 目的地址DirAddr
	Buffer[2] = 0xFF;
	Buffer[3] = 0xFF;
	Buffer[4] = 0xFF;
	
	Buffer[5] = 0x00;		// 源地址SrcAddr
	Buffer[6] = 0x00;
	Buffer[7] = 0x00;
	Buffer[8] = 0x00;

	Buffer[9] = Cmd;		// 指令Cmd

	Buffer[10] = 0x00;		// 序号Sn

	Buffer[11] = nDataLen;	// 数据位长度

	int j = 12;				// 填充数据
	for(int i = 0; i < nDataLen; i++, j++)
	{
		Buffer[j] = SendData[i];
	}						// 模2加校验位
	Buffer[j] = GetVfy(Buffer, j-1);
	Buffer[j+1] = 0xFE;		// 停止位

	nDataLen = j + 2;
	memcpy(SendPacket, Buffer, nDataLen);
							// 转换数据包中非头尾的 FF FE FD
	Convert(SendPacket, nDataLen);

	SendLen = nDataLen;		// 转换后的数据包长度
	return nDataLen;
}

// 模2加获取数据包的校验位 包头 包尾 校验位不用参与异或
BYTE CProtocolHandle::GetVfy(BYTE* nData, int nDataLen)
{
	BYTE Vfy = 0;
	for(int i = 1; i <= nDataLen; i++)
    {
        Vfy ^= nData[i];
    }
    return Vfy;
}

// 转换数据包中非头尾的 FF FE FD
void CProtocolHandle::Convert(BYTE* Packet, int &Length)
{
	BYTE Buffer[PACKET_SIZE] = {0};
    Buffer[0] = 0xFF;
    int i, j;
    for(i = 1, j = 1; i < Length-1; i++)
	{
        switch(Packet[i])
        {
            case 0xFF:  Buffer[j++] = 0xFD;
                        Buffer[j++] = 0x00;
                        break;
            case 0xFE:  Buffer[j++] = 0xFD;
                        Buffer[j++] = 0x01;
                        break;
            case 0xFD:  Buffer[j++] = 0xFD;
                        Buffer[j++] = 0x02;
                        break;
            default:    Buffer[j++] = Packet[i];
                        break;
        }
	}
    Buffer[j] = 0xFE;
    Length = j + 1;
    memcpy(Packet, Buffer, Length);
}

// 从接收缓冲区获取数据包 因为缓冲区可能还有数据包之外的脏数据
int CProtocolHandle::GetPacket(BYTE* RecvBuffer, int RecvBufLen)
{
	BYTE Buffer[PACKET_SIZE] = {0};
	int start = 0, end = 0;
	for(int i = 0; i < RecvBufLen; i++) 
	{
		if(RecvBuffer[i] == 0xFF)
		{
			start = i;
			break;
		}
		if(i > RecvBufLen-14)return FALSE;	// 没找到包头
	}
	for(int i = start, j = 0; i < RecvBufLen; i++, j++)
	{
		Buffer[j] = RecvBuffer[i];
		if(RecvBuffer[i] == 0xFE)
		{
			end = i;
			break;
		}
	}
	if(end == 0)  return FALSE;				// 没找到包尾

	int PacketLen = end - start + 1;
	memcpy(RecvPacket, Buffer, PacketLen);

	RecvLen = PacketLen;
	return PacketLen;
}

// 从接收数据包还原非头尾的 FF FE FD
int CProtocolHandle::UnConvert(BYTE* Packet, int Length)
{
	BYTE Buffer[PACKET_SIZE] = {0};
	int len = 0;

	for(int i = 0; i < Length; i++)
	{
		if(0xFD == Packet[i])
		{
			switch(Packet[++i])
			{
				case 0x00: Buffer[len++] = 0xFF; break;
				case 0x01: Buffer[len++] = 0xFE; break;
				case 0x02: Buffer[len++] = 0xFD; break;
				default: return FALSE;
			}
		}
		else
		{
			Buffer[len++] = Packet[i];
		}
	}
	memcpy(ConvPacket, Buffer, len);

	ConvLen = len;
	return len;
}

// 判断数据包是否有效
bool CProtocolHandle::isVaildPacket(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen)
{
	if(FALSE == GetPacket(RecvBuffer, RecvBufLen))			// 先获取数据包
		return false;
	int len = UnConvert(RecvPacket, RecvLen);				// 从接收数据包还原非头尾的 FF FE FD

	if(ConvPacket[0] != 0xFF || ConvPacket[len-1] != 0xFE)	// 判断包头包尾
		return false;
	if(ConvPacket[len-2] != GetVfy(ConvPacket, len-3))		// 判断校验位 减去头尾和校验位本身
		return false;
	if(ConvPacket[9] != 0 || ConvPacket[10] != Cmd)			// 判断Ret位和Sn位
		return false;

	return true;
}

// 获取应答包的纯数据（如果有）
int CProtocolHandle::GetPureData(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen)
{
	if( !isVaildPacket(Cmd, RecvBuffer, RecvBufLen) )
		return FALSE;

	BYTE Buffer[PACKET_SIZE] = {0};
	int length = ConvPacket[11];

	for(int i = 0, j = 12; j < length+12; i++, j++)
	{
		Buffer[i] = ConvPacket[j];
	}
	memcpy(PureData, Buffer, length);

	PureLen = length;
	return length;
}

// 打包通道属性的数据
void CProtocolHandle::PacketItemAttriData(ItemAttri ItemValue, BYTE* SendData)
{
    SendData[0]  = ItemValue.No;
    SendData[1]  = ItemValue.Type;
    SendData[2]  = ItemValue.Uplimit >> 8;
    SendData[3]  = ItemValue.Uplimit & 0xFF;
    SendData[4]  = 0x00;
    SendData[5]  = 0x00;
    SendData[6]  = ItemValue.Dnlimit >> 8;
    SendData[7]  = ItemValue.Dnlimit & 0xFF;
    SendData[8]  = 0x00;
    SendData[9]  = 0x00;
    SendData[10] = 0x00;
    SendData[11] = (BYTE)ItemValue.Tol;
    SendData[12] = 0x00;
    SendData[13] = 0x00;
    SendData[14] = 0x00;
    SendData[15] = (BYTE)ItemValue.Adj;
    SendData[16] = 0x00;
    SendData[17] = 0x00;
    SendData[18] = ItemValue.Upout;
    SendData[19] = ItemValue.Dnout;
}

// 成员变量全置为0
void CProtocolHandle::Clear()
{
	memset(SendPacket, 0, PACKET_SIZE);
	memset(RecvPacket, 0, PACKET_SIZE);
	memset(ConvPacket, 0, PACKET_SIZE);
	memset(PureData,   0, PACKET_SIZE);

	SendLen = 0;
	RecvLen = 0;
	ConvLen = 0;
	PureLen = 0;
}

UINT16 CProtocolHandle::GetVfy2M(BYTE* nData, int nDataLen)
{
	UINT16 wVfy = 0x00;
	for(int i = 1; i <= nDataLen; i++)
	{
		wVfy += nData[i];
	}
    wVfy = ~wVfy;
    wVfy = wVfy + 1;
    return wVfy;
}

UINT16 CProtocolHandle::GetCodeLen(int iLen)	// 长度及长度校验
{
	BYTE byLCHK = ((iLen&0xF00) >> 8) + ((iLen&0x0F0) >> 4) + (iLen&0x00F);
    byLCHK &= 0x0F;
    byLCHK =  ~byLCHK;
    byLCHK &= 0x0F;
    byLCHK++;
    WORD wLen = byLCHK;
    wLen = (wLen << 12) + iLen;
    return wLen;
}

int CProtocolHandle::Package2M(BYTE Ver, BYTE Addr, BYTE CID1, BYTE CID2, BYTE* SendData, int nDataLen, BYTE* Packet)
{
	BYTE chASCIIH, chASCIIL;

	// 起始位SOI
	Packet[0] = 0x7E;

	// 版本号VER
    HexToAscii(Ver, chASCIIH, chASCIIL);
    Packet[1] = chASCIIH;
    Packet[2] = chASCIIL;

	// 地址码ADR
    HexToAscii(Addr, chASCIIH, chASCIIL);
    Packet[3] = chASCIIH;
    Packet[4] = chASCIIL;

	// 标识码CID1
    HexToAscii(CID1, chASCIIH, chASCIIL);
    Packet[5] = chASCIIH;
    Packet[6] = chASCIIL;

	// 标识码CID2
    HexToAscii(CID2, chASCIIH, chASCIIL);
    Packet[7] = chASCIIH;
    Packet[8] = chASCIIL;

	// 长度LENGTH
    UINT16 wLen = GetCodeLen(nDataLen*2);
    HexToAscii(*((BYTE*)(&wLen)+1), chASCIIH, chASCIIL);
    Packet[9]  = chASCIIH;
    Packet[10] = chASCIIL;
    HexToAscii(*((BYTE*)(&wLen)), chASCIIH, chASCIIL);
	Packet[11]  = chASCIIH;
    Packet[12] = chASCIIL;

	// 数据
	int j = 13;
    for(int i = 0; i < nDataLen; i++)
	{
		HexToAscii(SendData[i], chASCIIH, chASCIIL);
		Packet[j++] = chASCIIH;
		Packet[j++] = chASCIIL;
	}

	// 校验
    WORD wVfy = GetVfy2M(Packet, j-1);
    HexToAscii(*((BYTE*)(&wVfy)+1), chASCIIH, chASCIIL);
    Packet[j++] = chASCIIH;
    Packet[j++] = chASCIIL;
    HexToAscii(*((BYTE*)(&wVfy)), chASCIIH, chASCIIL);
    Packet[j++] = chASCIIH;
    Packet[j++] = chASCIIL;

	// 包尾
	Packet[j++] = 0x0D;
	return j;
}

// 判断2M版本响应包是否有效
bool CProtocolHandle::isVaildAck2M(BYTE* RecvBuff, int BufLen)
{
	if(RecvBuff[0] != 0x7E || RecvBuff[BufLen-1] != 0x0D)
		return false;
	if(RecvBuff[7] != 0x30 || RecvBuff[8] != 0x30)	// RTN BYTE:00H -- ASCII:0x30 0x30
		return false;
	return true;
}