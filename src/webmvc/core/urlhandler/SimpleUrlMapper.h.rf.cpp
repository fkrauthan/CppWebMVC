/*
 * Reflection macros for header: SimpleUrlMapper.h
 *
 *   Created on: 30.6.2010
 *       Author: ./readSampleClass.py
 */

#include "SimpleUrlMapper.h"
#include <reflections/ReflectionMacros.h>


BEGIN_CREATE_CONSTRUCTOR_CALL(SimpleUrlMapper, 0)
END_CREATE_CONSTRUCTOR_CALL()

BEGIN_CREATE_FUNCTIONCALL_VOID(SimpleUrlMapper, setInterceptors, 0)
	ADD_VECTOR_POINTER_PARAMETER(IInterceptor*, 0)
END_CREATE_FUNCTIONCALL_VOID()

BEGIN_CREATE_FUNCTIONCALL_VOID(SimpleUrlMapper, setMappings, 1)
	ADD_VECTOR_PAIR_POINTER_PARAMETER(std::string, IBasicController*, 0)
END_CREATE_FUNCTIONCALL_VOID()


BEGIN_REGISTER_CLASS(SimpleUrlMapper)
	REGISTER_INTERFACE(IUrlHandler)

	START_REGISTER_CTOR()
	END_REGISTER_CTOR(SimpleUrlMapper, 0)

	START_REGISTER_FUNCTION(setInterceptors)
		REGISTER_PARAM(std::vector<IInterceptor*>, interceptors)
	END_REGISTER_FUNCTION(SimpleUrlMapper, setInterceptors, void, 0)
	START_REGISTER_FUNCTION(setMappings)
		REGISTER_PARAM(MAP(std::string, IBasicController*), mappings)
	END_REGISTER_FUNCTION(SimpleUrlMapper, setMappings, void, 1)
END_REGISTER_CLASS(SimpleUrlMapper)

