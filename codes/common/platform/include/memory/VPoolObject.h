

#ifndef __VISION_POOL_OBJECT_H__
#define __VISION_POOL_OBJECT_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"


namespace VPlatform
{
	class VPLATFORM_API VPoolObject
	{
		friend class VObjectList;
		friend class VObjectPool;

	public:
		VPoolObject();
		virtual ~VPoolObject();

		/**
		 * @brief 对象被重新复用时被调用
		 */
		virtual void onReused() = 0;
		
		/**
		 * @brief 对象被回收时被调用
		 * @param bOutOfMemory [in] : true表示对象池内存满了，需要回收当前这个最老的对象；
		 *								false表示是外部调用对象池回收对象
		 * @return 当bOutOfMemory为true时，返回true，就表示允许对象池回收，返回false不允许回收。
		 *		如果允许回收，回收时将不再调用onRecycled()，所以这里派生类需要同时处理被回收的事情。
		 *		当bOutOfMemory为false时，返回值会被忽略，对象直接被回收.
		 * @note 当bOutOfMemory为true时，如果返回值是true，那么需要从对象池新分配的对象将无法获得
		 */
		virtual bool onRecycled(bool bOutOfMemory) = 0;

	private:
		void		*_pList;
		void		*_pBlock;
		VPoolObject	*_pPrevObj;
		VPoolObject	*_pNextObj;
	};
}



#endif	/*__VISION_POOL_OBJECT_H__*/
