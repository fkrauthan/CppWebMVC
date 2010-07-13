/*
 * Reflection macros for header: Application.h
 *
 *   Created on: 23.6.2010
 *       Author: ./readSampleClass.py
 */

#include "Application.h"
#include <reflections/ReflectionMacros.h>


BEGIN_CREATE_CONSTRUCTOR_CALL(Application, 0)
END_CREATE_CONSTRUCTOR_CALL()

BEGIN_CREATE_FUNCTIONCALL(Application, getBeanFactory, 0)
END_CREATE_FUNCTIONCALL()

BEGIN_CREATE_FUNCTIONCALL_VOID(Application, setBeanFactory, 1)
	ADD_PARAMETER(BeanFactory*, 0)
END_CREATE_FUNCTIONCALL_VOID()

BEGIN_CREATE_FUNCTIONCALL_VOID(Application, setThreadPoolSize, 2)
	ADD_PARAMETER(int, 0)
END_CREATE_FUNCTIONCALL_VOID()


BEGIN_REGISTER_CLASS(Application)
	REGISTER_INTERFACE(IApplication)

	START_REGISTER_CTOR()
	END_REGISTER_CTOR(Application, 0)

	START_REGISTER_FUNCTION(getBeanFactory)
	END_REGISTER_FUNCTION(Application, getBeanFactory, BeanFactory*, 0)
	START_REGISTER_FUNCTION(setBeanFactory)
		REGISTER_PARAM(BeanFactory*, beanFactory)
	END_REGISTER_FUNCTION(Application, setBeanFactory, void, 1)
	START_REGISTER_FUNCTION(setThreadPoolSize)
		REGISTER_PARAM(int, size)
	END_REGISTER_FUNCTION(Application, setThreadPoolSize, void, 2)
END_REGISTER_CLASS(Application)

