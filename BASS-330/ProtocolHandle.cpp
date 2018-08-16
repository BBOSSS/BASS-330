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