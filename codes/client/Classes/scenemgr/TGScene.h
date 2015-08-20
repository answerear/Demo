
#ifndef __TG_SCENE_H__
#define __TG_SCENE_H__


#include "TGEngine.h"


/**
 * @class TGScene
 * @brief 场景类基类，提供跟CCLayer相类似功能，提供可以接收触摸屏、按键、重力感应事件.
 */
class TGScene : public CCScene
{
public:
	virtual const VString &getSceneName() const = 0;
};


#endif	/*__TG_SCENE_H__*/
