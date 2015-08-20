
#ifndef __TG_SCENE_MANAGER_H__
#define __TG_SCENE_MANAGER_H__


#include "TGEngine.h"
#include "VSingleton.h"


typedef CCScene* (*TG_PFN_SCENE_CREATOR)();


class TGScene;


class TGSceneManager : public VSingleton<TGSceneManager>
{
	V_DISABLE_COPY(TGSceneManager);

public:
	/**
	 * @brief 场景切换效果枚举
	 */
	enum TGSceneTransition
	{
		TG_TRANSITION_NONE = 0,			/// 没有切换效果
		TG_TRANSITION_DEFAULT,			/// 默认场景切换效果
		TG_TRANSITION_CROSS_FADE,		/// 
		TG_TRANSITION_FADE,
		TG_TRANSITION_FADE_TR,
		TG_TRANSITION_JUMP_ZOOM,
		TG_TRANSITION_MOVE_IN_L,
		TG_TRANSITION_PAGE_TURN_UP,     //向上翻页
        TG_TRANSITION_PAGE_TURN_DOWN,   // 向下翻页
		TG_TRANSITION_PROGRESS,
		TG_TRANSITION_ROTO_ZOOM,
		TG_TRANSITION_SCENE_ORIENTED,
		TG_TRANSITION_SHRINK_GROW,
		TG_TRANSITION_SLIDE_IN_L,
        TG_TRANSITION_SLIDE_IN_R,
		TG_TRANSITION_SPLIT_COLS,
		TG_TRANSITION_TURN_OFF_TILES,
	};

public: 
	/**
	 * @brief Constructor for QGSceneManager.
	 */
	TGSceneManager();

	/**
	 * @brief Destructor for QGSceneManager.
	 */
	virtual ~TGSceneManager();

	bool registerScene(const VString &strName, TG_PFN_SCENE_CREATOR pfnCreator);
	bool unregisterScene(const VString &strName);

	bool runScene(const VString &strName);

	bool replaceScene(const VString &strName, TGSceneTransition eTransition = TG_TRANSITION_DEFAULT,  float fDuration = 1.0f);

	bool pushScene(const VString &strName, TGSceneTransition eTransition = TG_TRANSITION_DEFAULT,  float fDuration = 1.0f);
	void popScene();

	TGScene *getCurrentScene();

	const VString getLastSceneName() const
	{
		return m_strLastSceneName;
	}

protected:
	CCScene *createTransitionScene(CCScene *pScene, TGSceneTransition eTransition, float fDuration);

protected:
	typedef std::map<VString, TG_PFN_SCENE_CREATOR> TGSceneMap;
	typedef TGSceneMap::iterator TGSceneMapItr;

	typedef std::list<TGScene*> TGSceneStack;
	typedef TGSceneStack::iterator	TGSceneStackItr;

	TGSceneMap		m_sceneMap;
	TGSceneStack	m_sceneStack;

	VString			m_strLastSceneName;
};


#define TG_SCENE_MGR		TGSceneManager::GetInstancePtr()


#endif	/*__TG_SCENE_MANAGER_H__*/
