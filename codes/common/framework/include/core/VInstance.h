

#ifndef __VISION_INSTANCE_H__
#define __VISION_INSTANCE_H__


#include "VType.h"
#include "VMacro.h"
#include "VFramework.h"


namespace VFramework
{
    class VFRAMEWORK_API VInstance
    {
    public:
        static const VInstance V_BROADCAST_INSTANCE_ID;
        static const VInstance V_INVALID_INSTANCE_ID;
        
        void        *m_pObject;
        int32_t     m_nIndex;
        
        VInstance()
            : m_pObject(NULL)
            , m_nIndex(0)
        {
        }
        
        VInstance(void *pObject, uint32_t nIndex)
            : m_pObject(pObject)
            , m_nIndex(nIndex)
        {
        }
        
        VInstance(const VInstance &other)
        {
            m_pObject = other.m_pObject;
            m_nIndex = other.m_nIndex;
        }
        
        bool operator ==(const VInstance &other) const
        {
            return (m_pObject == other.m_pObject && m_nIndex == other.m_nIndex);
        }
        
        bool operator !=(const VInstance &other) const
        {
            return (m_pObject != other.m_pObject || m_nIndex != other.m_nIndex);
        }
        
        bool operator <(const VInstance &other) const
        {
            return (m_nIndex < other.m_nIndex || (m_nIndex == other.m_nIndex && m_pObject < other.m_pObject));
        }
    };
}



typedef VFramework::VInstance VINSTANCE;


#endif	/*__VISION_INSTANCE_H__*/
