/*
 * Reflection registration for header: TestController.h
 *
 *   Created on: 19.07.2010
 *       Author: CodeGenerator V1.0
 */

#include "TestController.h"
#include <reflections/Reflection.h>
#include <stddef.h>
#include <boost/any.hpp>


void* TestControllerConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new TestController();
}


struct TestController_ReflectionStruct {
	TestController_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		superClasses.push_back("BasicController");

		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &TestControllerConstructorCreateFunction0));

		ReflectionClass* tmpClass = new ReflectionClass("TestController", typeid(TestController).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
TestController_ReflectionStruct refStructTestController;

