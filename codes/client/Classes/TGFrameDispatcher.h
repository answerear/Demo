

#ifndef __TG_FRAME_DISPATCHER_H__
#define __TG_FRAME_DISPATCHER_H__


#include "TGEngine.h"
#include "VSingleton.h"


namespace VPlatform
{
	class VSystem;
}

namespace VFramework
{
	class VEventManager;
}


class TGSceneManager;


class TGFrameDispatcher
	: public CCObject
	, public VSingleton<TGFrameDispatcher>
{
public:
	TGFrameDispatcher();
	virtual ~TGFrameDispatcher();

protected:	// from class CCObject
	virtual void update(float dt);

protected:
	VPlatform::VSystem				*m_pSystem;
	VFramework::VEventManager		*m_pEventMgr;
	TGSceneManager					*m_pSceneMgr;
};


#endif	/*__TG_FRAME_DISPATCHER_H__*/
