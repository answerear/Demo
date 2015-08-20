
#include "TGSceneMainMenu.h"
#include "TGSceneName.h"


TG_IMPLEMENT_SCENE(TGSceneMainMenu)


TGSceneMainMenu::TGSceneMainMenu()
{

}

TGSceneMainMenu::~TGSceneMainMenu()
{

}

bool TGSceneMainMenu::init()
{
	return TGScene::init();
}

const VString &TGSceneMainMenu::getSceneName() const
{
	return TG_SCENE_MAIN_MENU;
}

void TGSceneMainMenu::onEnter()
{
	TGScene::onEnter();

	// TODO: Add your code here
}

void TGSceneMainMenu::onEnterTransitionDidFinish()
{
	// TODO: Add your code here
}

void TGSceneMainMenu::onExit()
{
	// TODO: Add your code here

	TGScene::onExit();
}
