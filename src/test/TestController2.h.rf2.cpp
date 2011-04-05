/*
 * Reflection registration for header: TestController2.h
 *
 *   Created on: 05.04.2011
 *       Author: CodeGenerator V2.0
 */

#include "TestController2.h"
#include <reflectionlib/Reflection.h>
#include <reflectionlib/ReflectionConverter.h>
#include <vector>
#include <stddef.h>
#include <boost/any.hpp>
#include <serializationlib/Serializer.h>
#include <serializationlib/MapDataConverter.h>
#include <serializationlib/PairDataConverter.h>
#include <serializationlib/VectorDataConverter.h>

void* TestController2ConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new TestController2();
}

boost::any TestController2CallFunction_testFunction2(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((TestController2*)instance)->testFunction(ReflectionConverter::convertPointer<HttpRequest*>(params[0]), ReflectionConverter::convertPointer<HttpResponse*>(params[1])));
}


struct TestController2_ReflectionStruct {
	TestController2_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		std::map<std::string, std::string> paramsMap;
		std::map<std::string, ReflectionAnotation*> anotationsHolder;

		superClasses.push_back("IObject");

		anotationsHolder.clear();
		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &TestController2ConstructorCreateFunction0, anotationsHolder));

		anotationsHolder.clear();
		paramsMap.clear();
		paramsMap["url"] = "/text";
		anotationsHolder["Request"] = new ReflectionAnotation("Request", paramsMap);
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("request", typeid(HttpRequest*).name(), "HttpRequest*"));
		paramsHolder.push_back(new ReflectionParam("response", typeid(HttpResponse*).name(), "HttpResponse*"));
		functionsHolder.push_back(new ReflectionFunction("testFunction", "ModelAndView", paramsHolder, &TestController2CallFunction_testFunction2, anotationsHolder));

		anotationsHolder.clear();
		ReflectionClass* tmpClass = new ReflectionClass("TestController2", typeid(TestController2).name(), typeid(TestController2*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS, anotationsHolder);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
TestController2_ReflectionStruct refStructTestController2;


