

#include "VPoolObject.h"


namespace VPlatform
{
	VPoolObject::VPoolObject()
		: _pList(NULL)
		, _pBlock(NULL)
		, _pPrevObj(NULL)
		, _pNextObj(NULL)
	{

	}

	VPoolObject::~VPoolObject()
	{
		if (_pPrevObj != NULL)
			_pPrevObj->_pNextObj = _pNextObj;
		
		if (_pNextObj != NULL)
			_pNextObj->_pPrevObj = _pPrevObj;

		_pPrevObj = _pNextObj = NULL;
	}
}
