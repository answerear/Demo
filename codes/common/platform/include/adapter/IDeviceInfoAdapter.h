

#ifndef __VISION_DEVICE_INFO_ADAPTER_H__
#define __VISION_DEVICE_INFO_ADAPTER_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform
{
	class IDeviceInfoAdapter
	{
		V_DECLARE_INTERFACE(IDeviceInfoAdapter);

	public:
		enum EPlatform
		{
			E_PLATFORM_UNKNOWN = 0,
			E_PLATFORM_WIN32,
			E_PLATFORM_IOS,
			E_PLATFORM_ANDROID,
		};

	public:
		/**
		 * @brief 获取平台类型
		 */
		virtual EPlatform getPlatform() const = 0;
		
		/**
		 * @brief 获取软件版本号字符串
		 */
		virtual VString getSoftwareVersion() const = 0;

		/**
		 * @brief 获取操作系统版本号字符串
		 */
		virtual VString getOSVersion() const = 0;

		/**
		 * @brief 获取设备机型版本信息字符串
		 */
		virtual VString getDeviceVersion() const = 0;

		/**
		 * @brief 获取屏幕宽度.  
		 */
		virtual int32_t getScreenWidth() const = 0;

		/**
		 * @brief 获取屏幕高度.  
		 */
		virtual int32_t getScreenHeight() const = 0;

		/**
		 * @brief 获取屏幕像素密度.
		 */
		virtual float getScreenDPI() const = 0;

		/**
		 * @brief 获取设备mac地址.  
		 */
		virtual VString getMacAddress() const = 0;

		/**
		 * @brief 获取CPU类型信息.  
		 */
		virtual VString getCPUType() const = 0;

		/**
		 * @brief 获取CPU核数.
		 */
		virtual int32_t getNumberOfProcessors() const = 0;

		/**
		 * @brief 获取内存信息.  
		 */
		virtual uint32_t getMemoryCapacity() const = 0;

		/**
		 * @brief 获取设备ID.  
		 */
		virtual VString getDeviceID() const = 0;
	};
}


#endif	/*__QQGAME_DEVICE_INFO_ADAPTER_H__*/
