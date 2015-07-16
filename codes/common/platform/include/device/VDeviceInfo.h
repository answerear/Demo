

#ifndef __VISION_DEVICE_INFO_H__
#define __VISION_DEVICE_INFO_H__


#include "VSingleton.h"
#include "VPlatform.h"


namespace VPlatform
{
	class IDeviceInfoAdapter;

	class VPLATFORM_API VDeviceInfo : public VSingleton<VDeviceInfo>
	{
	public:
		enum EPlatform
		{
			E_PLATFORM_UNKNOWN = 0,
			E_PLATFORM_WIN32,
			E_PLATFORM_IOS,
			E_PLATFORM_ANDROID,
		};

		static const char* Unknown;
		static const char* Windows;
		static const char* iOS;
		static const char* Android;

	public:
		VDeviceInfo();
		virtual ~VDeviceInfo();

		/**
		 * @brief 获取平台类型
		 */
		EPlatform getPlatform() const;

		/**
		 * @brief 获取平台类型字符串
		 */
		VString getPlatformString() const;

		/**
		 * @brief 获取软件版本号字符串
		 */
		VString getSoftwareVersion() const;

		/**
		 * @brief 获取操作系统版本号字符串
		 */
		VString getOSVersion() const;

		/**
		 * @brief 获取设备机型版本信息字符串
		 */
		VString getDeviceVersion() const;

		/**
		 * @brief 获取屏幕宽度.  
		 */
		int32_t getScreenWidth() const;

		/**
		 * @brief 获取屏幕高度.  
		 */
		int32_t getScreenHeight() const;

		/**
		 * @brief 获取屏幕像素密度.
		 */
		float getScreenDPI() const;

		/**
		 * @brief 获取设备mac地址.  
		 */
		VString getMacAddress() const;

		/**
		 * @brief 获取CPU类型信息.  
		 */
		VString getCPUType() const;

		/**
		 * @brief 获取CPU核数
		 */
		int32_t getNumberOfProcessors() const;

		/**
		 * @brief 获取内存信息.  
		 */
		uint32_t getMemoryCapacity() const;

		/**
		 * @brief 获取设备ID.  
		 */
		VString getDeviceID() const;

	protected:
		IDeviceInfoAdapter	*m_pDevInfoAdapter;
	};
}


#define V_DEVICE_INFO		VPlatform::VDeviceInfo::GetInstance()


#endif	/*__VISION_DEVICE_INFO_H__*/
