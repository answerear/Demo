

#include "VAutoLock.h"
#include "VMutex.h"


namespace VPlatform
{
	VAutoLock::VAutoLock(VMutex *pMutex, bool bInitLock /* = false */)
		: m_pMutex(pMutex)
	{
		if (bInitLock)
		{
			if (m_pMutex != NULL)
			{
				m_pMutex->lock();
				m_bLocked = true;
			}
		}
	}

	VAutoLock::~VAutoLock()
	{
		if (isLocked() && m_pMutex != NULL)
		{
			m_pMutex->unlock();
			m_bLocked = false;
		}
	}

	void VAutoLock::lock()
	{
		if (!isLocked() && m_pMutex != NULL)
		{
			m_pMutex->lock();
			m_bLocked = true;
		}
	}

	void VAutoLock::unlock()
	{
		if (isLocked() && m_pMutex != NULL)
		{
			m_pMutex->unlock();
			m_bLocked = false;
		}
	}
}
