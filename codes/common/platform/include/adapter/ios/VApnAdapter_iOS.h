//
//  VApnAdapter_iOS.h
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//

#import "VReach.h"


@interface VApnAdapter_iOS : NSObject<VReachDelegate>
{
    VReach *_routeReach;
    VReach *_pingReach;
    void *_observer;
    
    VReachRoutes   _routes;
    BOOL    _isReachable;
}
@property(nonatomic, retain) VReach    *routeReach;
@property(nonatomic, retain) VReach    *pingReach;
@property(nonatomic, assign) void *observer;

- (int)apnType;
- (int)routeToApn:(VReachRoutes)routes;
- (void)pingRoutes:(NSString *)host;
- (void)cancelPingRoutes;

@end
