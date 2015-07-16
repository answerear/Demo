//
//  VDirAdapter_Unix.cpp
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#include "VDirAdapter_Unix.h"
#include <sys/stat.h>
#include <unistd.h>


namespace VPlatform
{
    VDirAdapter_Unix::VDirAdapter_Unix()
    {
        
    }
    
    VDirAdapter_Unix::~VDirAdapter_Unix()
    {
        
    }
    
    bool VDirAdapter_Unix::findFile(const VString &strPath)
	{
        if (strPath.empty() || strPath == "")
        {
            return false;
        }
        
        extractRoot(strPath, m_strRoot);
        extractExt(strPath, m_strExt);
        m_pDir = opendir(m_strRoot.c_str());
        m_bExtractName = false;
        
		return (m_pDir != NULL);
	}
    
	bool VDirAdapter_Unix::findNextFile()
	{
        if (NULL == m_pDir)
        {
            return false;
        }
        
        m_pDirent = readdir(m_pDir);
        if (m_pDirent != NULL && !isDirectory())
        {
            VString strName = m_pDirent->d_name;
            VString strExt;
            extractExt(strName, strExt);
            if (strExt != m_strExt && m_strExt != "*" && m_strExt != "")
                findNextFile();
        }
        
        m_bExtractName = false;
        
		return (m_pDirent != NULL);
	}
    
	void VDirAdapter_Unix::close()
	{
        if (NULL == m_pDir)
        {
            return;
        }
        
        closedir(m_pDir);
        m_pDir = NULL;
        m_pDirent = NULL;
        m_bExtractName = false;
	}
    
	VString VDirAdapter_Unix::getRoot() const
	{
        if (NULL == m_pDir)
            return "";
        
		return m_strRoot;
	}
    
	VString VDirAdapter_Unix::getFileName() const
	{
        if (NULL == m_pDir || NULL == m_pDirent)
            return "";
        
        if (!m_bExtractName)
        {
            VString strFilePath = m_pDirent->d_name;
            extractFileName(strFilePath, m_strName, m_strTitle);
        }
        
		return m_strName;
	}
    
	VString VDirAdapter_Unix::getFilePath() const
	{
        if (NULL == m_pDir || NULL == m_pDirent)
            return "";
        
        VString strPath = m_pDirent->d_name;
        
        if (!m_bExtractName)
        {
            extractFileName(strPath, m_strName, m_strTitle);
        }
        
		return m_strRoot + strPath;
	}
    
	VString VDirAdapter_Unix::getFileTitle() const
	{
        if (NULL == m_pDir || NULL == m_pDirent)
            return "";
        
        if (!m_bExtractName)
        {
            VString strPath = m_pDirent->d_name;
            extractFileName(strPath, m_strName, m_strTitle);
        }
        
		return m_strTitle;
	}
    
	uint32_t VDirAdapter_Unix::getLength() const
	{
        VString strPath = m_strRoot + VString(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        
		return (result == 0 ? s.st_size : 0);
	}
    
	bool VDirAdapter_Unix::isDots() const
	{
        if (NULL == m_pDir || NULL == m_pDirent)
            return false;
        
		return (strcmp(m_pDirent->d_name, ".") == 0 || strcmp(m_pDirent->d_name, "..") == 0);
	}
    
	bool VDirAdapter_Unix::isDirectory() const
	{
        if (NULL == m_pDir || NULL == m_pDirent)
            return false;
        
        VString strPath = m_strRoot + VString(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        
		return (result == 0 && S_ISDIR(s.st_mode));
	}
    
	bool VDirAdapter_Unix::makeDir(const VString &strDir)
	{
        if (strDir.empty() || strDir == "")
            return false;
        
		return (mkdir(strDir.c_str(), S_IRWXU) == 0);
	}
    
    bool VDirAdapter_Unix::removeDir(const VString &strDir)
    {
        if (strDir.empty() || strDir == "")
            return false;
        
        return (rmdir(strDir.c_str()) == 0);
    }
    
    bool VDirAdapter_Unix::remove(const VString &strFileName)
    {
        if (strFileName.empty() || strFileName == "")
            return false;
        
        return (remove(strFileName.c_str()) == 0);
    }
    
    bool VDirAdapter_Unix::exists(const VString &strPath) const
    {
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        return (result == 0);
    }
    
    char VDirAdapter_Unix::getNativeSeparator() const
    {
    	return '/';
    }
    
    bool VDirAdapter_Unix::extractRoot(const VString &strPath, VString &strRoot)
    {
        bool bResult = false;
        size_t nPos = strPath.rfind("/");
        
        if (nPos == -1)
        {
            nPos = strPath.rfind("\\");
        }
        
        if (nPos != -1)
        {
            bResult = true;
            size_t nCount = nPos + 1;
            size_t nOffset = 0;
            strRoot = strPath.substr(nOffset, nCount);
        }
        else
        {
            bResult = false;
        }
        
        return bResult;
    }
    
    bool VDirAdapter_Unix::extractExt(const VString &strName, VString &strExt)
    {
        bool bResult = false;
        
        size_t nPos = strName.rfind(".");
        
        if (nPos != -1)
        {
            bResult = true;
            size_t nLength = strName.length();
            size_t nCount = nLength - nPos - 1;
            size_t nOffset = nPos + 1;
            strExt = strName.substr(nOffset, nCount);
        }
        else
        {
            bResult = false;
        }
        
        return bResult;
    }
    
    bool VDirAdapter_Unix::extractFileName(const VString &strPath, VString &strName, VString &strTitle) const
    {
        bool bResult = false;
        
        strName = strPath;
        
        size_t nPos = strName.rfind(".");
        size_t nCount = nPos;
        size_t nOffset = 0;
        if (nPos == 0)
            strTitle = "";
        else
            strTitle = strPath.substr(nOffset, nCount);
        
        m_bExtractName = true;
        
        return bResult;
    }
}
