

#include "VSocket.h"


namespace VPlatform
{
	int32_t VSocket::m_nCount = 0;

	VString VSocket::GetHostByName(const VString &strDomain)
	{
		if (strDomain.empty() || strDomain == "")
			return VString("");

		hostent *pHostEnt = ::gethostbyname(strDomain.c_str());
		if (pHostEnt != NULL)
		{
			if (pHostEnt->h_addr_list[0] != NULL)
			{
				return VString(inet_ntoa(*((struct in_addr*)pHostEnt->h_addr_list[0])));
			}
		}

		return VString("");
	}

	ulong_t VSocket::DNS(const VString &strDomain)
	{
		if (strDomain.empty() || strDomain == "")
			return INADDR_NONE;

		hostent *pHostEnt = ::gethostbyname(strDomain.c_str());
		if (pHostEnt != NULL)
		{
			if (pHostEnt->h_addr != NULL)
			{
				sockaddr_in address;
				struct in_addr *pin_addr =  ((struct in_addr *)pHostEnt->h_addr);
				address.sin_addr = *(pin_addr);
				ulong_t ip = address.sin_addr.s_addr;
				return ip;
			}
		}

		return INADDR_NONE;
	}

	bool VSocket::IsDomain(const VString &strDomain)
	{
		if (strDomain.empty() || strDomain == "")
			return false;

		ulong_t ulHostIP = inet_addr(strDomain.c_str());

		return (ulHostIP == INADDR_NONE);
	}

	VSocket::VSocket()
		: m_Socket(V_INVALID_SOCKET)
	{
		
	}

	VSocket::~VSocket()
	{
		Close();
	}

	bool VSocket::Create(EProtocol eProtocol /* = PROTOCOL_TCP */)
	{
		if (0 == m_nCount++)
		{
			if (!Startup(1, 1))
				return false;
		}

		if (V_INVALID_SOCKET != m_Socket)
		{
			Close();
		}

		if (PROTOCOL_UDP == eProtocol)
		{
			m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		}
		else
		{
			m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		}

		return V_INVALID_SOCKET != m_Socket;
	}

	bool VSocket::Close()
	{
		if (V_INVALID_SOCKET == m_Socket)
		{
			return false;
		}

		shutdown(m_Socket, 2);

		VCloseSocket(m_Socket);
		m_Socket = V_INVALID_SOCKET;

		if (0 == --m_nCount)
		{
			Cleanup();
		}

		return true;
	}

	bool VSocket::Attach(SOCKET socket)
	{
		m_Socket = socket;
		return true;
	}

	SOCKET VSocket::Detach()
	{
		SOCKET socket = m_Socket;
		m_Socket = V_INVALID_SOCKET;
		return socket;
	}

	bool VSocket::Connect(const VString &strHostAddress, uint16_t unHostPort)
	{
		if (strHostAddress.empty() || strHostAddress == "")
		{
			return false;
		}

		SOCKADDR_IN addrRemote;
		hostent *lpszHost = 0;

		memset(&addrRemote, 0, sizeof(addrRemote));
		addrRemote.sin_family = AF_INET;
		addrRemote.sin_port = htons(unHostPort);
		addrRemote.sin_addr.s_addr = inet_addr(strHostAddress.c_str());

		if (INADDR_NONE == addrRemote.sin_addr.s_addr)
		{
			lpszHost = gethostbyname(strHostAddress.c_str());
			if (NULL == lpszHost) 
				return false;

			memcpy(&addrRemote.sin_addr, lpszHost->h_addr_list[0], lpszHost->h_length);
		}

		if (connect(m_Socket, (SOCKADDR *)&addrRemote, sizeof(addrRemote)) == V_SOCKET_ERROR)
		{
			return false;
		}

		return true;
	}

	bool VSocket::Connect(ulong_t ulHostIP, uint16_t unHostPort)
	{
		if (ulHostIP == 0)
		{
			return false;
		}

		SOCKADDR_IN addrRemote;

		memset(&addrRemote, 0, sizeof(addrRemote));
		addrRemote.sin_family = AF_INET;
		addrRemote.sin_port = htons(unHostPort);
		addrRemote.sin_addr.s_addr = ulHostIP;

		if (connect(m_Socket, (SOCKADDR *)&addrRemote, sizeof(addrRemote)) == V_SOCKET_ERROR)
		{
			return false;
		}

		return true;
	}

	bool VSocket::Listen(int32_t nConnectionBacklog /* = 5 */)
	{
		if (listen(m_Socket, nConnectionBacklog) == V_SOCKET_ERROR)
		{
			return false;
		}

		return true;
	}

	bool VSocket::Bind(uint16_t unSocketPort, const VString &strSocketAddress /* = "" */)
	{
		if (V_INVALID_SOCKET == m_Socket)
		{
			return false;
		}

		SOCKADDR_IN addrLocal;
		addrLocal.sin_family = AF_INET;
		addrLocal.sin_port = htons(unSocketPort);

		if (strSocketAddress.empty() || strSocketAddress == "")
		{
			addrLocal.sin_addr.s_addr = inet_addr(strSocketAddress.c_str());
		}
		else
		{
			addrLocal.sin_addr.s_addr = htonl(INADDR_ANY);
		}

		if (bind(m_Socket, (SOCKADDR *)&addrLocal, sizeof(addrLocal)) == V_SOCKET_ERROR)
		{
			return false;
		}

		return true;
	}

	bool VSocket::Accept(VSocket &sockClient)
	{
		SOCKADDR_IN addr;
		int32_t len = sizeof(addr);
		SOCKET socket;

		socket = accept(m_Socket, (SOCKADDR *)&addr, (socklen_t *)&len);
		if (V_INVALID_SOCKET == socket || 0 == socket)
		{
			return false;
		}

		++m_nCount;

		sockClient.Attach(socket);

		return true;
	}

	int32_t VSocket::Recv(uchar_t *pBuffer, int32_t nBufLen)
	{
		return recv(m_Socket, (char*)pBuffer, nBufLen, 0);
	}

	int32_t VSocket::Send(uchar_t *pBuffer, int32_t nBufLen)
	{
		return send(m_Socket, (char*)pBuffer, nBufLen, 0);
	}

	int32_t VSocket::RecvFrom(uchar_t *pBuffer, int32_t nBufLen, const VString &strHostAddress, uint16_t unHostPort)
	{
		if (strHostAddress.empty() || strHostAddress == "")
			return -1;

		SOCKADDR_IN addrRemote;
		memset(&addrRemote, 0, sizeof(addrRemote));
		addrRemote.sin_family = AF_INET;
		addrRemote.sin_port = htons(unHostPort);
		addrRemote.sin_addr.s_addr = inet_addr(strHostAddress.c_str());

		socklen_t addrLen = sizeof(addrRemote);

		return recvfrom(m_Socket, (char*)pBuffer, nBufLen, 0, (SOCKADDR*)&addrRemote, (socklen_t*)&addrLen);
	}

	int32_t VSocket::SendTo(uchar_t *pBuffer, int32_t nBufLen, const VString &strHostAddress, uint16_t unHostPort)
	{
		if (strHostAddress.empty() || strHostAddress == "")
			return -1;

		SOCKADDR_IN addrRemote;
		memset(&addrRemote, 0, sizeof(addrRemote));
		addrRemote.sin_family = AF_INET;
		addrRemote.sin_port = htons(unHostPort);
		addrRemote.sin_addr.s_addr = inet_addr(strHostAddress.c_str());

		return sendto(m_Socket, (char*)pBuffer, nBufLen, 0, (SOCKADDR *)&addrRemote, sizeof(SOCKADDR_IN));
	}

	bool VSocket::CanWrite() const
	{
		fd_set writefds;
		struct timeval timeout;

		timeout.tv_sec=0;
		timeout.tv_usec=0;
		FD_ZERO(&writefds);
		FD_SET(m_Socket, &writefds);

		int ret = select(FD_SETSIZE, NULL, &writefds, NULL, &timeout);
		if(ret > 0 && FD_ISSET(m_Socket, &writefds))
			return true;
		
		return false;
	}

	bool VSocket::CanRead() const
	{
		fd_set readfds;
		struct timeval timeout;

		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		FD_ZERO(&readfds);
		FD_SET(m_Socket, &readfds);

		int32_t ret = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
		if (ret > 0 && FD_ISSET(m_Socket, &readfds))
			return true;
		
		return false;
	}

	bool VSocket::HasExcept() const
	{
		fd_set exceptfds;
		struct timeval timeout;

		timeout.tv_sec=0;
		timeout.tv_usec=0;
		FD_ZERO(&exceptfds);
		FD_SET(m_Socket, &exceptfds);

		int ret = select(FD_SETSIZE, NULL, NULL, &exceptfds, &timeout);
		if(ret > 0 && FD_ISSET(m_Socket, &exceptfds))
			return true;
		
		return false;
	}

	bool VSocket::SetNonBlocking()
	{
		/* set to nonblocking mode */
		ulong_t arg;
		arg = 1;

		if (VIOCtlSocket(m_Socket, FIONBIO, &arg) == V_SOCKET_ERROR)
		{
			return false;
		}
		
		return true;
	}

	void VSocket::Reset()
	{
		m_Socket = V_INVALID_SOCKET;
	}

	bool VSocket::SetSendBufferSize(int32_t nSize)
	{
		int32_t ret;
		ret = setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&nSize, sizeof(nSize));
		if (ret == V_SOCKET_ERROR) 
			return false;

		return true;
	}

	bool VSocket::SetRecvBufferSize(int32_t nSize)
	{
		int32_t ret;
		ret = setsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&nSize, sizeof(nSize));
		if (ret == V_SOCKET_ERROR)
			return false;

		return true;
	}

	bool VSocket::SetReuseAddress(bool bReuse)
	{
#ifndef V_OS_WIN32
		/* only useful in linux */
		int32_t opt = 0;
		uint32_t len = sizeof(opt);

		if (bReuse) 
			opt = 1;

		if (setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, len) == V_SOCKET_ERROR)
		{
			return false;
		}
		
		return true;
#else
		return true;
#endif
	}

	bool VSocket::GetLocalName(VString &rSockName, uint16_t &rSockPort) const
	{
		SOCKADDR_IN addrLocal;
		socklen_t len = sizeof(addrLocal);
		if (getsockname(m_Socket, (SOCKADDR*)&addrLocal, &len) == V_SOCKET_ERROR)
			return false;

		char *tmp = inet_ntoa(addrLocal.sin_addr);
		if (!tmp) 
			return false;
		
		rSockName = tmp;
		rSockPort = ntohs(addrLocal.sin_port);

		return true;
	}

	bool VSocket::GetPeerName(VString &rPeerName, uint16_t &rPeerPort) const
	{
		sockaddr_in addrRemote;
		int len = sizeof(addrRemote);
		if (getpeername(m_Socket, (sockaddr *)&addrRemote, (socklen_t *)&len) == V_SOCKET_ERROR)
			return false;

		char *tmp = inet_ntoa(addrRemote.sin_addr);
		if (!tmp) 
			return false;
		
		rPeerName = tmp;
		rPeerPort = ntohs(addrRemote.sin_port);

		return true;
	}

	uint32_t VSocket::GetErrorCode() const
	{
		return VGetError();
	}

	uint32_t VSocket::GetSocketError() const
	{
		socklen_t iSockErr, iSockErrLen = sizeof(iSockErr);
		int32_t ret = getsockopt(m_Socket, SOL_SOCKET, SO_ERROR, (char*)&iSockErr, &iSockErrLen);
		if (ret == V_SOCKET_ERROR) 
			return iSockErr;

		return 0;
	}

	bool VSocket::Startup(int32_t nVersionH, int32_t nVersionL)
	{
#ifdef V_OS_WIN32
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(nVersionH, nVersionL);
		err = WSAStartup(wVersionRequested, &wsaData);

		/* startup failed */
		if (err != 0)									
		{
			WSACleanup();
			return false;
		}

		/* version error */
		if (LOBYTE(wsaData.wVersion)!= nVersionL ||
			HIBYTE(wsaData.wVersion)!= nVersionH ) 
		{
			WSACleanup();
			return false;
		}
#endif
		return true;
	}

	bool VSocket::Cleanup()
	{
#ifdef V_OS_WIN32	
		WSACleanup();
#endif
		return true;
	}
}

