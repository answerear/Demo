/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VSocket.h
 * @brief   Socket类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:13:41
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_SOCKET_H__
#define __VISION_SOCKET_H__


#include "VSocketType.h"
#include "VPlatform.h"


namespace VPlatform
{
	/**
	 * @class VSocket
	 * @brief Socket封装类.
	 */
	class VPLATFORM_API VSocket
	{
		V_DISABLE_COPY(VSocket);

	public:
		/**
		 * @brief 套接字协议枚举
		 */
		enum EProtocol
		{
			PROTOCOL_UNKNOWN = 0,	/**< 未知协议 */
			PROTOCOL_UDP,			/**< UDP协议 */
			PROTOCOL_TCP			/**< TCP协议 */
		};

		/**
		 * @brief Constructor for VSocket.
		 */
		VSocket();

		/**
		 * @brief Destructor for VSocket.
		 */
		virtual ~VSocket();

		/**
		 * @brief 创建套接字.
		 * @param [in] eProtocol : 套接字协议类型，默认是TCP.
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Create(EProtocol eProtocol = PROTOCOL_TCP);

		/**
		 * @brief 关闭套接字.
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Close();

		/**
		 * @brief 附加原始套接字.
		 * @param [in] socket : 原始套接字描述符
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Attach(SOCKET socket);

		/**
		 * @brief 分离出原始套接字.
		 * @return 返回原始套接字描述符  
		 */
		SOCKET Detach();

		/**
		 * @brief 连接到指定IP和端口服务器.
		 * @param [in] strHostAddress : IP地址
		 * @param [in] unHostPort : 端口
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Connect(const VString &strHostAddress, uint16_t unHostPort);
		bool Connect(ulong_t ulHostIP, uint16_t unHostPort);
		
		/**
		 * @brief 监听连接请求.
		 * @param [in] nConnectionBacklog : Defaults to 5.
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Listen(int32_t nConnectionBacklog = 5);

		/**
		 * @brief 绑定端口和IP.
		 * @param [in] unSocketPort : 端口
		 * @param [in] strSocketAddress : Defaults to "".
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Bind(uint16_t unSocketPort, const VString &strSocketAddress = "");

		/**
		 * @brief 接受新连接.
		 * @param [out] sockClient : 返回新套接字对象
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool Accept(VSocket &sockClient);

		/**
		 * @brief 接收数据.
		 * @param [in] pBuffer : 数据缓冲区
		 * @param [in] nBufLen : 缓冲区大小
		 * @return 接收到的数据大小  
		 */
		int32_t Recv(uchar_t *pBuffer, int32_t nBufLen);

		/**
		 * @brief 发送数据.
		 * @param [in] pBuffer : 数据缓冲区
		 * @param [in] nBufLen : 缓冲区大小
		 * @return 发送的数据大小  
		 */
		int32_t Send(uchar_t *pBuffer, int32_t nBufLen);

		/**
		 * @brief 接收数据.
		 * @param [in] pBuffer : 数据缓冲区
		 * @param [in] nBufLen : 缓冲区大小
		 * @param [in] strHostAddress : 接收服务器IP地址
		 * @param [in] unHostPort : 接收的服务器端口
		 * @return 接收到的数据大小  
		 */
		int32_t RecvFrom(uchar_t *pBuffer, int32_t nBufLen, const VString &strHostAddress, uint16_t unHostPort);

		/**
		 * @brief 发送数据.
		 * @param [in] pBuffer : 数据缓冲区
		 * @param [in] nBufLen : 缓冲区大小
		 * @param [in] strHostAddress : 发送到的服务器IP地址
		 * @param [in] unHostPort : 发送到的服务器对应端口
		 * @return 发送的数据大小  
		 */
		int32_t SendTo(uchar_t *pBuffer, int32_t nBufLen, const VString &strHostAddress, uint16_t unHostPort);

		/**
		 * @brief 套接字能否写.
		 * @return 可写返回true，否则返回false.  
		 */
		bool CanWrite() const;

		/**
		 * @brief 套接字能否读.
		 * @return 有数据可读返回true，否则返回false.  
		 */
		bool CanRead() const;

		/**
		 * @brief 套接字是否有异常.
		 * @return 有异常返回true，否则返回false.  
		 */
		bool HasExcept() const;

		/**
		 * @brief 设置为非阻塞套接字.
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool SetNonBlocking();

		/**
		 * @brief 重置套接字及其状态
		 */
		void Reset();

		/**
		 * @brief 设置系统发送缓冲区大小.
		 * @param [in] nSize : 缓冲区大小
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool SetSendBufferSize(int32_t nSize);

		/**
		 * @brief 设置系统接收缓冲区大小.
		 * @param [in] nSize : 换红区大熊啊
		 * @return 函数调用成功返回true，否则返回false.
		 */
		bool SetRecvBufferSize(int32_t nSize);

		/**
		 * @brief 设置是否可重用端口.
		 * @param [in] bReuse : reuse
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool SetReuseAddress(bool bReuse);

		/**
		 * @brief 获取本地ip和端口.
		 * @param [out] rSockName : ip
		 * @param [out] rSockPort : 端口
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool GetLocalName(VString &rSockName, uint16_t &rSockPort) const;

		/**
		 * @brief 获取对端ip和端口.
		 * @param [in] rPeerName : ip
		 * @param [in] rPeerPort : 端口
		 * @return 函数调用成功返回true，否则返回false.  
		 */
		bool GetPeerName(VString &rPeerName, uint16_t &rPeerPort) const;

		/**
		 * @brief 获取系统错误码.
		 * @return 返回系统错误码  
		 */
		uint32_t GetErrorCode() const;

		/**
		 * @brief 获取socket错误码.
		 * @return 返回socket错误码
		 */
		uint32_t GetSocketError() const;

		/**
		 * @brief 获取原始套接字描述符
		 */
		SOCKET GetSocketFD() const	{ return m_Socket; }

		/**
		 * @brief DNS同步解析.
		 * @param [in] strDomain : 域名
		 * @return 返回字符串形式的IP地址 
		 */
		static VString GetHostByName(const VString &strDomain);

		/**
		 * @brief DNS同步解析.
		 * @param [in] strDomain : 域名
		 * @return 返回的整型IP地址  
		 */
		static ulong_t DNS(const VString &strDomain);

		/**
		 * @brief 判断字符串是否是域名.
		 * @param [in] strDomain : 字符串
		 * @return 如果是域名格式返回true
		 */
		static bool IsDomain(const VString &strDomain);

	protected:
		bool Startup(int32_t nVersionH, int32_t nVersionL);
		bool Cleanup();

		SOCKET	m_Socket;
		static int32_t	m_nCount;
	};
}


#endif	/*__VISION_SOCKET_H__*/
