#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

#pragma once
#include <vector>
#include <string>
using namespace std;

#define		PARAM_INIT		"test-330"
#define		CHANNEL_INIT	"channeltest1"
#define		LIST_INIT		"抚州移动"

class CBASS330Dlg;
class CParamConfig1;
class CParamConfig2;
class CParamConfig3;
class CParamConfig4;
class CParamConfig5;
class CParamConfig6;
class CParamConfig7;
class CProcessBar;

extern CBASS330Dlg	 *	pMainDlg;		// 主窗口全局指针
extern CParamConfig1 *	pSubDlg1;		// 标签子窗口指针1
extern CParamConfig2 *	pSubDlg2;		// 标签子窗口指针2
extern CParamConfig3 *	pSubDlg3;		// 标签子窗口指针3
extern CParamConfig4 *	pSubDlg4;		// 标签子窗口指针4
extern CParamConfig5 *	pSubDlg5;		// 标签子窗口指针5
extern CParamConfig6 *	pSubDlg6;		// 标签子窗口指针6
extern CParamConfig7 *	pSubDlg7;		// 标签子窗口指针7

extern vector<vector<string>> AllParams;

#endif 