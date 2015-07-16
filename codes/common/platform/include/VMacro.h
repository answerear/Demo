

#ifndef __VISION_MACRO_H__
#define __VISION_MACRO_H__


#include "VType.h"
#include <assert.h>


#if defined V_OS_WIN32		// Win32

	#ifdef _DEBUG	// debug
		#define V_DEBUG
	#else			// release
		#undef V_DEBUG
	#endif

	#pragma warning(disable:4996)
	#pragma warning(disable:4251)
	#define snprintf	_snprintf
	#define vsnprintf	_vsnprintf

#elif defined V_OS_IOS || defined V_OS_MAC || defined V_OS_LINUX	// iOS or Mac OS x or Linux

	#ifdef DEBUG	// debug
		#define V_DEBUG
	#else			// release
		#undef V_DEBUG
	#endif

#elif defined V_OS_ANDROID	// Android

	#ifdef NDK_DEBUG	// debug
		#define V_DEBUG
	#else				// release
		#undef V_DEBUG
	#endif

#endif


#ifndef ASSERT
#ifdef V_DEBUG
#define ASSERT(x)	assert(x)
#else
#define ASSERT(x)
#endif
#endif


#define MK_DWORD(h, l)		(((h<<16)&0xFFFF0000)|(0xFFFF&l))
#define LO_WORD(x)			(x&0xFFFF)
#define HI_WORD(x)			((x>>16)&0xFFFF)
#define MK_WORD(h, l)		(((h<<8)&0xFF00)|(0xFF&l))
#define LO_BYTE(x)			(x&0xFF)
#define HI_BYTE(x)			((x&>>8)&0xFF)


#define V_DECLARE_INTERFACE(T)	\
	public:		\
		virtual ~T()	{}

#define V_DISABLE_COPY(T)	\
	private:	\
		T(const T &);	\
		T &operator =(const T &);

#define V_SAFE_DELETE(p)	\
	if (p != NULL)	\
	{	\
		delete p;	\
		p = NULL;	\
	}

#define V_SAFE_DELETE_ARRAY(p)	\
	if (p != NULL)	\
	{	\
		delete []p;	\
		p = NULL;	\
	}


#define V_MAX_LOG_BUFFER_SIZE			4096

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif	/*__VISION_LOGGER_MACRO_H__*/
