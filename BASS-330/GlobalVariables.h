#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

#pragma once
#include <vector>
#include <string>
using namespace std;

#define		PARAM_INIT		"test-330"
#define		CHANNEL_INIT	"channeltest1"
#define		LIST_INIT		"�����ƶ�"

class CBASS330Dlg;
class CParamConfig1;
class CParamConfig2;
class CParamConfig3;
class CParamConfig4;
class CParamConfig5;
class CParamConfig6;
class CParamConfig7;
class CProcessBar;

extern CBASS330Dlg	 *	pMainDlg;		// ������ȫ��ָ��
extern CParamConfig1 *	pSubDlg1;		// ��ǩ�Ӵ���ָ��1
extern CParamConfig2 *	pSubDlg2;		// ��ǩ�Ӵ���ָ��2
extern CParamConfig3 *	pSubDlg3;		// ��ǩ�Ӵ���ָ��3
extern CParamConfig4 *	pSubDlg4;		// ��ǩ�Ӵ���ָ��4
extern CParamConfig5 *	pSubDlg5;		// ��ǩ�Ӵ���ָ��5
extern CParamConfig6 *	pSubDlg6;		// ��ǩ�Ӵ���ָ��6
extern CParamConfig7 *	pSubDlg7;		// ��ǩ�Ӵ���ָ��7

extern vector<vector<string>> AllParams;

#endif 