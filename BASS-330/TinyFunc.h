/*****************************************************************
** �ļ���:С����ͷ�ļ�  tinyFunc.h
** Copyright (c) 2018 �����˿Ƽ����Źɷ����޹�˾������Ʒ��
 
** ������: 
** ��  ��: 2018-08-02
** ��  ��: 
** ��  ��: V1.0

** �޸���:
** ��  ��:
** �޸�����:
** ��  ��: 
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