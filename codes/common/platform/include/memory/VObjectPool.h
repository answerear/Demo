

#ifndef __VISION_OBJECT_POOL_H__
#define __VISION_OBJECT_POOL_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"
#include <mutex>

namespace VPlatform
{
	class VPoolObject;
	class VObjectAllocator;
	class VMutex;
	class VObjectList;

	class VPLATFORM_API VObjectPool
	{
	protected:
		struct HeapBlock
		{
			size_t		m_nMaxObjects;		/// 当前堆内存块可以存放最大对象数量
			size_t		m_nUsedObjects;		/// 记录堆使用对象的个数
			HeapBlock	*m_pPrev;			/// 上一块堆块信息
			HeapBlock	*m_pNext;			/// 下一块堆块信息
			char		m_pHeap[1];			/// 可分配内存首地址
		};

	public:
		static const size_t POOL_INFINITE;

	public:
		/**
		 * @brief Constructor
		 * @param [in] nMinCapacity : 初始化和最小容量
		 * @param [in] nMaxCapacity : 最大容量
		 * @param [in] creator : 创建函数对象 
		 * @param [in] bAutoAdjust : 是否自动释放内存
		 * @param [in] bHasLocker : 是否加锁
		 */
		VObjectPool(size_t nMinCapacity, size_t nMaxCapacity, VObjectAllocator *pAllocator, uint64_t ullAutoreleaseInterval = 0, bool bHasLocker = false);

		/**
		 * @brief Destructor
		 */
		virtual ~VObjectPool();
	
		/**
		 * @brief 从对象池分配对象
		 * @return 返回一个对象
		 * @note 如果对象是从池中复用的，会调用VObjectPool::reset接口重置；
		 *			如果对象是新分配的，直接调用创建函数对象QGObjectCreator创建对象
		 */
		VPoolObject *allocateObject();

		/**
		 * @brief 释放对象回对象池中
		 */
		void releaseObject(VPoolObject *pObject);

		/**
		 * @brief 还原成初始状态
		 */
		void reset();

		/**
		 * @brief 获取最小容量
		 */
		size_t getMinCapacity() const	{ return m_nMinCapacity; }

		/**
		 * @brief 获取最大容量
		 */
		size_t getMaxCapacity() const	{ return m_nMaxCapacity; }

		size_t getFreeCount() const;

		size_t getUsedCount() const;

	protected:
		/** 分配内存堆空间 */
		HeapBlock *allocateHeapBlock();
		/** 释放内存堆空间 */
		void releaseHeapBlock(HeapBlock *pBlock);

		/** 从堆中分配对象 */
		void allocateObjects(HeapBlock *pBlock);
		/** 从对中释放对象 */
		void releaseObjects(HeapBlock *pBlock);

		/** 申请对象并且放入空闲链表 */
		HeapBlock *allocateObjects();
		/** 回收使用对象，并且放入空闲链表 */
		void recycleObjects();
		/** 自动释放多余对象 */
		void autoReleaseObjects();

		void releaseAllObjects();

		void lock();
		void unlock();

	protected:
		uint64_t	m_ullAutoreleaseInterval;	/// 释放资源间隔
		uint64_t	m_ullLastTimestamp;			/// 上一次释放内存时间戳

		size_t	m_nMinCapacity;				/// 初始化和最小容量大小
		size_t	m_nMaxCapacity;				/// 最大容量

		size_t	m_nBlockCount;				/// 内存块数量

		VObjectList	*m_pFreeList;			/// 空闲对象链表
		VObjectList	*m_pUsedList;			/// 使用中对象链表

		HeapBlock	*m_pHeapHead;			/// 内存块链表头指针
		HeapBlock	*m_pHeapTail;			/// 内存块链表尾指针

		VObjectAllocator	*m_pObjectAllocator;	/// 对象分配器

		std::recursive_mutex	m_mutex;
		bool		m_bHasLocker;
// 		VMutex		*m_pMutex;
	};
}


#endif	/*__VISION_OBJECT_POOL_H__*/
