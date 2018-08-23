#include "stdafx.h"
#include "ProtocolHandle.h"
#include "BASS-330.h"
#include "BASS-330Dlg.h"

// ���캯��
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
// ��������
CProtocolHandle::~CProtocolHandle() {}

// ������͵�ָ������ݲ��� Դ��ַ:0.0.0.0 Ŀ�ĵ�ַ��Ϊ�㲥��ַ:FF.FF.FF.FF
int CProtocolHandle::Package(BYTE Cmd, BYTE* SendData, int nDataLen)
{
	BYTE Buffer[PACKET_SIZE] = {0};

	Buffer[0] = 0xFF;		// ��ͷ

	Buffer[1] = 0xFF;		// Ŀ�ĵ�ַDirAddr
	Buffer[2] = 0xFF;
	Buffer[3] = 0xFF;
	Buffer[4] = 0xFF;
	
	Buffer[5] = 0x00;		// Դ��ַSrcAddr
	Buffer[6] = 0x00;
	Buffer[7] = 0x00;
	Buffer[8] = 0x00;

	Buffer[9] = Cmd;		// ָ��Cmd

	Buffer[10] = 0x00;		// ���Sn

	Buffer[11] = nDataLen;	// ����λ����

	int j = 12;				// �������
	for(int i = 0; i < nDataLen; i++, j++)
	{
		Buffer[j] = SendData[i];
	}						// ģ2��У��λ
	Buffer[j] = GetVfy(Buffer, j-1);
	Buffer[j+1] = 0xFE;		// ֹͣλ

	nDataLen = j + 2;
	memcpy(SendPacket, Buffer, nDataLen);
							// ת�����ݰ��з�ͷβ�� FF FE FD
	Convert(SendPacket, nDataLen);

	SendLen = nDataLen;		// ת��������ݰ�����
	return nDataLen;
}

// ģ2�ӻ�ȡ���ݰ���У��λ ��ͷ ��β У��λ���ò������
BYTE CProtocolHandle::GetVfy(BYTE* nData, int nDataLen)
{
	BYTE Vfy = 0;
	for(int i = 1; i <= nDataLen; i++)
    {
        Vfy ^= nData[i];
    }
    return Vfy;
}

// ת�����ݰ��з�ͷβ�� FF FE FD
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

// �ӽ��ջ�������ȡ���ݰ� ��Ϊ���������ܻ������ݰ�֮���������
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
		if(i > RecvBufLen-14)return FALSE;	// û�ҵ���ͷ
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
	if(end == 0)  return FALSE;				// û�ҵ���β

	int PacketLen = end - start + 1;
	memcpy(RecvPacket, Buffer, PacketLen);

	RecvLen = PacketLen;
	return PacketLen;
}

// �ӽ������ݰ���ԭ��ͷβ�� FF FE FD
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

// �ж����ݰ��Ƿ���Ч
bool CProtocolHandle::isVaildPacket(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen)
{
	if(FALSE == GetPacket(RecvBuffer, RecvBufLen))			// �Ȼ�ȡ���ݰ�
		return false;
	int len = UnConvert(RecvPacket, RecvLen);				// �ӽ������ݰ���ԭ��ͷβ�� FF FE FD

	if(ConvPacket[0] != 0xFF || ConvPacket[len-1] != 0xFE)	// �жϰ�ͷ��β
		return false;
	if(ConvPacket[len-2] != GetVfy(ConvPacket, len-3))		// �ж�У��λ ��ȥͷβ��У��λ����
		return false;
	if(ConvPacket[9] != 0 || ConvPacket[10] != Cmd)			// �ж�Retλ��Snλ
		return false;

	return true;
}

// ��ȡӦ����Ĵ����ݣ�����У�
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

// ���ͨ�����Ե�����
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

// ��Ա����ȫ��Ϊ0
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

UINT16 CProtocolHandle::GetCodeLen(int iLen)	// ���ȼ�����У��
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

	// ��ʼλSOI
	Packet[0] = 0x7E;

	// �汾��VER
    HexToAscii(Ver, chASCIIH, chASCIIL);
    Packet[1] = chASCIIH;
    Packet[2] = chASCIIL;

	// ��ַ��ADR
    HexToAscii(Addr, chASCIIH, chASCIIL);
    Packet[3] = chASCIIH;
    Packet[4] = chASCIIL;

	// ��ʶ��CID1
    HexToAscii(CID1, chASCIIH, chASCIIL);
    Packet[5] = chASCIIH;
    Packet[6] = chASCIIL;

	// ��ʶ��CID2
    HexToAscii(CID2, chASCIIH, chASCIIL);
    Packet[7] = chASCIIH;
    Packet[8] = chASCIIL;

	// ����LENGTH
    UINT16 wLen = GetCodeLen(nDataLen*2);
    HexToAscii(*((BYTE*)(&wLen)+1), chASCIIH, chASCIIL);
    Packet[9]  = chASCIIH;
    Packet[10] = chASCIIL;
    HexToAscii(*((BYTE*)(&wLen)), chASCIIH, chASCIIL);
	Packet[11]  = chASCIIH;
    Packet[12] = chASCIIL;

	// ����
	int j = 13;
    for(int i = 0; i < nDataLen; i++)
	{
		HexToAscii(SendData[i], chASCIIH, chASCIIL);
		Packet[j++] = chASCIIH;
		Packet[j++] = chASCIIL;
	}

	// У��
    WORD wVfy = GetVfy2M(Packet, j-1);
    HexToAscii(*((BYTE*)(&wVfy)+1), chASCIIH, chASCIIL);
    Packet[j++] = chASCIIH;
    Packet[j++] = chASCIIL;
    HexToAscii(*((BYTE*)(&wVfy)), chASCIIH, chASCIIL);
    Packet[j++] = chASCIIH;
    Packet[j++] = chASCIIL;

	// ��β
	Packet[j++] = 0x0D;
	return j;
}

// �ж�2M�汾��Ӧ���Ƿ���Ч
bool CProtocolHandle::isVaildAck2M(BYTE* RecvBuff, int BufLen)
{
	if(RecvBuff[0] != 0x7E || RecvBuff[BufLen-1] != 0x0D)
		return false;
	if(RecvBuff[7] != 0x30 || RecvBuff[8] != 0x30)	// RTN BYTE:00H -- ASCII:0x30 0x30
		return false;
	return true;
}