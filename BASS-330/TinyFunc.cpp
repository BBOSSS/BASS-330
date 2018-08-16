/*********************************************************
 ** 文件名：小函数源文件 tinyFunc.c
 ** Copyright (c) 2018 高新兴科技集团物联产品部
 ** 创建人：xieruibin
 ** 日  期：2018/08/02
 ** 描  述：
 ** 版  本：V1.0
 
 ** 修改人：xxx
 ** 日  期：
 ** 描  述：
 ** 版  本：
*********************************************************/

#include "stdafx.h"
#include "TinyFunc.h"

/**
 * @brief		整型数转为字符串函数
 * @param[in]	num		整型数
 * @param[out]	null     
 * @return		整型数对应的字符串
 * @date:		2018/08/02
 * @par Description: 
 * @note 
 * @see
 */
CString ToString(int num)
{
	CString res;
	if(0 == num)
	{
		res += "0";
		return res;
	}
	while(0 != num)
	{
		res = (char)(num%10 + '0') + res;
		num /= 10;
	}
	return res;
}

/**
 * @brief		字符串转为整型数函数
 * @param[in]	cstr	字符串
 * @param[out]	null     
 * @return		字符串对应的整型数
 * @date:		2018/08/02
 * @par Description: 
 * @note 
 * @see
 */
int ToInt(CString cstr)
{
	int res = 0;
	int length = cstr.GetLength();
	for(int i = 0; i < length; i++)
	{
		res = res*10 + (int)(cstr[i] - '0');
	}
	return res;
}

/**
 * @brief		ASCII转为16进制
 * @param[in]	
 * @param[out]	 
 * @return		
 * @date:		2018/08/02
 * @par Description: 
 * @note 
 * @see
 */
int AscToHex(int a) //ASC码转为16进制
{
    if(a > 70)
        a = a - 32;
    int x = 0;
    switch(a)
    {
        case 48: x = 0;		break;
        case 49: x = 1;		break;
        case 50: x = 2;		break;
        case 51: x = 3;		break;
        case 52: x = 4;		break;
        case 53: x = 5;		break;
        case 54: x = 6;		break;
        case 55: x = 7;		break;
        case 56: x = 8;		break;
        case 57: x = 9;		break;
        case 65: x = 10;	break;
        case 66: x = 11;	break;
        case 67: x = 12;	break;
        case 68: x = 13;	break;
        case 69: x = 14;	break;
        case 70: x = 15;	break;
        default : break;
    }
    return x;
}

CString	IntToHex(unsigned char num)
{
	CString res;
	unsigned char hight = num / 16;
	unsigned char low = num % 16;
	switch(hight)
    {
        case 0: res += "0";		break;
        case 1: res += "1";		break;
        case 2: res += "2";		break;
        case 3: res += "3";		break;
        case 4: res += "4";		break;
        case 5: res += "5";		break;
        case 6: res += "6";		break;
        case 7: res += "7";		break;
        case 8: res += "8";		break;
        case 9: res += "9";		break;
        case 10: res += "A";	break;
        case 11: res += "B";	break;
        case 12: res += "C";	break;
        case 13: res += "D";	break;
        case 14: res += "E";	break;
        case 15: res += "F";	break;
        default : break;
    }
	switch( low )
    {
        case 0: res += "0";		break;
        case 1: res += "1";		break;
        case 2: res += "2";		break;
        case 3: res += "3";		break;
        case 4: res += "4";		break;
        case 5: res += "5";		break;
        case 6: res += "6";		break;
        case 7: res += "7";		break;
        case 8: res += "8";		break;
        case 9: res += "9";		break;
        case 10: res += "A";	break;
        case 11: res += "B";	break;
        case 12: res += "C";	break;
        case 13: res += "D";	break;
        case 14: res += "E";	break;
        case 15: res += "F";	break;
        default : break;
    }
	return res;
}

CString  hexToStrNoBlank(unsigned char *tpHexData, int len)
{
	CString res;
	unsigned char *strData;
	strData = tpHexData;
	for(int i = 0; i < len; i++)
	{
         res += IntToHex(*strData++);
	}
	return res;
}


void HexToAscii(BYTE &byAt, BYTE &chAsciiH, BYTE &chAsciiL)
{
    chAsciiH=0x00;
    chAsciiL=0x00;
    switch(byAt&0xF0)
    {
        case 0x00: chAsciiH=0x30; break;
        case 0x10: chAsciiH=0x31; break;
        case 0x20: chAsciiH=0x32; break;
        case 0x30: chAsciiH=0x33; break;
        case 0x40: chAsciiH=0x34; break;
        case 0x50: chAsciiH=0x35; break;
        case 0x60: chAsciiH=0x36; break;
        case 0x70: chAsciiH=0x37; break;
        case 0x80: chAsciiH=0x38; break;
        case 0x90: chAsciiH=0x39; break;
        case 0xA0: chAsciiH=0x41; break;
        case 0xB0: chAsciiH=0x42; break;
        case 0xC0: chAsciiH=0x43; break;
        case 0xD0: chAsciiH=0x44; break;
        case 0xE0: chAsciiH=0x45; break;
        case 0xF0: chAsciiH=0x46; break;
        default:return;
    }
    switch(byAt&0x0F)
    {
        case 0x00:chAsciiL=0x30; break;
        case 0x01:chAsciiL=0x31; break;
        case 0x02:chAsciiL=0x32; break;
        case 0x03:chAsciiL=0x33; break;
        case 0x04:chAsciiL=0x34; break;
        case 0x05:chAsciiL=0x35; break;
        case 0x06:chAsciiL=0x36; break;
        case 0x07:chAsciiL=0x37; break;
        case 0x08:chAsciiL=0x38; break;
        case 0x09:chAsciiL=0x39; break;
        case 0x0A:chAsciiL=0x41; break;
        case 0x0B:chAsciiL=0x42; break;
        case 0x0C:chAsciiL=0x43; break;
        case 0x0D:chAsciiL=0x44; break;
        case 0X0E:chAsciiL=0x45; break;
        case 0x0F:chAsciiL=0x46; break;
        default: return;
    }
    return;
}

std::string itos(int num)
{
	std::string res;
	if(num == 0) return "0";
	while(0 != num)
	{
		res = (char)(num%10 + '0') + res;
		num /= 10;
	}
	return res;
}

int stoi(std::string str)
{
	int res = 0;
	for(unsigned int i = 0; i < str.length(); i++)
	{
		res = res*10 + (int)(str[i]-'0');
	}
	return res;
}