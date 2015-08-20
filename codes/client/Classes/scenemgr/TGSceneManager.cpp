/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    TGSceneManager.cpp
 * @brief   Brief description.
 * @author  
 * @date    2014/3/18 14:35:01
 * @version v1.00
 **************************************************************************************************/


#include "TGSceneManager.h"
#include "TGScene.h"


template<> TGSceneManager *VSingleton<TGSceneManager>::m_pInstance = NULL;


TGSceneManager::TGSceneManager()
{

}

TGSceneManager::~TGSceneManager()
{

}

bool TGSceneManager::registerScene(const VString &strName, TG_PFN_SCENE_CREATOR pfnCreator)
{
	if (strName.empty() || pfnCreator == NULL)
		return false;

	std::pair<VString, TG_PFN_SCENE_CREATOR> val(strName, pfnCreator);
	std::pair<TGSceneMap::iterator, bool> inserted = m_sceneMap.insert(val);
	return inserted.second;
}

bool TGSceneManager::unregisterScene(const VString &strName)
{
	if (strName.empty())
		return false;

	bool bRet = false;
	TGSceneMapItr itr = m_sceneMap.find(strName);

	if (itr != m_sceneMap.end())
	{
		m_sceneMap.erase(itr);
		bRet = true;
	}

	return bRet;
}

bool TGSceneManager::runScene(const VString &strName)
{
	bool bRet = false;
	TGSceneMapItr itr = m_sceneMap.find(strName);
	if (itr != m_sceneMap.end())
	{
		TG_PFN_SCENE_CREATOR pfnCreator = itr->second;

		CCScene *pScene = NULL;
		if (pfnCreator != NULL)
		{
			pScene = pfnCreator();
		}

		if (pScene != NULL)
		{
			m_strLastSceneName = strName;
			m_sceneStack.push_back((TGScene*)pScene);
			CCDirector::sharedDirector()->runWithScene(pScene);
			bRet = true;
		}
	}

	return bRet;
}

bool TGSceneManager::replaceScene(const VString &strName, TGSceneTransition eTransition /* = TG_TRANSITION_DEFAULT */, float fDuration /*= 1.0f*/)
{
	if (strName.empty())
		return false;

	TGScene *pRunningScene = getCurrentScene();
	if (pRunningScene != NULL)
	{
		if (pRunningScene->getSceneName() == strName)
			return false;
	}

	bool bRet = false;

	TGSceneMapItr itr = m_sceneMap.find(strName);
	if (itr != m_sceneMap.end())
	{
		TG_PFN_SCENE_CREATOR pfnCreator = itr->second;

		CCScene *pScene = NULL;
		if (pfnCreator != NULL)
		{
			pScene = pfnCreator(); 
		}

		if (pScene != NULL)
		{
			if (!m_sceneStack.empty())
			{
				// 先弹出原来的场景，这里不需要删除，因为cocos2d-x里面会删除
				m_sceneStack.pop_back();
			}

			if (pRunningScene != NULL)
			{
				m_strLastSceneName = pRunningScene->getSceneName();
			}
			
			m_sceneStack.push_back((TGScene*)pScene);
			CCScene *pTransitionScene = createTransitionScene(pScene, eTransition, fDuration);
			CCDirector::sharedDirector()->replaceScene(pTransitionScene);
		}
	}

	return bRet;
}

bool TGSceneManager::pushScene(const VString &strName, TGSceneTransition eTransition,  float fDuration)
{
	if (strName.empty())
		return false;

	bool bRet = false;
	TGSceneMapItr itr = m_sceneMap.find(strName);
	if (itr != m_sceneMap.end())
	{
		TG_PFN_SCENE_CREATOR pfnCreator = itr->second;

		CCScene *pScene = NULL;
		if (pfnCreator != NULL)
		{
			pScene = pfnCreator();
		}

		if (pScene != NULL)
		{
			TGScene *pRunningScene = getCurrentScene();
			if (pRunningScene != NULL)
			{
				m_strLastSceneName = pRunningScene->getSceneName();
			}

			m_sceneStack.push_back((TGScene*)pScene);
			CCScene *pTransitionScene = createTransitionScene(pScene, eTransition, fDuration);
			CCDirector::sharedDirector()->pushScene(pTransitionScene);
		}
	}

	return bRet;
}

void TGSceneManager::popScene()
{
	m_sceneStack.pop_back();
	CCDirector::sharedDirector()->popScene();
}

TGScene *TGSceneManager::getCurrentScene()
{
	TGScene *pScene = NULL;

	if (!m_sceneStack.empty())
	{
		pScene = m_sceneStack.back();
	}

	return pScene;
}

CCScene *TGSceneManager::createTransitionScene(CCScene *pScene, TGSceneTransition eTransition,  float fDuration)
{
	CCScene *pTransitionScene = NULL;

	switch (eTransition)
	{
	case TG_TRANSITION_NONE:
		{
			pTransitionScene = pScene;
		}
		break;
	case TG_TRANSITION_DEFAULT:
		{
			pTransitionScene = CCTransitionFade::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_CROSS_FADE:
		{
			pTransitionScene = CCTransitionCrossFade::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_FADE:
		{
			pTransitionScene = CCTransitionFade::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_FADE_TR:
		{
			pTransitionScene = CCTransitionFadeTR::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_JUMP_ZOOM:
		{
			pTransitionScene = CCTransitionJumpZoom::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_MOVE_IN_L:
		{
			pTransitionScene = CCTransitionMoveInL::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_PAGE_TURN_UP:
		{
			pTransitionScene = CCTransitionPageTurn::create(fDuration, pScene, false);
		}
		break;
    case TG_TRANSITION_PAGE_TURN_DOWN:
        {
            pTransitionScene = CCTransitionPageTurn::create(fDuration, pScene, true);
        }
        break;
	case TG_TRANSITION_PROGRESS:
		{
			pTransitionScene = CCTransitionProgress::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_ROTO_ZOOM:
		{
			pTransitionScene = CCTransitionRotoZoom::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_SCENE_ORIENTED:
		{
			pTransitionScene = CCTransitionSceneOriented::create(fDuration, pScene, kCCTransitionOrientationLeftOver);
		}
		break;
	case TG_TRANSITION_SHRINK_GROW:
		{
			pTransitionScene = CCTransitionShrinkGrow::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_SLIDE_IN_L:
		{
			pTransitionScene = CCTransitionSlideInL::create(fDuration, pScene);
		}
		break;
    case TG_TRANSITION_SLIDE_IN_R:
        {
            pTransitionScene = CCTransitionSlideInR::create(fDuration, pScene);
        }
        break;
	case TG_TRANSITION_SPLIT_COLS:
		{
			pTransitionScene = CCTransitionSplitCols::create(fDuration, pScene);
		}
		break;
	case TG_TRANSITION_TURN_OFF_TILES:
		{
			pTransitionScene = CCTransitionTurnOffTiles::create(fDuration, pScene);
		}
		break;
	default:
		break;
	}

	return pTransitionScene;
}
