/*****************************************************************
** 文件名:全局变量头文件  GlobalVariables.h
** Copyright (c) 2018 高新兴科技集团股份有限公司物联产品部
 
** 创建人: 
** 日  期: 2018-08-02
** 描  述: 用于不同子窗口之间相互通信
** 版  本: V1.0

** 修改人:
** 日  期:
** 修改描述:
** 版  本: 
******************************************************************/

#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

#pragma once

// #include "BASS-330.h"
// #include "BASS-330Dlg.h"
// #include "ParamConfig1.h"
// #include "ParamConfig2.h"
// #include "ParamConfig3.h"
// #include "ParamConfig4.h"
// #include "ParamConfig5.h"
// #include "ParamConfig6.h"
// #include "ParamConfig7.h"

class CBASS330Dlg;
class CParamConfig1;
class CParamConfig2;
class CParamConfig3;
class CParamConfig4;
class CParamConfig5;
class CParamConfig6;
class CParamConfig7;

extern CBASS330Dlg	 *	pMainDlg;		// 主窗口全局指针
extern CParamConfig1 *	pSubDlg1;		// 标签子窗口指针1
extern CParamConfig2 *	pSubDlg2;		// 标签子窗口指针2
extern CParamConfig3 *	pSubDlg3;		// 标签子窗口指针3
extern CParamConfig4 *	pSubDlg4;		// 标签子窗口指针4
extern CParamConfig5 *	pSubDlg5;		// 标签子窗口指针5
extern CParamConfig6 *	pSubDlg6;		// 标签子窗口指针6
extern CParamConfig7 *	pSubDlg7;		// 标签子窗口指针7

#endif 