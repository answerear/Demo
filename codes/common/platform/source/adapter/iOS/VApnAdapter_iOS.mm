//
//  VApnAdapter_iOS.m
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//

#import "VApnAdapter_iOS.h"
#import "IApnAdapterObserver.h"

#import <ifaddrs.h>
#import <sys/socket.h>
#import <arpa/inet.h>
#import <dns_sd.h>
#import <sys/types.h>
#import <net/if.h>
#import <netinet/in.h>
#import <netdb.h>
#import <unistd.h>

#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>


using namespace VPlatform;


@implementation VApnAdapter_iOS

@synthesize routeReach = _routeReach;
@synthesize pingReach = _pingReach;
@synthesize observer = _observer;

- (id)init
{
    self = [super init];
    if (self)
    {
#if 1
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(struct sockaddr_in));
        addr.sin_len = sizeof(struct sockaddr_in);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(80);
        inet_aton("173.194.43.0", &addr.sin_addr);
        self.routeReach = [VReach reachForAddress:&addr];
#else
        self.routeReach = [VReach reachForHost:@"www.apple.com"];
#endif
        self.routeReach.delegate = self;
        [self.routeReach startUpdating];
        
        _routes = [self.routeReach routes];
    }
    return self;
}

- (void)dealloc
{
    [self.routeReach stopUpdating];
    self.routeReach = nil;
    
    [self.pingReach stopUpdating];
    self.pingReach = nil;
    
    [super dealloc];
}

- (void)networkChanged:(VReach *)reach
{
    if (self.routeReach != nil && reach == self.routeReach)
    {
        if (self.observer != nil)
        {
            VReachRoutes oldRoutes = _routes;
            VReachRoutes newRoutes = [reach routes];
            _routes = newRoutes;
            
            EApnType nLastApn = (EApnType)[self routeToApn:oldRoutes];
            EApnType nCurrentApn = (EApnType)[self routeToApn:newRoutes];
            
            IApnAdapterObserver *observer = (IApnAdapterObserver*)_observer;
            observer->onApnChanged(nLastApn, nCurrentApn);
        }
    }
    else if (self.pingReach != nil && reach == self.pingReach)
    {
        _isReachable = [reach isReachable];
        IApnAdapterObserver *observer = (IApnAdapterObserver*)_observer;
        observer->onPingResult(_isReachable == YES);
        
        [self.pingReach stopUpdating];
        self.pingReach = nil;
    }
}

- (void)pingRoutes:(NSString *)host
{
    if (self.pingReach != nil)
    {
        [self.pingReach stopUpdating];
        self.pingReach = nil;
    }
    
    self.pingReach = [VReach reachForHost:@"www.apple.com"];
    self.pingReach.delegate = self;
    [self.pingReach startUpdating];
}

- (void)cancelPingRoutes
{
    if (self.pingReach != nil)
    {
        [self.pingReach stopUpdating];
        self.pingReach = nil;
    }
}

- (int)apnType
{
    VReachRoutes routes = [self.routeReach routes];
    return [self routeToApn:routes];
}

- (int)routeToApn:(VReachRoutes)routes
{
    EApnType apn = E_APN_UNKNOWN;
    
    switch (routes)
    {
        case VReachRouteNone:
            apn = E_APN_UNREACHABLE;
            break;
        case VReachRouteWiFi:
            apn = E_APN_WIFI;
            break;
        case VReachRouteWWAN_3G:
            apn = E_APN_3G;
            break;
        case VReachRouteWWAN_2G:
            apn = E_APN_2G;
            break;
        default:
            apn = E_APN_UNKNOWN;
            break;
    }
    return apn;
}

@end
