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

	BYTE SendPacket[PACKET_SIZE];	// ת����ķ������ݰ�
	BYTE RecvPacket[PACKET_SIZE];	// �ӽ��ջ�������ȡ��Ӧ�����ݰ�
	BYTE ConvPacket[PACKET_SIZE];	// ת����Ľ������ݰ�
	BYTE PureData  [PACKET_SIZE];	// �������ݰ��е����ݲ���	

	int SendLen;					// ת����ķ������ݰ��ĳ���
	int RecvLen;					// �ӽ��ջ�������ȡ��Ӧ�����ݰ��ĳ���
	int ConvLen;					// ת����Ľ������ݰ��ĳ���
	int PureLen;					// �������ݰ��е����ݲ��ֵĳ���

	int Package(BYTE Cmd, BYTE* SendData, int nDataLen);

	void Convert(BYTE* Packet, int &Length);		// ת�����ݰ��з�ͷβ�� FF FE FD

	int UnConvert(BYTE* Packet, int Length);		// �ӽ������ݰ���ԭ��ͷβ�� FF FE FD

	BYTE GetVfy(BYTE* nData, int nDataLen);			// ģ2�ӻ�ȡ���ݰ���У��λ
													
	bool isVaildPacket(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen);	// �ж����ݰ��Ƿ���Ч

	int GetPacket(BYTE* RecvBuffer, int RecvBufLen);				// �ӽ��ջ�������ȡ���ݰ� ��Ϊ���ܻ������������ݰ�֮���������

	int GetPureData(BYTE Cmd, BYTE* RecvBuffer, int RecvBufLen);	// ��ȡӦ����Ĵ�����

	void Clear();	// ��Ա����ȫ��Ϊ0
};