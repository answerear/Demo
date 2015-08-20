﻿

#include "VDirAdapter.h"
#include <direct.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#pragma warning(disable:4244)
#pragma warning(disable:4996)

namespace VPlatform
{
	VDirAdapter::VDirAdapter()
		: m_hFindFile(INVALID_HANDLE_VALUE)
		, m_bExtractName(false)
	{
		memset(&m_FindFileData, 0, sizeof(m_FindFileData));
	}

	VDirAdapter::~VDirAdapter()
	{
		close();
	}

	bool VDirAdapter::findFile(const VString &strPath)
	{
		if (strPath.empty() || strPath == "")
			return false;

#ifdef UNICODE
		WCHAR wszPath[512] = {0};
		::MultiByteToWideChar(CP_UTF8, 0, strPath.c_str(), strPath.length(), wszPath, sizeof(wszPath));
		m_hFindFile = ::FindFirstFile(wszPath, &m_FindFileData);
#else
		m_hFindFile = ::FindFirstFile(strPath.c_str(), &m_FindFileData);
#endif
		
		extractRoot(strPath, m_strRoot);

		m_bExtractName = false;

		return (m_hFindFile != INVALID_HANDLE_VALUE);
	}

	bool VDirAdapter::findNextFile()
	{
		BOOL bResult = FALSE;

		if (m_hFindFile != NULL)
		{
			bResult = ::FindNextFile(m_hFindFile, &m_FindFileData);
			m_bExtractName = false;
		}

		return (bResult == TRUE);
	}

	void VDirAdapter::close()
	{
		if (m_hFindFile != NULL)
		{
			::FindClose(m_hFindFile);
			m_hFindFile = INVALID_HANDLE_VALUE;

			memset(&m_FindFileData, 0, sizeof(m_FindFileData));
			m_bExtractName = false;
		}
	}

	VString VDirAdapter::getRoot() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return "";

		return m_strRoot;
	}

	VString VDirAdapter::getFileName() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return "";

		if (!m_bExtractName)
		{
#ifdef UNICODE
			char szPath[512] = {0};
			::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szPath, sizeof(szPath), nullptr, nullptr);
			VString strFilePath(szPath);
#else
			VString strFilePath = m_FindFileData.cFileName;
#endif
			extractFileName(strFilePath, m_strName, m_strTitle);
		}

		return m_strName;
	}

	VString VDirAdapter::getFilePath() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return "";

#ifdef UNICODE
		char szPath[512] = {0};
		::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szPath, sizeof(szPath), nullptr, nullptr);
		VString strPath(szPath);
#else
		VString strPath = m_FindFileData.cFileName;
#endif

		if (!m_bExtractName)
		{
			extractFileName(strPath, m_strName, m_strTitle);
		}

		return m_strRoot + strPath;
	}

	VString VDirAdapter::getFileTitle() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return "";

		if (!m_bExtractName)
		{
#ifdef UNICODE
			char szPath[512] = {0};
			::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szPath, sizeof(szPath), nullptr, nullptr);
			VString strFilePath(szPath);
#else
			VString strFilePath = m_FindFileData.cFileName;
#endif
			extractFileName(strFilePath, m_strName, m_strTitle);
		}

		return m_strTitle;
	}

	UINT VDirAdapter::getLength() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return 0;

		return m_FindFileData.nFileSizeLow;
	}

	bool VDirAdapter::isDots() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return false;

		if (!m_bExtractName)
		{
#ifdef UNICODE
			char szPath[512] = {0};
			::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szPath, sizeof(szPath), nullptr, nullptr);
			VString strPath(szPath);
#else
			VString strPath = m_FindFileData.cFileName;
#endif
			extractFileName(strPath, m_strName, m_strTitle);
		}

		return ((m_FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (m_strName == "." || m_strName == ".."));
	}

	bool VDirAdapter::isDirectory() const
	{
		return (m_hFindFile != INVALID_HANDLE_VALUE && (m_FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
	}

	long VDirAdapter::getCreationTime() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return 0;

		struct _stat buffer;
#ifdef UNICODE
		char szFileName[MAX_PATH] = {0};
		::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szFileName, sizeof(szFileName), nullptr, nullptr);
		int result = _stat(szFileName, &buffer);
#else
		int result = _stat(m_FindFileData.cFileName, &buffer);
#endif
		if (result == 0)
		{
			return buffer.st_ctime;
		}

		return 0;
	}

	long VDirAdapter::getLastAccessTime() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return 0;

		struct _stat buffer;
#ifdef UNICODE
		char szFileName[MAX_PATH] = {0};
		::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szFileName, sizeof(szFileName), nullptr, nullptr);
		int result = _stat(szFileName, &buffer);
#else
		int result = _stat(m_FindFileData.cFileName, &buffer);
#endif
		if (result == 0)
		{
			return buffer.st_atime;
		}

		return 0;
	}

	long VDirAdapter::getLastWriteTime() const
	{
		if (m_hFindFile == INVALID_HANDLE_VALUE)
			return 0;

		struct _stat buffer;
#ifdef UNICODE
		char szFileName[MAX_PATH] = {0};
		::WideCharToMultiByte(CP_UTF8, 0, m_FindFileData.cFileName, MAX_PATH, szFileName, sizeof(szFileName), nullptr, nullptr);
		int result = _stat(szFileName, &buffer);
#else
		int result = _stat(m_FindFileData.cFileName, &buffer);
#endif
		if (result == 0)
		{
			return buffer.st_mtime;
		}

		return 0;
	}

	bool VDirAdapter::makeDir(const VString &strDir)
	{
		if (strDir.empty() || strDir == "")
			return false;

		return (mkdir(strDir.c_str()) == 0);
	}

	bool VDirAdapter::removeDir(const VString &strDir)
	{
		if (strDir.empty() || strDir == "")
			return false;

		return (rmdir(strDir.c_str()) == 0);
	}

	bool VDirAdapter::remove(const VString &strFileName)
	{
		if (strFileName.empty() || strFileName == "")
			return false;

		return (remove(strFileName.c_str()) == 0);
	}

	bool VDirAdapter::exists(const VString &strPath) const
	{
		return true;
	}

	VString VDirAdapter::getCachePath() const
	{
		char szBuf[MAX_PATH];
#ifdef UNICODE
		WCHAR wszBuf[MAX_PATH];
		::GetModuleFileName(NULL, wszBuf, sizeof(wszBuf));
		::WideCharToMultiByte(CP_UTF8, 0, wszBuf, MAX_PATH, szBuf, sizeof(szBuf), nullptr, nullptr);
#else
		::GetModuleFileName(NULL, szBuf, sizeof(szBuf));
#endif
		char *ptr = szBuf;
		while (strchr(ptr, '\\'))
		{
			ptr = strchr(ptr, '\\');
			ptr++;
		}
		*ptr = 0;

		return VString(szBuf);
	}

	VString VDirAdapter::getAppPath() const
	{
		return getCachePath();
	}

	char VDirAdapter::getNativeSeparator() const
	{
		return '\\';
	}

	bool VDirAdapter::extractRoot(const VString &strFilePath, VString &strRoot)
	{
		bool bResult = false;
		size_t nPos = strFilePath.rfind("/");

		if (nPos == -1)
		{
			nPos = strFilePath.rfind("\\");
		}

		if (nPos != -1)
		{
			bResult = true;
			size_t nCount = nPos + 1;
			size_t nOffset = 0;
			strRoot = strFilePath.substr(nOffset, nCount);
		}
		else
		{
			bResult = false;
		}

		return bResult;
	}

	bool VDirAdapter::extractFileName(const VString &strFilePath, VString &strName, VString &strTitle) const
	{
		bool bResult = false;
		size_t nLength = strFilePath.length();

		strName = strFilePath;

		size_t nPos = strName.rfind(".");
		size_t nCount = nPos;
		size_t nOffset = 0;
		if (nPos == 0)
			strTitle = "";
		else
			strTitle = strFilePath.substr(nOffset, nCount);

		m_bExtractName = true;

		return bResult;
	}


}
