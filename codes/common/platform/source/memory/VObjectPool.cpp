

#include "VObjectPool.h"
#include "VObjectAllocator.h"
#include "VObjectList.h"
#include "VPoolObject.h"
#include "VMutex.h"
#include "VDateTime.h"


namespace VPlatform
{
	const size_t VObjectPool::POOL_INFINITE = 0xFFFFFFFF;

	VObjectPool::VObjectPool(size_t nMinCapacity, size_t nMaxCapacity, VObjectAllocator *pAllocator, 
		uint64_t ullAutoreleaseInterval/* = 0 */, bool bHasLocker/* = false */)
		: m_ullAutoreleaseInterval(ullAutoreleaseInterval)
		, m_ullLastTimestamp(0)
		, m_nMinCapacity(nMinCapacity)
		, m_nMaxCapacity(nMaxCapacity)
		, m_nBlockCount(0)
		, m_pFreeList(new VObjectList(bHasLocker))
		, m_pUsedList(new VObjectList(bHasLocker))
		, m_pHeapHead(NULL)
		, m_pHeapTail(NULL)
		, m_pObjectAllocator(pAllocator)
		, m_pMutex(NULL)
	{
		if (bHasLocker)
		{
			m_pMutex = new VMutex(VMutex::Recursive);
		}

		m_ullLastTimestamp = VDateTime::currentSecsSinceEpoch();
		allocateObjects();
	}

	VObjectPool::~VObjectPool()
	{
		releaseAllObjects();
		V_SAFE_DELETE(m_pMutex);
	}

	void VObjectPool::reset()
	{
		lock();
		
		HeapBlock *pBlock = m_pHeapHead->m_pNext;
		
		while (pBlock != NULL)
		{
			HeapBlock *pTemp = pBlock->m_pNext;
			releaseObjects(pBlock);
			releaseHeapBlock(pBlock);
			pBlock = pTemp;
		}

		m_nBlockCount = 1;
		m_pHeapTail = m_pHeapHead;

		unlock();
	}

	size_t VObjectPool::getFreeCount() const
	{
		size_t nCount = 0;
		if (m_pFreeList != NULL)
		{
			nCount = m_pFreeList->size();
		}
		return nCount;
	}

	size_t VObjectPool::getUsedCount() const
	{
		size_t nCount = 0;
		if (m_pUsedList != NULL)
		{
			nCount = m_pUsedList->size();
		}
		return nCount;
	}

	VPoolObject *VObjectPool::allocateObject()
	{
		VPoolObject *pObj = NULL;

		lock();

		if (m_pFreeList->isEmpty())
		{
			// 空闲链表已经没有预先分配好的对象，需要重新分配
			if (m_nMaxCapacity != POOL_INFINITE)
			{
				// 有容量上限的池
				size_t nTotalCount = m_pFreeList->size() + m_pUsedList->size();
				if (nTotalCount < m_nMaxCapacity)
				{
					// 没有到池的容量上限，继续预分配
// 					lock();
					allocateObjects();
// 					unlock();
				}
				else
				{
					// 到了池的上限，无法继续分配，看能否回收正在使用的某些对象回来复用
// 					lock();
					recycleObjects();
// 					unlock();
				}
			}
			else
			{
				// 没有容量上限的池，继续预分配
// 				lock();
				allocateObjects();
// 				unlock();
			}
		}
		
		if (!m_pFreeList->isEmpty())
		{
			// 从空闲链表获取，不用预先分配
			pObj = m_pFreeList->take();
			m_pUsedList->put(pObj);

			/// 给当前内存块占用增加一个引用计数
// 			lock();
			HeapBlock *pBlock = (HeapBlock *)pObj->_pBlock;
			pBlock->m_nUsedObjects++;
// 			unlock();
		}
		else
		{
			ASSERT(0);
		}

		unlock();

		// 回调
		if (pObj != NULL)
		{
			pObj->onReused();
		}

		return pObj;
	}

	void VObjectPool::releaseObject(VPoolObject *pObject)
	{
		if (pObject == NULL)
			return;

		// 回调
		pObject->onRecycled(false);

		lock();

		// 从使用链表拿走
		m_pUsedList->detach(pObject);

		// 加入空闲链表
		m_pFreeList->put(pObject);
		
		// 把当前对象占用的内存块减少一个对象引用计数
		HeapBlock *pBlock = (HeapBlock *)pObject->_pBlock;
		pBlock->m_nUsedObjects--;

		// 自动释放空间
		autoReleaseObjects();		
		
		unlock();
	}

	VObjectPool::HeapBlock *VObjectPool::allocateHeapBlock()
	{
		HeapBlock *pBlock = NULL;

		if (m_pObjectAllocator != NULL)
		{
			size_t nAddressSize = sizeof(void*);
			size_t s = m_pObjectAllocator->sizeOfObject();
			size_t nTotalSize = m_nMinCapacity * s;
			size_t nBlockSize = sizeof(HeapBlock) - nAddressSize + nTotalSize;

			/// 先分配大块内存
			pBlock = (HeapBlock *)m_pObjectAllocator->allocHeap(nBlockSize);

			if (pBlock != NULL)
			{
				/// 插入到内存块链表末尾
				if (m_pHeapHead == NULL)
				{
					ASSERT(m_pHeapTail == NULL);
					m_pHeapHead = m_pHeapTail = pBlock;
					pBlock->m_pPrev = NULL;
				}
				else
				{
					ASSERT(m_pHeapHead != NULL && m_pHeapTail != NULL);
					m_pHeapTail->m_pNext = pBlock;
					pBlock->m_pPrev = m_pHeapTail;
					m_pHeapTail = pBlock;
				}

				pBlock->m_nMaxObjects = m_nMinCapacity;
				pBlock->m_nUsedObjects = 0;
				pBlock->m_pNext = NULL;

				m_nBlockCount++;
			}
		}

		return pBlock;
	}

	void VObjectPool::releaseHeapBlock(HeapBlock *pBlock)
	{
		if (m_pObjectAllocator != NULL && pBlock != NULL)
		{
			pBlock->m_pPrev->m_pNext = pBlock->m_pNext;
			pBlock->m_pNext->m_pPrev = pBlock->m_pPrev;
			m_pObjectAllocator->freeHeap(pBlock);
		}
	}

	void VObjectPool::allocateObjects(HeapBlock *pBlock)
	{
		if (m_pObjectAllocator != NULL)
		{
			char *pHeap = (char *)pBlock->m_pHeap;
			size_t s = m_pObjectAllocator->sizeOfObject();
			size_t i = 0;

			for (i = 0; i < pBlock->m_nMaxObjects; ++i)
			{
				VPoolObject *pObject = m_pObjectAllocator->createObject(pHeap);
				pObject->_pBlock = pBlock;
				m_pFreeList->put(pObject);
				pHeap = pHeap + s;
			}
		}
	}

	void VObjectPool::releaseObjects(HeapBlock *pBlock)
	{
		if (m_pObjectAllocator != NULL)
		{
			char *pHeap = (char*)pBlock->m_pHeap;
			size_t s = m_pObjectAllocator->sizeOfObject();
			size_t i = 0;

			for (i = 0; i < pBlock->m_nMaxObjects; ++i)
			{
				VPoolObject *pObject = (VPoolObject *)pHeap;
				/// 先从空闲链表里面取出，再释放
				m_pFreeList->detach(pObject);
				m_pObjectAllocator->destroyObject(pObject);
				pHeap = pHeap + s;
			}
		}
	}

	VObjectPool::HeapBlock *VObjectPool::allocateObjects()
	{
		HeapBlock *pBlock = allocateHeapBlock();
		allocateObjects(pBlock);
		return pBlock;
	}

	void VObjectPool::recycleObjects()
	{
		VPoolObject *pHead = m_pUsedList->begin();
		ASSERT(pHead != NULL);
		if (pHead->onRecycled(true))
		{
			m_pUsedList->detach(pHead);
			m_pFreeList->put(pHead);
		}
	}

	void VObjectPool::autoReleaseObjects()
	{
		if (m_ullAutoreleaseInterval != 0)
		{
			/// 需要自动释放
			uint64_t ullCurrentTimestamp = VDateTime::currentSecsSinceEpoch();

			if (ullCurrentTimestamp - m_ullLastTimestamp >= m_ullAutoreleaseInterval)
			{
				HeapBlock *pBlock = m_pHeapHead->m_pNext;
				HeapBlock *pTemp = pBlock;

				while (pBlock != NULL)
				{
					pTemp = pBlock->m_pNext;

					if (pBlock->m_nUsedObjects == 0)
					{
						/// 没有使用的对象，可以释放内存块了
						pBlock->m_pPrev->m_pNext = pBlock->m_pNext;
						pBlock->m_pNext->m_pPrev = pBlock->m_pPrev;

						if (pBlock == m_pHeapTail)
						{
							m_pHeapTail = pBlock->m_pPrev;
						}

						releaseObjects(pBlock);
						releaseHeapBlock(pBlock);
						m_nBlockCount--;
					}

					pBlock = pTemp;
				}

				m_ullLastTimestamp = ullCurrentTimestamp;
			}
		}
	}

	void VObjectPool::lock()
	{
		if (m_pMutex != NULL)
			m_pMutex->lock();
	}

	void VObjectPool::unlock()
	{
		if (m_pMutex != NULL)
			m_pMutex->unlock();
	}

	void VObjectPool::releaseAllObjects()
	{
	}
}
