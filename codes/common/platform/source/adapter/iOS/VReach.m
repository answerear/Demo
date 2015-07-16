//
//  VReach.m
//
//  Copyright (c) 2012 Auerhaus Development, LLC
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal in the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included 
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
//  IN THE SOFTWARE.
//  

#import "VReach.h"
#import <SystemConfiguration/SystemConfiguration.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>



@interface VReach ()
@property(nonatomic) SCNetworkReachabilityRef reachability;
@end

void QGReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void *info);

@implementation VReach

@synthesize reachability;
@synthesize delegate = _delegate;

#pragma mark - Factory methods

+ (VReach *)reachForHost:(NSString *)host {
	SCNetworkReachabilityRef reachabilityRef = SCNetworkReachabilityCreateWithName(NULL, [host UTF8String]);
	return [[[VReach alloc] initWithReachability:reachabilityRef] autorelease];
}

+ (VReach *)reachForAddress:(const struct sockaddr_in *)addr {
	SCNetworkReachabilityRef reachabilityRef = SCNetworkReachabilityCreateWithAddress(NULL, (const struct sockaddr *)addr);
	return [[[VReach alloc] initWithReachability:reachabilityRef] autorelease];
}

#pragma mark - Object lifetime

- (id)initWithReachability:(SCNetworkReachabilityRef)reachabilityRef {
	if((self = [super init]) && reachabilityRef) {
		reachability = reachabilityRef;
		return self;
	}

	return nil;
}

- (void)dealloc {
	[self stopUpdating];
        
	if(reachability) {
		CFRelease(reachability);
		reachability = NULL;
	}
    
    [super dealloc];
}

#pragma mark - Reachability and notification methods

- (VReachRoutes)availableRoutes {
	VReachRoutes routes = VReachRouteNone;
	SCNetworkReachabilityFlags flags = 0;
	SCNetworkReachabilityGetFlags(self.reachability, &flags);
	
	if(flags & kSCNetworkReachabilityFlagsReachable)
	{
		// Since WWAN is likely to require a connection, we initially assume a route with no connection required is WiFi
		if(!(flags & kSCNetworkReachabilityFlagsConnectionRequired)) {
			routes |= VReachRouteWiFi;
		}
		
		BOOL automatic = (flags & kSCNetworkReachabilityFlagsConnectionOnDemand) || 
		                 (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic);
		
		// Alternatively, a connection that connects on-demand/-traffic without intervention required might be WiFi too
		if(automatic && !(flags & kSCNetworkReachabilityFlagsInterventionRequired)) {
			routes |= VReachRouteWiFi;
		}
		
		// But if we're told explicitly that we're on WWAN, we throw away all earlier knowledge and just report WWAN
		if(flags & kSCNetworkReachabilityFlagsIsWWAN) {
			routes &= ~VReachRouteWiFi;
            
            if ((flags & kSCNetworkFlagsTransientConnection) == kSCNetworkFlagsTransientConnection)
            {
                routes |= VReachRouteWWAN_2G;
            }
            else
            {
                routes |= VReachRouteWWAN_3G;
            }
		}
	}

	return routes;
}

- (BOOL)isReachable {
	return [self availableRoutes] != VReachRouteNone;
}

- (VReachRoutes)routes {
    VReachRoutes r = [self availableRoutes];
    
    if (r & VReachRouteWiFi)
        return VReachRouteWiFi;
    else if (r & VReachRouteWWAN_2G)
        return VReachRouteWWAN_2G;
    else if (r & VReachRouteWWAN_3G)
        return VReachRouteWWAN_3G;
    
    return r;
}

- (BOOL)isReachableViaWWAN_2G {
	return [self availableRoutes] & VReachRouteWWAN_2G;
}

- (BOOL)isReachableViaWWAN_3G {
	return [self availableRoutes] & VReachRouteWWAN_3G;
}

- (BOOL)isReachableViaWiFi {
	return [self availableRoutes] & VReachRouteWiFi;
}

- (void)startUpdating {
	if(self.reachability) {
		SCNetworkReachabilityContext context = { 0, self, NULL, NULL, NULL };
		SCNetworkReachabilitySetCallback(self.reachability, QGReachabilityCallback, &context);
		SCNetworkReachabilityScheduleWithRunLoop(self.reachability, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
	} else {
		[self stopUpdating];
	}
}

- (void)reachabilityDidChange {
	if (self.delegate != nil && [self.delegate respondsToSelector:@selector(networkChanged:)])
    {
        [self.delegate networkChanged:self];
    }
}

- (void)stopUpdating {
	
	if(self.reachability) {
		SCNetworkReachabilityUnscheduleFromRunLoop(self.reachability, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
		SCNetworkReachabilitySetCallback(self.reachability, NULL, NULL);
	}
}

@end

#pragma mark - Reachability callback function

void QGReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void *info)
{
	VReach *reach = (VReach *)info;
	[reach reachabilityDidChange];
}
