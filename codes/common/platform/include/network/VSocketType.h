/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VSocketType.h
 * @brief   网络套接字相关的平台定义.
 * @author  aaronwang
 * @date    2014/2/10 0:31:22
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_SOCKET_TYPE_H__
#define __VISION_SOCKET_TYPE_H__


#include "VType.h"
#include "VMacro.h"


#if defined (V_OS_WIN32)
	#include <WinSock.h>
//    #include <WinSock2.h>

	#define VGetError()				WSAGetLastError()
	#define VCloseSocket(s)			closesocket(s)
	#define VIOCtlSocket(s, c, a)	ioctlsocket(s, c, a)

	#define V_EAGAIN				WSAEWOULDBLOCK		// Resource temporarily unavailable. Nonblocking socket
	#define V_EINPROGRESS			WSAEINPROGRESS		// Operation now in progress. Blocking socket
	#define V_ENOBUFS				WSAENOBUFS			// No buffer space available.
	#define V_EINTR					WSAEINTR			// Interrupted function call.	
	#define V_ETIMEDOUT				WSAETIMEDOUT		// Connection timed out.
	#define V_EHOSTNOTFOUND			WSAHOST_NOT_FOUND	// 
	#define V_INVALID_SOCKET		INVALID_SOCKET
	#define V_SOCKET_ERROR			SOCKET_ERROR

	typedef int socklen_t;
#else
	#include <sys/time.h>
	#include <stddef.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <sys/wait.h>
	#include <sys/Socket.h>
	#include <netinet/in.h>
	#include <sys/ioctl.h>
	#include <netdb.h>
	#include <sys/errno.h>
	#include <arpa/inet.h>

	typedef int				SOCKET;
	typedef sockaddr_in		SOCKADDR_IN;
	typedef sockaddr		SOCKADDR;

	#define VGetError()			errno
	
	#define VCloseSocket(s)		close(s)
	#define VIOCtlSocket(s, c, a)	ioctl(s, c, a)

	#define V_EAGAIN				EAGAIN
	#define V_EINPROGRESS			EINPROGRESS
	#define V_ENOBUFS				ENOBUFS
	#define V_EINTR				EINTR
	#define V_ETIMEDOUT			ETIMEDOUT
	#define V_EHOSTNOTFOUND		133
	#define V_INVALID_SOCKET		(-1)
	#define V_SOCKET_ERROR			(-1)
#endif


#endif	/*__VISION_SOCKET_TYPE_H__*/
