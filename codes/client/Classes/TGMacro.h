
#ifndef __TG_MACRO_H__
#define __TG_MACRO_H__


#include "VType.h"
#include "VMacro.h"


#define TG_DECLARE_SCENE()	\
	public:	\
		static CCScene *create();

#define TG_IMPLEMENT_SCENE(className)	\
	CCScene *className::create()	\
	{	\
		className *pScene = new className();	\
		if (pScene && pScene->init())	\
		{	\
			pScene->autorelease();	\
			return pScene;	\
		}	\
		V_SAFE_DELETE(pScene);	\
		return pScene;	\
	}

#endif	/*__TG_MACRO_H__*/
