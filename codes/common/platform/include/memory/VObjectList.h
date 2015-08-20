

#ifndef __VISION_OBJECT_LIST_H__
#define __VISION_OBJECT_LIST_H__


#include "VType.h"
#include "VMacro.h"
#include "VPoolObject.h"
#include <mutex>


namespace VPlatform
{
	class VMutex;

	class VObjectList
	{
	public:
		VObjectList(bool bLocker = false);
		virtual ~VObjectList();

		/** 清空链表 */
		void clear();

		/** 获取表头对象 */
		VPoolObject *begin()	{ return m_pHead; }

		/** 获取表尾对象 */
		VPoolObject *end()		{ return m_pTail; }

		/** 从链表头移除对象 */
		VPoolObject *take();

		/** 把对象放入链表尾 */
		void put(VPoolObject *pObject);

		/** 从链表中断开联系 */
		void detach(VPoolObject *pObject);

		/** 链表大小 */
		size_t size() const		{ return m_nSize; }

		/** 链表是否空 */
		bool isEmpty() const	{ return m_nSize == 0; }

	protected:
		void lock();
		void unlock();

		size_t realSize();

	protected:
		VPoolObject				*m_pHead;
		VPoolObject				*m_pTail;
		size_t					m_nSize;
		bool					m_bHasLocker;
		std::recursive_mutex	m_mutex;
	};
}



#endif	/*__VISION_OBJECT_LIST_H__*/
