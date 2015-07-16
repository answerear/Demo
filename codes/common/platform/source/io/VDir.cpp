/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VDir.cpp
 * @brief   操作系统平台无关的枚举搜索路径文件类实现.
 * @author  aaronwang
 * @date    2014/2/9 22:50:44
 * @version v1.00
 **************************************************************************************************/

#include "VDir.h"
#include "IAdapterFactory.h"
#include "IDirAdapter.h"
#include "VSystem.h"
#include "VType.h"


namespace VPlatform
{
	IDirAdapter *VDir::s_pDirAdapter = NULL;

	char VDir::NATIVE_SEPARATOR = 0;

	VDir::VDir()
	{
		m_pDirAdpater = V_ADAPTER_FACTORY.createDirAdapter();
	}

	VDir::~VDir()
	{
		V_SAFE_DELETE(m_pDirAdpater);
	}

	bool VDir::findFile(const VString &strPath)
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->findFile(strPath);
		}

		return false;
	}

	bool VDir::findNextFile()
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->findNextFile();
		}

		return false;
	}

	void VDir::close()
	{
		if (m_pDirAdpater != NULL)
		{
			m_pDirAdpater->close();
		}
	}

	VString VDir::getRoot() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getRoot();
		}

		return "";
	}

	VString VDir::getFileName() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getFileName();
		}
		
		return "";
	}

	VString VDir::getFilePath() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getFilePath();
		}

		return "";
	}

	VString VDir::getFileTitle() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getFileTitle();
		}

		return "";
	}

	uint32_t VDir::getFileSize() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getLength();
		}

		return 0;
	}

	bool VDir::isDots() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->isDots();
		}

		return false;
	}

	bool VDir::isDirectory() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->isDirectory();
		}

		return false;
	}

	long_t VDir::getCreationTime() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getCreationTime();
		}

		return 0;
	}

	long_t VDir::getLastAccessTime() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getLastAccessTime();
		}

		return 0;
	}

	long_t VDir::getLastWriteTime() const
	{
		if (m_pDirAdpater != NULL)
		{
			return m_pDirAdpater->getLastWriteTime();
		}

		return 0;
	}

	bool VDir::makeDir(const VString &strDir)
	{
		if (NULL == s_pDirAdapter)
			s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

		if (s_pDirAdapter != NULL)
		{
			return s_pDirAdapter->makeDir(strDir);
		}

		return false;
	}

	bool VDir::removeDir(const VString &strDir)
	{
		if (NULL == s_pDirAdapter)
			s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

		if (s_pDirAdapter != NULL)
		{
			return s_pDirAdapter->removeDir(strDir);
		}

		return false;
	}

	bool VDir::remove(const VString &strFileName)
	{
		if (NULL == s_pDirAdapter)
			s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

		if (s_pDirAdapter != NULL)
		{
			return s_pDirAdapter->remove(strFileName);
		}

		return false;
	}

	bool VDir::exists(const VString &strPath)
	{
		if (NULL == s_pDirAdapter)
			s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

		if (s_pDirAdapter != NULL)
		{
			return s_pDirAdapter->exists(strPath);
		}

		return false;
	}

	VString VDir::getCachePath()
	{
		if (NULL == s_pDirAdapter)
			s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

		if (s_pDirAdapter != NULL)
		{
			return s_pDirAdapter->getCachePath();
		}

		return "";
	}

	VString VDir::getAppPath()
	{
		if (NULL == s_pDirAdapter)
			s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

		if (s_pDirAdapter != NULL)
		{
			return s_pDirAdapter->getAppPath();
		}

		return "";
	}

	char VDir::getNativeSeparator()
	{
		if (NATIVE_SEPARATOR == 0)
		{
			if (NULL == s_pDirAdapter)
				s_pDirAdapter = V_ADAPTER_FACTORY.createDirAdapter();

			if (s_pDirAdapter != NULL)
			{
				NATIVE_SEPARATOR = s_pDirAdapter->getNativeSeparator();
			}
		}
		
		return NATIVE_SEPARATOR;
	}
}

