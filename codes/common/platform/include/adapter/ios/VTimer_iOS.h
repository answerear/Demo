//
//  VTimer_iOS.h
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VTimer_iOS : NSObject
{
    NSTimer *_timer;
    void    *_object;
}

- (id)initWithObject:(void*)object;
- (unsigned int)start:(unsigned int)interval;
- (void)stop;

@end
