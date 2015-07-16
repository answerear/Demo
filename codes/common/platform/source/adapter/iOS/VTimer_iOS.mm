//
//  VTimer_iOS.m
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//

#import "VTimer_iOS.h"
#include "VTimerAdapter.h"
#include "ITimerObserver.h"
#include <map>


using namespace VPlatform;


@interface VTimer_iOS (Private)
- (void)onTimer:(NSTimer*)timer;
@end


@implementation VTimer_iOS

- (id)initWithObject:(void *)object
{
    if (self = [super init])
    {
        _object = object;
    }
    return self;
}

- (unsigned int)start:(unsigned int)interval
{
    _timer = [[NSTimer scheduledTimerWithTimeInterval:(interval/1000.0f)
                                              target:self selector:@selector(onTimer:)
                                            userInfo:nil
                                             repeats:TRUE] retain];
    return (_timer != nil);
}

- (void)stop
{
    [_timer invalidate];
	[_timer release];
	_timer = nil;
}

- (void)onTimer:(NSTimer *)timer    
{
    if ([timer isValid])
	{
		VTimerAdapter *pTimer = (VTimerAdapter *)_object;
        if (pTimer != NULL && pTimer->m_pObserver != NULL)
        {
            pTimer->m_pObserver->onTimer(pTimer->m_unTimerID);
        }
	}
}

@end
