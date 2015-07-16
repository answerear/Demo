//
//  VApnAdapter.cpp
//  LogSDK
//
//  Created by aaronwang on 14-1-24.
//  Copyright (c) 2014年 aaronwang. All rights reserved.
//


#include "VApnAdapter.h"
#include "VApnAdapter_iOS.h"

#import "VReach.h"

#import <ifaddrs.h>
#import <sys/socket.h>
#import <arpa/inet.h>
#import <dns_sd.h>
#import <sys/types.h>
#import <net/if.h>
#import <netinet/in.h>
#import <netdb.h>
#import <unistd.h>

#import <UIKit/UIKit.h>
#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>


namespace VPlatform
{
    VApnAdapter::VApnAdapter()
    : m_pOSAdapter(NULL)
    , m_pObserver(NULL)
    {
        VApnAdapter_iOS *adapter = [[VApnAdapter_iOS alloc] init];
        adapter.observer = this;
        m_pOSAdapter = adapter;
    }
    
    VApnAdapter::~VApnAdapter()
    {
        VApnAdapter_iOS *adapter = (VApnAdapter_iOS *)m_pOSAdapter;
        [adapter release];
        m_pOSAdapter = NULL;
    }
    
    void VApnAdapter::setObserver(IApnAdapterObserver *pObserver)
    {
        m_pObserver = pObserver;
    }
    
    EApnType VApnAdapter::getApnType() const
    {
        VApnAdapter_iOS *adapter = (VApnAdapter_iOS *)m_pOSAdapter;
        return (EApnType)[adapter apnType];
    }
    
    ECarrier VApnAdapter::getCarrier() const
    {
        UIDevice* device = [UIDevice currentDevice];
        if ([device.systemVersion floatValue] < 4.0) {
            return E_CARRIER_CHINA_MOBILE;
        }
        
        ECarrier carrierType = E_CARRIER_UNKNOWN;
        
        if ([CTTelephonyNetworkInfo class])
        {
            // Setup the Network Info and create a CTCarrier object
            CTTelephonyNetworkInfo *networkInfo = [[[CTTelephonyNetworkInfo alloc] init] autorelease];
            CTCarrier *carrier = [networkInfo subscriberCellularProvider];
            
            // Get carrier name
            //NSString *name = [carrier carrierName];
            
            // Get mobile country code
            NSString *countryCode = [carrier mobileCountryCode];
            NSInteger mcc = [countryCode intValue];
            
            if (460 == mcc)	// 460是IMSI中国编号
            {
                // Get mobile network code
                NSString *networkCode = [carrier mobileNetworkCode];
                NSInteger mnc = [networkCode intValue];
                
                /* China - CN
                 * MCC    MNC    Brand    Operator                Status        Bands (MHz)                                    References and notes
                 * 460    00            China Mobile            Operational    GSM 900/GSM 1800 UMTS (TD-SCDMA) 1880/2010
                 * 460    01            China Unicom            Operational    GSM 900/GSM 1800/ UMTS 2100                    CDMA network sold to China Telecom, WCDMA commercial trial started in May 2009 and in full commercial operation as of October 2009.
                 * 460    02            China Mobile            Operational    GSM 900/GSM 1800/ UMTS (TD-SCDMA) 1880/2010
                 * 460    03            China Telecom            Operational    CDMA 800/cdma evdo 2100
                 * 460    05            China Telecom            Operational
                 * 460    06            China Unicom            Operational    GSM 900/GSM 1800/UMTS 2100
                 * 460    07            China Mobile            Operational    GSM 900/GSM 1800/UMTS (TD-SCDMA) 1880/2010
                 * 460    20            China Tietong            Operational    GSM-R
                 * NA    NA            China Telecom&China Unicom    Operational
                 */
                switch (mnc)
                {
                    case 0:
                    case 2:
                    case 7:	// 00、02、07均是中国移动
                    {
                        carrierType = E_CARRIER_CHINA_MOBILE;
                    }
                        break;
                    case 1:
                    case 6: // 01、06是中国联通
                    {
                        carrierType = E_CARRIER_CHINA_UNICOM;
                    }
                        break;
                    case 3:
                    case 5:	// 03、05是中国电信
                    {
                        carrierType = E_CARRIER_CHINA_TELECOM;
                    }
                        break;
                    case 20:// 20是中国铁通
                    {
                        carrierType = E_CARRIER_CHINA_TIETONG;
                    }
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            carrierType = E_CARRIER_CHINA_UNICOM;
        }
        
        return carrierType;
    }
    
    bool VApnAdapter::pingRoutes(const std::string &strHost)
    {
        if (strHost.empty())
            return false;
        
        VApnAdapter_iOS *adapter = (VApnAdapter_iOS *)m_pOSAdapter;
        NSString *host = [NSString stringWithUTF8String:strHost.c_str()];
        [adapter pingRoutes:host];
        
        return true;
    }
    
    void VApnAdapter::cancelPingRoutes()
    {
        VApnAdapter_iOS *adapter = (VApnAdapter_iOS *)m_pOSAdapter;
        [adapter cancelPingRoutes];
    }
    
    void VApnAdapter::onApnChanged(EApnType eLastApn, EApnType eCurrentApn)
    {
        if (m_pObserver != NULL)
        {
            m_pObserver->onApnChanged(eLastApn, eCurrentApn);
        }
    }
    
    void VApnAdapter::onPingResult(bool bReachable)
    {
        if (m_pObserver != NULL)
        {
            m_pObserver->onPingResult(bReachable);
        }
    }

}
