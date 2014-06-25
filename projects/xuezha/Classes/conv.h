#ifndef _CONV_H_
#define _CONV_H_

#include "cocos2d.h"  

inline int WCHARToUTF8(const wchar_t* src, std::string& utfStr)
{
    char buffer[256] = {};
    int ret = wcstombs(buffer, src, 256);
    utfStr = buffer;
    return ret;
}

//ֻ�������ֽ���string��
inline std::string WStringToString(const std::wstring &wstr)
{
    std::string str(wstr.length(), ' ');
    std::copy(wstr.begin(), wstr.end(), str.begin());
    return str;
}

inline std::wstring StringToWString(const std::string &str)
{
    std::wstring wstr(str.length(), L' ');
    std::copy(str.begin(), str.end(), wstr.begin());
    return wstr;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  

#include "iconv\iconv.h"
#pragma comment(lib, "libiconv.lib")

inline int ConvertCode(std::string &gbkStr,const char* toCode,const char* formCode)
{
	iconv_t iconvH;  
	iconvH = iconv_open(formCode,toCode);  
	if(iconvH == 0)  
	{  
		return -1;  
	}  

	const char* strChar = gbkStr.c_str();  
	const char** pin = &strChar;  

	size_t strLength = gbkStr.length();  
	char* outbuf = (char*)malloc(strLength*4);  
	char* pBuff = outbuf;  
	memset(outbuf,0,strLength*4);  
	size_t outLength = strLength*4;  
	if(-1 == iconv(iconvH,pin,&strLength,&outbuf,&outLength))  
	{  
		iconv_close(iconvH);  
		return -1;  
	}  

	gbkStr = pBuff;  
	iconv_close(iconvH);  
	return 0; 
}

/** 
**�ڷ�װһ�㣬ֱ�Ӵ���һ��string��ת���󻹻ض�Ӧ�ı������ 
*/  
inline const char* GBKToUTF(std::string &gbkStr)  
{  
    ConvertCode(gbkStr, "gbk", "utf-8"); //��������������Ĭ����,��ú����ٴ����鷳  

	return gbkStr.c_str();  
}  


#endif 

#endif//_CONV_H_
