#include "QGGBKcode.h"

namespace QGTSDKFacade
{
	std::string QGGBKcode::wtSkey2Hex(const std::string wtSkey)
	{
		if(wtSkey.length() <= 0)
		{
			return wtSkey;
		}
		std::string hexWtSkey;
		unsigned char wtDstSkey[512];// to pay attention
		int length = wtSkey.length() / 2;
		for (int i = 0; i < length; i++) {
			unsigned char high = CharToHex(wtSkey[i * 2]) ;
			unsigned char low  = CharToHex(wtSkey[i * 2 + 1]);
			unsigned char c = high << 4 | low;
			wtDstSkey[i] =  c;
		}
		hexWtSkey.assign((char*)wtDstSkey,length);	
		return hexWtSkey;
	}

	char QGGBKcode::CharToHex(char input)
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

    int QGGBKcode::DecodeUtfCodeTwoChar(unsigned char a, unsigned char b)
    {
        int ret = 0;
        int bb = (b&0x3f);
        int aa = (a&0x1f)<<6;
        ret = bb|aa;
        return ret;
    }
    
    int QGGBKcode::DecodeUtfCodeThreeChar(unsigned char a, unsigned char b, unsigned char c)
    {
        int ret = 0;
        int cc = (c&0x3f);
        int bb = (b&0x3f)<<6;
        int aa = (a&0xf)<<12;
        ret = cc|bb|aa;
        return ret;
    }
    
    int QGGBKcode::DecodeUtfCodeFourChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d)
    {
        int ret = 0;
        int dd = (d&0x3f);
        int cc = (c&0x3f)<<6;
        int bb = (b&0x3f)<<12;
        int aa = (a&0x7)<<18;
        ret = dd|cc|bb|aa;
        return ret;
    }
    
    int QGGBKcode::DecodeUtfCodeFiveChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d, unsigned char e)
    {
        int ret = 0;
        int ee = (e&0x3f);
        int dd = (d&0x3f)<<6;
        int cc = (c&0x3f)<<12;
        int bb = (b&0x3f)<<18;
        int aa = (a&0x3)<<24;
        ret = ee|dd|cc|bb|aa;
        return ret;
    }
    
    int QGGBKcode::DecodeUtfCodeSixChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d, unsigned char e, unsigned char f)
    {
        int ret = 0;
        int ff = (f&0x3f);
        int ee = (e&0x3f)<<6;
        int dd = (d&0x3f)<<12;
        int cc = (c&0x3f)<<18;
        int bb = (b&0x3f)<<24;
        int aa = (a&0x1)<<30;
        ret = ff|ee|dd|cc|bb|aa;
        return ret;
    }
    
    bool QGGBKcode::IsEmoji(int codePoint)
    {
        return
        ((codePoint >= 0x1f000) && (codePoint <= 0x1f6f0))
        ||
        ((codePoint >= 0x2000) && (codePoint <= 0x2940))
        ||
        ((codePoint >= 0xE000) && (codePoint <= 0xE4FF));
    }
    
    
    std::string QGGBKcode::FilterEmoji(std::string str)
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
        int length = str.length();
		if(length>FilterEmoji_MaxLen)//如果文字过长就截断
			length=FilterEmoji_MaxLen;

        char target[FilterEmoji_MaxLen];
        
        memset(target, 0, FilterEmoji_MaxLen);
        int targetId=0;
        const char * source = str.c_str();
        
        for(int i = 0; i < length; i++)
        {
            unsigned char tempChar = source[i]&0xff;
            
            if(tempChar >= 0 && tempChar < 0xc0)
            {
                target[targetId++] = source[i];
            }else if(tempChar >= 0xc0 && tempChar < 0xe0)
            {
                int unicode = DecodeUtfCodeTwoChar(source[i],source[i+1]);
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
                int unicode = (i+2 <= length) ? DecodeUtfCodeThreeChar(source[i],source[i+1],source[i+2]) : 0;
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
                int unicode = (i+3 <= length) ? DecodeUtfCodeFourChar(source[i],source[i+1],source[i+2],source[i+3]) : 0;
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
                int unicode = (i+4 <= length) ? DecodeUtfCodeFiveChar(source[i],source[i+1],source[i+2],source[i+3],source[i+4]) : 0;
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
                int unicode = (i+5 <= length) ? DecodeUtfCodeSixChar(source[i],source[i+1],source[i+2],source[i+3],source[i+4],source[i+5]) : 0;
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
        std::string ret(target,0,targetId);
        return ret;
        
    }
}