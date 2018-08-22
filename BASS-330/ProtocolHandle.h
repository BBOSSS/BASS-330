#pragma once
#include "GlobalVariables.h"
#include "TinyFunc.h"

#define		PACKET_SIZE		128

struct ItemAttri	 // ͨ�����Խṹ��
{
    BYTE	No;		 // ͨ����
	BYTE	Type;	 // 0-�޲��   1-����   2-����   3-ֱ��   4-�¶�   5-ʪ��   6-����  7-ģ��   8-����   9-����  10-����
                     // 11-ˮ��    12-�Ž�  13-�ͻ�  14-�յ�  15-����  16-����  17-����  18-����  19-����  20-��չ
    int 	Uplimit; // ����	������ : 0����ʾ�͵�ƽ�澯,1����ʾ�ߵ�ƽ�澯
	int 	Dnlimit; // ����	������������������
	int 	Tol;	 // ����
	int 	Adj;	 // ����ֵ
	BYTE	Upout;	 // �������
	BYTE	Dnout;	 // �������
};

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

	void PacketItemAttriData(ItemAttri ItemValue, BYTE* SendData);	// ���ͨ�����Ե�����

	void Clear();	// ��Ա����ȫ��Ϊ0
};