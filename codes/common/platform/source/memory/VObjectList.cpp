

#include "VObjectList.h"
#include "VPoolObject.h"


namespace VPlatform
{
	VObjectList::VObjectList(bool bLocker/* = false */)
		: m_pHead(NULL)
		, m_pTail(NULL)
		, m_nSize(0)
		, m_bHasLocker(bLocker)
	{
		
	}

	VObjectList::~VObjectList()
	{
		clear();
	}

	void VObjectList::lock()
	{
		if (m_bHasLocker)
			m_mutex.lock();
	}

	void VObjectList::unlock()
	{
		if (m_bHasLocker)
			m_mutex.unlock();
	}

	size_t VObjectList::realSize()
	{
		VPoolObject *pObj = m_pHead;
		size_t nCount = 0;
		while (pObj != NULL)
		{
			nCount++;
			pObj = pObj->_pNextObj;
		}
		return nCount;
	}

	void VObjectList::clear()
	{
		lock();
		VPoolObject *pObj = m_pHead;
		
		while (pObj != NULL)
		{
			m_pHead = pObj->_pNextObj;
			pObj->_pPrevObj = NULL;
			pObj->_pNextObj = NULL;
			pObj->_pList = NULL;
			pObj = m_pHead;
		}
		m_pHead = m_pTail = NULL;
		m_nSize = 0;
		unlock();
	}

	VPoolObject *VObjectList::take()
	{
		lock();

		VPoolObject *pObj = m_pHead;

		if (pObj != NULL)
		{
			// 非空链表
			m_pHead = m_pHead->_pNextObj;

			if (m_pHead != NULL)
			{
				m_pHead->_pPrevObj = NULL;
			}
		}

		if (m_pHead == NULL)
		{
			// 链表已经变空，首尾结点都置空
			m_pTail = NULL;
		}

		m_nSize--;

		size_t nSize = realSize();
		ASSERT(m_nSize == nSize);
		
		pObj->_pList = NULL;

		unlock();

		return pObj;
	}

	void VObjectList::put(VPoolObject *pObject)
	{
		if (pObject == NULL || pObject->_pList == this)
			return;

		lock();

		if (m_pTail == NULL)
		{
			// 空链表
			ASSERT(m_pHead == NULL);
			m_pTail = m_pHead = pObject;
			m_pHead->_pPrevObj = m_pHead->_pNextObj = NULL;
		}
		else
		{
			// 非空链表
			ASSERT(m_pTail != NULL && m_pHead != NULL);
			m_pTail->_pNextObj = pObject;
			pObject->_pPrevObj = m_pTail;
			pObject->_pNextObj = NULL;
			m_pTail = pObject;
		}

		m_nSize++;

		size_t nSize = realSize();
		ASSERT(m_nSize == nSize);

		pObject->_pList = this;

		unlock();
	}

	void VObjectList::detach(VPoolObject *pObject)
	{
		lock();

		if (pObject->_pList == this)
		{
			if (pObject->_pPrevObj == NULL && pObject->_pNextObj == NULL)
			{
				// 只有一个结点
				m_pHead = m_pTail = NULL;
			}
			else
			{
				// 链表多于一个结点
				if (m_pHead == pObject)
				{
					// 表头结点
					m_pHead = pObject->_pNextObj;
					m_pHead->_pPrevObj = NULL;
				}
				else if (m_pTail == pObject)
				{
					// 表尾结点
					m_pTail = pObject->_pPrevObj;
					m_pTail->_pNextObj = NULL;
				}
				else
				{
					// 中间结点
					pObject->_pPrevObj->_pNextObj = pObject->_pNextObj;
					pObject->_pNextObj->_pPrevObj = pObject->_pPrevObj;
				}
			}

			pObject->_pPrevObj = pObject->_pNextObj = NULL;
			m_nSize--;

			size_t nSize = realSize();
			ASSERT(m_nSize == nSize);
		}

		unlock();
	}
}


