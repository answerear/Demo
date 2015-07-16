//
//  VAdapterFactory.cpp
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#include "VAdapterFactory.h"
#include "VConsoleAdapter.h"
#include "VDirAdapter.h"
#include "VApnAdapter.h"
#include "VTimerAdapter.h"
#include "VAudioAdapter.h"


namespace VPlatform
{
    IAdapterFactory *createAdapterFactory()
    {
        return new VAdapterFactory();
    }
    
    VAdapterFactory::VAdapterFactory()
    {
        
    }
    
    VAdapterFactory::~VAdapterFactory()
    {
        
    }
    
    IConsoleAdapter *VAdapterFactory::createConsoleAdapter()
    {
        return new VConsoleAdapter();
    }
    
    ITimerAdapter *VAdapterFactory::createTimerAdapter()
    {
        return new VTimerAdapter();
    }
    
    IDirAdapter *VAdapterFactory::createDirAdapter()
    {
        return new VDirAdapter();
    }
    
    IApnAdapter *VAdapterFactory::createApnAdapter()
    {
        return new VApnAdapter();
    }
    
    IAudioAdapter *VAdapterFactory::createAudioAdapter()
    {
        return new VAudioAdapter();
    }
	
	EPlatform VAdapterFactory::getPlatform()
	{
		return E_PLATFORM_IOS;
	}
}

