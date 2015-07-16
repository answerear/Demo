#ifndef __QGGBKCODE_H__
#define __QGGBKCODE_H__

#include <string>
#include "QGType.h"
#include "QGMacro.h"
#include "VPlatform.h"


#define FilterEmoji_MaxLen   1024  //如果文字过长就截断
namespace QGTSDKFacade
{
	class QG_PLATFORM_API QGGBKcode
	{
	public:
		static int DecodeUtfCodeTwoChar(unsigned char a, unsigned char b);
		static int DecodeUtfCodeThreeChar(unsigned char a, unsigned char b, unsigned char c);
		static int DecodeUtfCodeFourChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d);
		static int DecodeUtfCodeFiveChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d, unsigned char e);
		static int DecodeUtfCodeSixChar(unsigned char a, unsigned char b, unsigned char c , unsigned char d, unsigned char e, unsigned char f);

		static bool IsEmoji(int codePoint);
		static std::string FilterEmoji(std::string str);

		static char CharToHex(char input);
		static std::string wtSkey2Hex(const std::string wtSkey);
	};
}

#endif