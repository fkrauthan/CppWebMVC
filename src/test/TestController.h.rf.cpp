/*
 * Reflection macros for header: TestController.h
 *
 *   Created on: 30.6.2010
 *       Author: ./readSampleClass.py
 */

#include "TestController.h"
#include <reflections/ReflectionMacros.h>


BEGIN_CREATE_CONSTRUCTOR_CALL(TestController, 0)
END_CREATE_CONSTRUCTOR_CALL()


BEGIN_REGISTER_CLASS(TestController)
	REGISTER_INTERFACE(BasicController)

	START_REGISTER_CTOR()
	END_REGISTER_CTOR(TestController, 0)

END_REGISTER_CLASS(TestController)

