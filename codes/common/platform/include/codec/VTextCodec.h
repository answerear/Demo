

#ifndef __VISION_TEXT_CODEC_H__
#define __VISION_TEXT_CODEC_H__


#include "VSingleton.h"
#include "VPlatform.h"


namespace VPlatform
{
	class VPLATFORM_API VTextCodec : public VSingleton<VTextCodec>
	{
		V_DISABLE_COPY(VTextCodec);

	public:
		VTextCodec(const VString &strCodecFile);
		virtual ~VTextCodec();

		/** GBK字符串有效性检查，过滤掉被截断的不完整gbk码 */
		bool checkGBKString(char *pText, int32_t nTextLength);
		
		/** 是否是gbk首字节 */
		bool IsGBKLeadByte(uchar_t ucChar) const;

		/** 是否gbk字符 */
		bool IsGBKChar(uint16_t ushChar) const;
		
		/** 是否gb2312字符 */
		bool IsGB2312Char(uint16_t ushChar) const;

		/** UTF-8转换成Unicode */
		bool UTF8ToUnicode(wchar_t &wchar, const char szInString[3]);

		/** Unicode转换成UTF-8 */
		bool UnicodeToUTF8(char szOutString[3], wchar_t wchar);

		/** 把Unicode转换成GB2312 */
		uint32_t UnicodeToGB2312(char *pszOutString, const wchar_t *pwszInString, uint32_t unInSize = -1);

		/** 把Unicode转换成GB2312 */
		uint32_t UnicodeToGB2312Ex(VString &strOut, const wchar_t *pwszInString, uint32_t unInSize = -1);

		/** UTF-8转为GB2312 */
		uint32_t UTF8ToGB2312(char *pszOutString, const char *pszInString, uint32_t unInSize = -1);

		/** UTF-8转为GB2312 */
		uint32_t UTF8ToGB2312Ex(VString &strOut, const char *pszInString, uint32_t unInSize = -1);

		/** GB2312转换成Unicode */
		uint32_t GB2312ToUnicode(wchar_t *pwszOutString, const char *pszInString, uint32_t unInSize = -1);

		/** GB2312转换成Unicode */
		uint32_t GB2312ToUnicodeEx(VWString &wstrOut, const char *pszInString, uint32_t unInSize = -1);

		/** GB2312转为UTF-8 */
		uint32_t GB2312ToUTF8(char *pszOutString, const char *pszInString, uint32_t unInSize = -1);

		/** GB2312转为UTF-8 */
		uint32_t GB2312ToUTF8Ex(VString &strOut, const char *pszInString, uint32_t unInSize = -1);

		bool TrimString(const VString &strSrc, VString &strDst);

		bool IsEmoji(int32_t codePoint);
		VString FilterEmoji(const VString &str);

		char CharToHex(char input);
		VString StringToHexString(const VString &strSrc);

		bool SubUTF8String(VString& sourceStr,int start,int size);

	protected:
		bool InitCodeTableFromFile(const VString &strCodecFile);

		int32_t DecodeUtfCodeTwoChar(uchar_t a, uchar_t b);
		int32_t DecodeUtfCodeThreeChar(uchar_t a, uchar_t b, uchar_t c);
		int32_t DecodeUtfCodeFourChar(uchar_t a, uchar_t b, uchar_t c , uchar_t d);
		int32_t DecodeUtfCodeFiveChar(uchar_t a, uchar_t b, uchar_t c , uchar_t d, uchar_t e);
		int32_t DecodeUtfCodeSixChar(uchar_t a, uchar_t b, uchar_t c , uchar_t d, uchar_t e, uchar_t f);

	protected:
		uint16_t	m_ushCodeTable[65536][2];
	};
}


#define V_TEXT_CODEC					VPlatform::VTextCodec::GetInstance()

#define VStringToHexString(src)			V_TEXT_CODEC.StringToHexString(src)


#endif	/*__VISION_TEXT_CODEC_H__*/