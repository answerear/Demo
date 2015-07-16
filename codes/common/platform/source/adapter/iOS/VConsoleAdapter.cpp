//
//  VConsoleAdapter.cpp
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#include "VConsoleAdapter.h"


namespace VPlatform
{
    VConsoleAdapter::VConsoleAdapter()
    {
        
    }
    
    VConsoleAdapter::~VConsoleAdapter()
    {
        
    }
    
    void VConsoleAdapter::print(const char *pText)
    {
        printf(pText);
    }
}
