
// BASS-330.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBASS330App:
// �йش����ʵ�֣������ BASS-330.cpp
//

class CBASS330App : public CWinAppEx
{
public:
	CBASS330App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBASS330App theApp;