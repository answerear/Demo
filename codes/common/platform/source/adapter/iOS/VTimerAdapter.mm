//
//  VTimerAdapter.cpp
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#include "VTimerAdapter.h"
#import "VTimer_iOS.h"


namespace VPlatform
{
    #define IOS_TIMER     ((VTimer_iOS*)m_pTimer)
    
    uint32_t g_unTimerID = V_INVALID_TIMER_ID;
    
    VTimerAdapter::VTimerAdapter()
        : m_pObserver(NULL)
        , m_unTimerID(V_INVALID_TIMER_ID)
        , m_pTimer(NULL)
    {
        VTimer_iOS *pTimer = [[VTimer_iOS alloc] initWithObject:this];
        
        if (pTimer != nil)
        {
            m_pTimer = pTimer;
        }
    }
    
    VTimerAdapter::~VTimerAdapter()
    {
        stop();
        
        VTimer_iOS *pTimer = IOS_TIMER;
        if (pTimer != nil)
        {
            [pTimer release];
            pTimer = nil;
        }
    }
    
    uint32_t VTimerAdapter::start(uint32_t unInterval)
    {
        if (IOS_TIMER != nil)
        {
            if ([IOS_TIMER start:unInterval])
            {
                m_unTimerID = ++g_unTimerID;
            }
        }
        
        return m_unTimerID;
    }
    
    void VTimerAdapter::stop()
    {
        if (IOS_TIMER != nil)
        {
            [IOS_TIMER stop];
			m_unTimerID = V_INVALID_TIMER_ID;
        }
    }
    
    void VTimerAdapter::setObserver(ITimerObserver *pObserver)
    {
        m_pObserver = pObserver;
    }
    
    uint32_t VTimerAdapter::getTimerID() const
    {
        return m_unTimerID;
    }
}

