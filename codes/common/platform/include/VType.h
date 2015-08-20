

#ifndef __VISION_TYPE_H__
#define __VISION_TYPE_H__


#include <string>
#include <map>

typedef signed char			char_t;
typedef unsigned char       uchar_t;
typedef signed short		short_t;
typedef unsigned short      ushort_t;
typedef signed int			int_t;
typedef unsigned int        uint_t;
typedef signed long			long_t;
typedef unsigned long       ulong_t;

typedef signed char			int8_t;
typedef unsigned char		uint8_t;
typedef signed short		int16_t;
typedef unsigned short		uint16_t;
typedef signed int			int32_t;
typedef unsigned int		uint32_t;

typedef signed long long	int64_t;
typedef unsigned long long	uint64_t;


typedef std::string			VString;
typedef std::wstring		VWString;



#if defined V_OS_WIN32	// Win32

	#if defined V_USE_DLL
		#define VEXPORT_API			__declspec(dllexport)
		#define VIMPORT_API			__declspec(dllimport)
	#else
		#define VEXPORT_API
		#define VIMPORT_API
	#endif

	#ifndef STDCALL
		#define STDCALL			__stdcall
	#endif

	#ifdef _WIN64
		#define V_OS_X64
	#else
		#define V_OS_X86
	#endif

#else

	#define VEXPORT_API
	#define VIMPORT_API

	#define STDCALL

#endif


#endif	/*__VISION_TYPE_H__*/
