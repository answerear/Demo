
#include "VTextCodec.h"
#include "VDir.h"
#include <stdio.h>

INIT_SINGLETON(VPlatform::VTextCodec);


namespace VPlatform
{
	#define FilterEmoji_MaxLen   1024  //如果文字过长就截断

	#define IS_SIMPLE_GBK(x)	((x) & 0x80)

	VTextCodec::VTextCodec(const VString &strCodecFile)
	{
		VString strPath = VDir::getAppPath() + strCodecFile;
		InitCodeTableFromFile(strPath);
	}

	VTextCodec::~VTextCodec()
	{

	}

	bool VTextCodec::InitCodeTableFromFile(const VString &strCodecFile)
	{
		bool bRet = false;

		if (!strCodecFile.empty())
		{
			FILE *stream = fopen(strCodecFile.c_str(), "r");
			if (stream)
			{
				int numread = fread(m_ushCodeTable, sizeof(m_ushCodeTable), 1, stream);
				bRet = numread == 1;

				fclose(stream);
			}
		}

		return bRet;
	}

	// GBK字符串有效性检查，过滤掉被截断的不完整gbk码
	bool VTextCodec::checkGBKString(char *pText, int32_t nTextLength)
	{
		if (NULL == pText || nTextLength <= 0) 
			return false;

		int pos = 0;
		while (pText[pos] && pos < nTextLength)
		{
			if (IsGBKChar((uint16_t)pText[pos]))
			{
				// 完整的gbk码
				pos += 2;
			}
			else if (IsGBKLeadByte(pText[pos]))
			{
				// 半个gbk码，在此截断字符串
				pText[pos] = 0;
				break;
			}
			else
			{
				// ascii码
				pos++;
			}
		}

		return true;
	}

	// 是否是gbk首字节
	bool VTextCodec::IsGBKLeadByte(uchar_t ucChar) const
	{
		return (IS_SIMPLE_GBK(ucChar) && ucChar >= 0x81 && ucChar <= 0xfe);
	}

	// 是否gbk字符
	bool VTextCodec::IsGBKChar(uint16_t ushChar) const
	{
		uchar_t uc1 = ushChar & 0xff;
		uchar_t uc2 = (ushChar >> 8);

		if (IS_SIMPLE_GBK(uc1)) // 先快速判断一下
		{
			// GBK编码范围是：首(低)字节从0x81到0xFE，尾(高)字节从0x40到0xFE，同时不包括0x7F
			if (uc1 >= 0x81 && uc1 <= 0xfe && uc2 >= 0x40 && uc2 <= 0xfe && uc2 != 0x7f)
			{
				return true;
			}
		}
		else
		{
			if (!(uc1>='a' &&  uc1 <='z' ||  uc1>='A' &&  uc1<='Z'))
			{
				return false;
			}
		}

		return false;
	}

	// 是否gb2312字符
	bool VTextCodec::IsGB2312Char(uint16_t ushChar) const
	{
		uchar_t uc1 = ushChar & 0xff;
		uchar_t uc2 = (ushChar >> 8);

		if (IS_SIMPLE_GBK(uc1)) // 先快速判断一下
		{
			// GB2312编码范围是：首(低)字节从0xB0到0xF7，尾(高)字节从0xA1到0xFE，同时不包括0x7F
			if (uc1 >= 0xb0 && uc1 <= 0xf7 && uc2 >= 0xa1 && uc2 <= 0xfe && uc2 != 0x7f)
			{
				return true;
			}
		}

		return false;
	}

	// 把UTF-8转换成Unicode
	bool VTextCodec::UTF8ToUnicode(wchar_t &wchar, const char szInString[3])
	{
		bool bRet = false;

		if (NULL != szInString)
		{
			// 确保大于2字节情况下的wchar高位清0
			wchar = 0;

			char *pChars = (char *)&wchar;

			pChars[1] = ((szInString[0] & 0x0F) << 4) + ((szInString[1] >> 2) & 0x0F);
			pChars[0] = ((szInString[1] & 0x03) << 6) + (szInString[2] & 0x3F);

			bRet = true;
		}

		return bRet;
	}

	// Unicode转换成UTF-8
	bool VTextCodec::UnicodeToUTF8(char szOutString[3], wchar_t wchar)
	{
		bool bRet = false;

		if (NULL != szOutString)
		{
			char *pChars = (char *)&wchar;

			szOutString[0] = (0xE0 | ((pChars[1] & 0xF0) >> 4));
			szOutString[1] = (0x80 | ((pChars[1] & 0x0F) << 2)) + ((pChars[0] & 0xC0) >> 6);
			szOutString[2] = (0x80 | (pChars[0] & 0x3F));

			bRet = true;
		}

		return bRet;
	}

	// 把Unicode转换成GB2312
	uint32_t VTextCodec::UnicodeToGB2312(char *pszOutString, const wchar_t *pwszInString, uint32_t unInSize/* = -1*/)
	{
		if (NULL == pwszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = wcslen(pwszInString);
		}

		uint32_t unOutSize = 0;

		uint32_t i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pszOutString)
		{
			for (i=0; i < unInSize; ++i)
			{
				uint16_t ushCode = (uint16_t)pwszInString[i];

				if (IS_SIMPLE_GBK(ushCode))
				{
					*(uint16_t *)(pszOutString+unOutSize) = m_ushCodeTable[ushCode][1];

					unOutSize += 2;
				}
				else
				{
					pszOutString[unOutSize] = *(char *)&m_ushCodeTable[ushCode][1];

					unOutSize += 1;
				}
			}
		}
		else
		{
			for (i=0; i < unInSize; ++i)
			{
				if (IS_SIMPLE_GBK(pwszInString[i]))
				{
					unOutSize += 2;
				}
				else
				{
					unOutSize += 1;
				}
			}
		}

		return unOutSize;
	}

	// 把Unicode转换成GB2312
	uint32_t VTextCodec::UnicodeToGB2312Ex(VString &strOut, const wchar_t *pwszInString, uint32_t unInSize)
	{
		if (NULL == pwszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = wcslen(pwszInString);
		}

		uint32_t i = 0;

		strOut = "";

		for (i=0; i < unInSize; ++i)
		{
			uint16_t ushCode = (uint16_t)pwszInString[i];

			if (IS_SIMPLE_GBK(ushCode))
			{
				uint16_t ushChar = m_ushCodeTable[ushCode][1];

				strOut += (ushChar & 0xff);
				strOut += (ushChar >> 8);
			}
			else
			{
				strOut += *(char *)&m_ushCodeTable[ushCode][1];
			}
		}

		return strOut.size();
	}

	// UTF-8转为GB2312
	uint32_t VTextCodec::UTF8ToGB2312(char *pszOutString, const char *pszInString, uint32_t unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		uint32_t unOutSize = 0;

		uint32_t i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pszOutString)
		{
			while (i < unInSize)
			{
				if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
				{
					wchar_t wchar;
					UTF8ToUnicode(wchar, pszInString+i);

					uint16_t ushCode = (uint16_t)wchar;

					*(uint16_t *)(pszOutString+unOutSize) = m_ushCodeTable[ushCode][1];

					unOutSize += 2;

					i += 3;
				}
				else
				{
					pszOutString[unOutSize] = pszInString[i];

					unOutSize++;
					i++;
				}
			}
		}
		else
		{
			while (i < unInSize)
			{
				if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
				{
					unOutSize += 2;

					i += 3;
				}
				else
				{
					unOutSize++;
					i++;
				}
			}
		}

		return unOutSize;
	}

	// UTF-8转为GB2312
	uint32_t VTextCodec::UTF8ToGB2312Ex(VString &strOut, const char *pszInString, uint32_t unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		uint32_t i = 0;

		strOut = "";

		while (i < unInSize)
		{
			if (i < unInSize-2 && IS_SIMPLE_GBK(pszInString[i]))
			{
				wchar_t wchar;
				UTF8ToUnicode(wchar, pszInString+i);

				uint16_t ushCode = (uint16_t)wchar;

				uint16_t ushChar = m_ushCodeTable[ushCode][1];

				strOut += (ushChar & 0xff);
				strOut += (ushChar >> 8);

				i += 3;
			}
			else
			{
				strOut += pszInString[i];

				i++;
			}
		}

		return strOut.size();
	}

	// GB2312转换成Unicode
	uint32_t VTextCodec::GB2312ToUnicode(wchar_t *pwszOutString, const char *pszInString, uint32_t unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		uint32_t unOutSize = 0;

		uint32_t i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pwszOutString)
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBKChar(*(uint16_t *)&pszInString[i]))
				{
					uint16_t ushCode = *(uint16_t *)(pszInString+i);

					pwszOutString[unOutSize++] = m_ushCodeTable[ushCode][0];

					i += 2;
				}
				else
				{
					pwszOutString[unOutSize++] = pszInString[i];

					i++;
				}
			}
		}
		else
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBKChar(*(uint16_t *)&pszInString[i]))
				{					
					unOutSize++;

					i += 2;
				}
				else
				{
					unOutSize++;

					i++;
				}
			}
		}

		return unOutSize;
	}

	// GB2312转换成Unicode
	uint32_t VTextCodec::GB2312ToUnicodeEx(VWString &wstrOut, const char *pszInString, uint32_t unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		uint32_t i = 0;

		wstrOut = L"";

		while (i < unInSize)
		{
			if (i < unInSize-1 && IsGBKChar(*(uint16_t *)&pszInString[i]))
			{
				uint16_t ushCode = *(uint16_t *)(pszInString+i);

				wstrOut += m_ushCodeTable[ushCode][0];

				i += 2;
			}
			else
			{
				wstrOut += pszInString[i];

				i++;
			}
		}

		return wstrOut.size();
	}

	// GB2312转为UTF-8
	uint32_t VTextCodec::GB2312ToUTF8(char *pszOutString, const char *pszInString, uint32_t unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		uint32_t unOutSize = 0;

		uint32_t i = 0;

		// 为NULL直接告诉需要的buffer长度，都不带结束符
		if (NULL != pszOutString)
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBKChar(*(uint16_t *)&pszInString[i]))
				{
					uint16_t ushCode = *(uint16_t *)(pszInString+i);

					wchar_t wchar = m_ushCodeTable[ushCode][0];

					UnicodeToUTF8(pszOutString+unOutSize, wchar);

					unOutSize += 3;
					i += 2;
				}
				else
				{
					pszOutString[unOutSize++] = pszInString[i];

					i++;
				}
			}
		}
		else
		{
			while (i < unInSize)
			{
				if (i < unInSize-1 && IsGBKChar(*(uint16_t *)&pszInString[i]))
				{
					unOutSize += 3;
					i += 2;
				}
				else
				{
					unOutSize++;
					i++;
				}
			}
		}

		return unOutSize;
	}

	// GB2312转为UTF-8
	uint32_t VTextCodec::GB2312ToUTF8Ex(VString &strOut, const char *pszInString, uint32_t unInSize)
	{
		if (NULL == pszInString || 0 == unInSize)
		{
			return 0;
		}

		if (-1 == unInSize)
		{
			unInSize = strlen(pszInString);
		}

		uint32_t i = 0;

		strOut = "";

		while (i < unInSize)
		{
			if (i < unInSize-1 && IsGBKChar(*(uint16_t *)&pszInString[i]))
			{
				uint16_t ushCode = *(uint16_t *)(pszInString+i);

				wchar_t wchar = m_ushCodeTable[ushCode][0];

				char str[3];

				UnicodeToUTF8(str, wchar);

				strOut += str[0];
				strOut += str[1];
				strOut += str[2];

				i += 2;
			}
			else
			{
				strOut += pszInString[i];

				i++;
			}
		}

		return strOut.size();
	}

	VString VTextCodec::StringToHexString(const VString &strSrc)
	{
		if(strSrc.length() <= 0)
		{
			return strSrc;
		}
		VString hexWtSkey;
		uchar_t wtDstSkey[512];// to pay attention
		int32_t length = strSrc.length() / 2;
		for (int32_t i = 0; i < length; i++) {
			uchar_t high = CharToHex(strSrc[i * 2]) ;
			uchar_t low  = CharToHex(strSrc[i * 2 + 1]);
			uchar_t c = high << 4 | low;
			wtDstSkey[i] =  c;
		}
		hexWtSkey.assign((char*)wtDstSkey,length);	
		return hexWtSkey;
	}

	char VTextCodec::CharToHex(char input)
	{
		if (input == 0) {
			return 0;
		}
		char k = (char)0;
		if(input<='9' && input>='0') 
		{
			return (input - '0');
		}
		else if(input<='f' && input>='a')
		{
			return (input - 'a' + 10);
		}
		else if(input<='F' && input>='A')
		{
			return (input - 'A' + 10);
		}
		else 
		{
			return 0;
		}

		return 0;
	}

    int32_t VTextCodec::DecodeUtfCodeTwoChar(uchar_t a, uchar_t b)
    {
        int32_t ret = 0;
        int32_t bb = (b&0x3f);
        int32_t aa = (a&0x1f)<<6;
        ret = bb|aa;
        return ret;
    }
    
    int32_t VTextCodec::DecodeUtfCodeThreeChar(uchar_t a, uchar_t b, uchar_t c)
    {
        int32_t ret = 0;
        int32_t cc = (c&0x3f);
        int32_t bb = (b&0x3f)<<6;
        int32_t aa = (a&0xf)<<12;
        ret = cc|bb|aa;
        return ret;
    }
    
    int32_t VTextCodec::DecodeUtfCodeFourChar(uchar_t a, uchar_t b, uchar_t c , uchar_t d)
    {
        int32_t ret = 0;
        int32_t dd = (d&0x3f);
        int32_t cc = (c&0x3f)<<6;
        int32_t bb = (b&0x3f)<<12;
        int32_t aa = (a&0x7)<<18;
        ret = dd|cc|bb|aa;
        return ret;
    }
    
    int32_t VTextCodec::DecodeUtfCodeFiveChar(uchar_t a, uchar_t b, uchar_t c , uchar_t d, uchar_t e)
    {
        int32_t ret = 0;
        int32_t ee = (e&0x3f);
        int32_t dd = (d&0x3f)<<6;
        int32_t cc = (c&0x3f)<<12;
        int32_t bb = (b&0x3f)<<18;
        int32_t aa = (a&0x3)<<24;
        ret = ee|dd|cc|bb|aa;
        return ret;
    }
    
    int32_t VTextCodec::DecodeUtfCodeSixChar(uchar_t a, uchar_t b, uchar_t c , uchar_t d, uchar_t e, uchar_t f)
    {
        int32_t ret = 0;
        int32_t ff = (f&0x3f);
        int32_t ee = (e&0x3f)<<6;
        int32_t dd = (d&0x3f)<<12;
        int32_t cc = (c&0x3f)<<18;
        int32_t bb = (b&0x3f)<<24;
        int32_t aa = (a&0x1)<<30;
        ret = ff|ee|dd|cc|bb|aa;
        return ret;
    }
    
    bool VTextCodec::IsEmoji(int32_t codePoint)
    {
        return
        ((codePoint >= 0x1f000) && (codePoint <= 0x1f6f0))
        ||
        ((codePoint >= 0x2000) && (codePoint <= 0x2940))
        ||
        ((codePoint >= 0xE000) && (codePoint <= 0xE4FF));
    }
    
    
    VString VTextCodec::FilterEmoji(const VString &str)
    {
        //test
        //char test[] = {'t','1'};
        //char test[] = {'t','2',0xc1,0x81};
        //char test[] = {'t','3',0xe1,0x81,0x81};
        //char test[] = {'t','4',0xf1,0x81,0x81,0x81};
        //char test[] = {'t','5',0xf9,0x81,0x81,0x81,0x81};
        //char test[] = {'t','6',0xfd,0x81,0x81,0x81,0x81,0x81};
        //string testStr(test,0,8);
        //str = testStr;
        //test end
        int32_t length = str.length();
		if(length>FilterEmoji_MaxLen)//如果文字过长就截断
			length=FilterEmoji_MaxLen;

        char target[FilterEmoji_MaxLen];
        
        memset(target, 0, FilterEmoji_MaxLen);
        int32_t targetId=0;
        const char * source = str.c_str();
        
        for(int32_t i = 0; i < length; i++)
        {
            uchar_t tempChar = source[i]&0xff;
            
            if(tempChar >= 0 && tempChar < 0xc0)
            {
                target[targetId++] = source[i];
            }else if(tempChar >= 0xc0 && tempChar < 0xe0)
            {
                int32_t unicode = DecodeUtfCodeTwoChar(source[i],source[i+1]);
                if(IsEmoji(unicode))
                {
                    i += 1;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xe0 && tempChar < 0xf0)
            {
                int32_t unicode = (i+2 <= length) ? DecodeUtfCodeThreeChar(source[i],source[i+1],source[i+2]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 2;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xf0 && tempChar < 0xf8)
            {
                int32_t unicode = (i+3 <= length) ? DecodeUtfCodeFourChar(source[i],source[i+1],source[i+2],source[i+3]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 3;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xf8 && tempChar < 0xfc)
            {
                int32_t unicode = (i+4 <= length) ? DecodeUtfCodeFiveChar(source[i],source[i+1],source[i+2],source[i+3],source[i+4]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 4;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }else if(tempChar >= 0xfc && tempChar <= 0xff)
            {
                int32_t unicode = (i+5 <= length) ? DecodeUtfCodeSixChar(source[i],source[i+1],source[i+2],source[i+3],source[i+4],source[i+5]) : 0;
                if(IsEmoji(unicode))
                {
                    i += 5;
                    target[targetId++] = 0x20;
                }else
                {
                    target[targetId++] = source[i];
                }
            }
        }
        VString ret(target,0,targetId);
        return ret;
        
    }

	bool VTextCodec::TrimString(const VString &strSrc, VString &strDst)
	{
		return true;
	}

	bool VTextCodec::SubUTF8String(VString& sourceStr,int start,int size)
	{
		//test²âÊÔÓÃÀý£¬°üÀ¨Ò»¸ö1~6¸ö×Ö½Ú±íÊ¾µÄUTF8×Ö·û
		/*char test[] = {0xc0,0x80,'1',0xe0,0x80,0x80,'1',0xf0,0x80,0x80,0x80,'1',0xf8,0x80,0x80,0x80,0x80,'1',0xfc,0x80,0x80,0x80,0x80,0x80};
		string testStr(test,0,24);
		string resultStr = SubUTF8String(testStr,0,1);*/
		//test end
		int length = sourceStr.length();

		if(size < 1 
			|| start < 0 
			|| start > (length - 1) 
			|| (start + size) > length
			|| length < 1)
		{
			return false;
		}
		int end = start + size - 1;
		int curCharIndex = 0;
		int startPosition = 0;
		int endPosition = 0;

		const char * source = sourceStr.c_str();
		//2个ascii码字符抵一个汉字,因此遇到非ascii码时，curCharIndex要增加2个

		for(int i = 0; i < length; i++)
		{
			unsigned char tempChar = source[i]&0xff;

			if(tempChar >= 0 && tempChar < 0xc0)
			{
				if(curCharIndex == start)
				{
					startPosition = i;
				}
				if(curCharIndex >= end)
				{
					endPosition = i;
					break;
				}
			}
			else if(tempChar >= 0xc0 && tempChar < 0xe0)
			{
				if(curCharIndex == start)
				{
					startPosition = i;
				}
				//因为已经进入了这个判断，表明这就是一个双字节的字，就当做汉字，因此先加1再去判断是不是结束了
				curCharIndex++;//2个ascii码字符抵一个汉字,因此遇到非ascii码时，curCharIndex要增加2个
				if(curCharIndex >= end)
				{
					endPosition = i+1;
					break;
				}
				i += 1;
			}
			else if(tempChar >= 0xe0 && tempChar < 0xf0)
			{
				if(curCharIndex == start)
				{
					startPosition = i;
				}
				curCharIndex++;//2个ascii码字符抵一个汉字,因此遇到非ascii码时，curCharIndex要增加2个
				if(curCharIndex >= end)
				{
					endPosition = i+2;
					break;
				}
				i += 2;
			}
			else if(tempChar >= 0xf0 && tempChar < 0xf8)
			{
				if(curCharIndex == start)
				{
					startPosition = i;
				}
				curCharIndex++;//2个ascii码字符抵一个汉字,因此遇到非ascii码时，curCharIndex要增加2个
				if(curCharIndex >= end)
				{
					endPosition = i+3;
					break;
				}
				i += 3;
			}
			else if(tempChar >= 0xf8 && tempChar < 0xfc)//到这其实没意义了，因为utf8最长为4个字节，前五位最大的开头是11110111=f7
			{
				if(curCharIndex == start)
				{
					startPosition = i;
				}
				curCharIndex++;//2个ascii码字符抵一个汉字,因此遇到非ascii码时，curCharIndex要增加2个
				if(curCharIndex >= end)
				{
					endPosition = i+4;
					break;
				}
				i += 4;
			}
			else if(tempChar >= 0xfc && tempChar <= 0xff)
			{
				if(curCharIndex == start)
				{
					startPosition = i;
				}
				curCharIndex++;//2个ascii码字符抵一个汉字,因此遇到非ascii码时，curCharIndex要增加2个
				if(curCharIndex >= end)
				{
					endPosition = i+5;
					break;
				}
				i += 5;
			}
			curCharIndex++;
		}

		if(startPosition >= 0 
			&& (endPosition + 1) <= length
			&& curCharIndex == end)
		{
			VString ret(source,startPosition,endPosition+1);
			sourceStr = ret;
			return true;
		}
		else
		{
			return false;
		}

	}
}