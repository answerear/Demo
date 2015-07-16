//
//  VDirAdapter.h
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#ifndef __QQGAME_DIR_ADAPTER_IOS_H__
#define __QQGAME_DIR_ADAPTER_IOS_H__


#include "VDirAdapter_Unix.h"


namespace VPlatform
{
    class VDirAdapter : public VDirAdapter_Unix
    {
        V_DISABLE_COPY(VDirAdapter);
        
    public:
        VDirAdapter();
        virtual ~VDirAdapter();
        
    protected:
        virtual long getCreationTime() const;
		virtual long getLastAccessTime() const;
		virtual long getLastWriteTime() const;
        
        virtual VString getCachePath() const;
		virtual VString getAppPath() const;
        
    protected:
        mutable VString m_strCachePath;
		mutable VString m_strDocPath;
    };
}


#endif  /*__QQGAME_DIR_ADAPTER_IOS_H__*/

