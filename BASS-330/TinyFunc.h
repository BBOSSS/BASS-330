/*****************************************************************
** 文件名:小函数头文件  tinyFunc.h
** Copyright (c) 2018 高新兴科技集团股份有限公司物联产品部
 
** 创建人: 
** 日  期: 2018-08-02
** 描  述: 
** 版  本: V1.0

** 修改人:
** 日  期:
** 修改描述:
** 版  本: 
******************************************************************/

#ifndef __TINY_FUNC_H
#define __TINY_FUNC_H

#pragma once

#include<string>

CString ToString(int num);

std::string itos(int num);

int stoi(std::string str);

int ToInt(CString cstr);

int AscToHex(int a);

CString	IntToHex(unsigned char num);

CString  hexToStrNoBlank(unsigned char *tpHexData, int len);

void HexToAscii(BYTE &byAt, BYTE &chAsciiH, BYTE &chAsciiL);

//Template<typename T>
//T GetAbs(T num);

#endif 