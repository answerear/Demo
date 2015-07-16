

#ifndef __VISION_DEVICE_INFO_ADAPTER_WIN32_H__
#define __VISION_DEVICE_INFO_ADAPTER_WIN32_H__


#include "IDeviceInfoAdapter.h"


namespace VPlatform
{
	class VDeviceInfoAdapter : public IDeviceInfoAdapter
	{
		V_DISABLE_COPY(VDeviceInfoAdapter);

	public:
		VDeviceInfoAdapter();
		virtual ~VDeviceInfoAdapter();

		/**
		 * @brief 获取平台类型
		 */
		virtual EPlatform getPlatform() const;
		
		/**
		 * @brief 获取软件版本号字符串
		 */
		virtual VString getSoftwareVersion() const;

		/**
		 * @brief 获取操作系统版本号字符串
		 */
		virtual VString getOSVersion() const;

		/**
		 * @brief 获取设备机型版本信息字符串
		 */
		virtual VString getDeviceVersion() const;

		/**
		 * @brief 获取屏幕宽度.  
		 */
		virtual int32_t getScreenWidth() const;

		/**
		 * @brief 获取屏幕高度.  
		 */
		virtual int32_t getScreenHeight() const;

		/**
		 * @brief 获取屏幕像素密度.
		 */
		virtual float getScreenDPI() const;

		/**
		 * @brief 获取设备mac地址.  
		 */
		virtual VString getMacAddress() const;

		/**
		 * @brief 获取CPU类型信息.  
		 */
		virtual VString getCPUType() const;

		/**
		 * @brief 获取CPU核数
		 */
		virtual int32_t getNumberOfProcessors() const;

		/**
		 * @brief 获取内存信息.  
		 */
		virtual uint32_t getMemoryCapacity() const;

		/**
		 * @brief 获取设备ID.  
		 */
		virtual VString getDeviceID() const;
	};
}


#endif	/*__VISION_DEVICE_INFO_ADAPTER_WIN32_H__*/
