

#ifndef __VISION_OBJECT_ALLOCATOR_H__
#define __VISION_OBJECT_ALLOCATOR_H__


#include "VType.h"
#include "VMacro.h"


namespace VPlatform
{
	class VPoolObject;

	/**
	 * @brief 对象内存分配器
	 */
	class VPLATFORM_API VObjectAllocator
	{
		V_DECLARE_INTERFACE(VObjectAllocator)

	public:
		/** 返回单个对象大小 */
		virtual size_t sizeOfObject() const = 0;

		/** 分配堆空间 */
		virtual void *allocHeap(size_t nSize) = 0;

		/** 释放堆空间 */
		virtual void freeHeap(void *pHeap) = 0;

		/** 创建对象 */
		virtual VPoolObject *createObject(void *pHeap) = 0;

		/** 销毁对象 */
		virtual void destroyObject(VPoolObject *pObject) = 0;
	};
}



#endif	/*__VISION_OBJECT_ALLOCATOR_H__*/
