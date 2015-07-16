//
//  VDirAdapter.cpp
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#include "VDirAdapter.h"
#include <sys/stat.h>
#include <unistd.h>


namespace VPlatform
{
    VDirAdapter::VDirAdapter()
    {
        
    }
    
    VDirAdapter::~VDirAdapter()
    {
        
    }
    
    long VDirAdapter::getCreationTime() const
	{
        if (NULL == m_pDir || NULL == m_pDirent)
            return false;
        
        std::string strPath = m_strRoot + std::string(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        
		return (result == 0 ? s.st_ctimespec.tv_sec : 0);
	}
    
	long VDirAdapter::getLastAccessTime() const
	{
		if (NULL == m_pDir || NULL == m_pDirent)
            return false;
        
        std::string strPath = m_strRoot + std::string(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        
		return (result == 0 ? s.st_atimespec.tv_sec : 0);
	}
    
	long VDirAdapter::getLastWriteTime() const
	{
		if (NULL == m_pDir || NULL == m_pDirent)
            return false;
        
        std::string strPath = m_strRoot + std::string(m_pDirent->d_name);
        struct stat s;
        int result = stat(strPath.c_str(), &s);
        
        return (result == 0 ? s.st_mtimespec.tv_sec : 0);
	}
    
    VString VDirAdapter::getCachePath() const
    {
        if (m_strCachePath.empty() || m_strCachePath == "")
        {
            char szFilePath[260] = {0};
            NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
            
            if ([paths count] > 0)
            {
                NSString *cachePath = [paths objectAtIndex:0];
                snprintf(szFilePath, sizeof(szFilePath)-1, "%s", [cachePath UTF8String]);
            }
            
            [pool release];
            
            m_strCachePath = VString(szFilePath) + VString("/");
        }
        
        return m_strCachePath;
    }
	
	VString VDirAdapter::getAppPath() const
	{
		if (m_strDocPath.empty() || m_strDocPath == "")
		{
			char szFilePath[260] = {0};
			NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
            
            if ([paths count] > 0)
            {
                NSString *cachePath = [paths objectAtIndex:0];
                snprintf(szFilePath, sizeof(szFilePath)-1, "%s", [cachePath UTF8String]);
            }
            
            [pool release];
            
            m_strDocPath = VString(szFilePath) + VString("/");
		}
		
		return m_strDocPath;
	}
}

