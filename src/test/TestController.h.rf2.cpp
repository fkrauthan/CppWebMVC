/*
 * Reflection registration for header: TestController.h
 *
 *   Created on: 05.04.2011
 *       Author: CodeGenerator V2.0
 */

#include "TestController.h"
#include <reflectionlib/Reflection.h>
#include <reflectionlib/ReflectionConverter.h>
#include <vector>
#include <stddef.h>
#include <boost/any.hpp>
#include <serializationlib/Serializer.h>
#include <serializationlib/MapDataConverter.h>
#include <serializationlib/PairDataConverter.h>
#include <serializationlib/VectorDataConverter.h>

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

		std::map<std::string, std::string> paramsMap;
		std::map<std::string, ReflectionAnotation*> anotationsHolder;

		superClasses.push_back("BasicController");

		anotationsHolder.clear();
		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &TestControllerConstructorCreateFunction0, anotationsHolder));

		anotationsHolder.clear();
		ReflectionClass* tmpClass = new ReflectionClass("TestController", typeid(TestController).name(), typeid(TestController*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS, anotationsHolder);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
TestController_ReflectionStruct refStructTestController;


