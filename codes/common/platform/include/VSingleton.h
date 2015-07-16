/**************************************************************************************************
 * Copyright (C) 2014. Tiny Entertainment Studio.
 * All rights reserved.
 *
 * @file    VSingleton.h
 * @brief   单例模板类定义.
 * @author  aaronwang
 * @date    2014/2/10 0:11:34
 * @version v1.00
 **************************************************************************************************/

#ifndef __VISION_SINGLETON_H__
#define __VISION_SINGLETON_H__


#include "VType.h"
#include "VMacro.h"
#include "VPlatform.h"

#define INIT_SINGLETON(t) template<> t *VSingleton<t>::m_pInstance = NULL


/**
 * @class VSingleton
 * @brief 单例模板类
 */
template<typename T>
class VSingleton
{
	V_DISABLE_COPY(VSingleton);

public:
	/**
		* @brief Constructor for VSingleton.
		*/
	VSingleton()
	{
		m_pInstance = static_cast<T*>(this);
	}

	/**
		* @brief Destructor for VSingleton.
		*/
	~VSingleton()
	{
		m_pInstance = NULL;
	}

	/**
		* @brief 获取单例对象 
		*/
	static T &GetInstance()
	{
		return *m_pInstance;
	}

	static T *GetInstancePtr()
	{
		return m_pInstance;
	}

protected:
	static T *m_pInstance;
};


#endif	/*__VISION_SINGLETON_H__*/
