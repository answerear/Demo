

#include "TGFrameDispatcher.h"
#include "TGEventDefine.h"
#include "VSystem.h"
#include "VEventManager.h"
#include "TGSceneManager.h"


using namespace VPlatform;
using namespace VFramework;


INIT_SINGLETON(TGFrameDispatcher);


TGFrameDispatcher::TGFrameDispatcher()
	: m_pSystem(new VSystem())
	, m_pEventMgr(new VEventManager(V_MAX_EVENTS))
	, m_pSceneMgr(new TGSceneManager())
{
}

TGFrameDispatcher::~TGFrameDispatcher()
{
	V_SAFE_DELETE(m_pSceneMgr);
	V_SAFE_DELETE(m_pEventMgr);
	V_SAFE_DELETE(m_pSystem);
}

void TGFrameDispatcher::update(float dt)
{
	if (m_pSystem != NULL)
	{
		m_pSystem->process();
	}

	if (m_pEventMgr != NULL)
	{
		m_pEventMgr->dispatchEvent();
	}
}
