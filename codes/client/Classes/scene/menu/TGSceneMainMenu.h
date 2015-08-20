
#ifndef __TG_SCENE_MAIN_MENU_H__
#define __TG_SCENE_MAIN_MENU_H__


#include "TGEngine.h"
#include "TGScene.h"


class TGSceneMainMenu : public TGScene
{
	V_DISABLE_COPY(TGSceneMainMenu);

	TG_DECLARE_SCENE();

CC_CONSTRUCTOR_ACCESS:
	TGSceneMainMenu();
	virtual ~TGSceneMainMenu();

	virtual bool init() override;

protected:	// from class TGScene
	virtual const VString &getSceneName() const;

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};


#endif	/*__TG_SCENE_MAIN_MENU_H__*/
