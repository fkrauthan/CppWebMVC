/*
 * Reflection registration for header: InMemorySessionManager.h
 *
 *   Created on: 05.04.2011
 *       Author: CodeGenerator V2.0
 */

#include "InMemorySessionManager.h"
#include <reflectionlib/Reflection.h>
#include <reflectionlib/ReflectionConverter.h>
#include <vector>
#include <stddef.h>
#include <boost/any.hpp>
#include <serializationlib/Serializer.h>
#include <serializationlib/MapDataConverter.h>
#include <serializationlib/PairDataConverter.h>
#include <serializationlib/VectorDataConverter.h>

void* InMemorySessionManagerConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new InMemorySessionManager();
}

boost::any InMemorySessionManagerCallFunction_endSession2(void* instance, const std::vector<boost::any>& params) {
	((InMemorySessionManager*)instance)->endSession(ReflectionConverter::convertPointer<HttpSession*>(params[0]), boost::any_cast< HttpRequest >(params[1]), boost::any_cast< HttpResponse >(params[2]));
	return boost::any(0);
}

boost::any InMemorySessionManagerCallFunction_existSessionId3(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((InMemorySessionManager*)instance)->existSessionId(boost::any_cast< std::string >(params[0])));
}


struct InMemorySessionManager_ReflectionStruct {
	InMemorySessionManager_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		std::map<std::string, std::string> paramsMap;
		std::map<std::string, ReflectionAnotation*> anotationsHolder;

		superClasses.push_back("SessionManager");

		anotationsHolder.clear();
		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &InMemorySessionManagerConstructorCreateFunction0, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("session", typeid(HttpSession*).name(), "HttpSession*"));
		paramsHolder.push_back(new ReflectionParam("request", typeid(HttpRequest).name(), "HttpRequest"));
		paramsHolder.push_back(new ReflectionParam("response", typeid(HttpResponse).name(), "HttpResponse"));
		functionsHolder.push_back(new ReflectionFunction("endSession", "void", paramsHolder, &InMemorySessionManagerCallFunction_endSession2, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("id", typeid(std::string).name(), "std::string"));
		functionsHolder.push_back(new ReflectionFunction("existSessionId", "bool", paramsHolder, &InMemorySessionManagerCallFunction_existSessionId3, anotationsHolder));


		anotationsHolder.clear();
		ReflectionClass* tmpClass = new ReflectionClass("InMemorySessionManager", typeid(InMemorySessionManager).name(), typeid(InMemorySessionManager*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS, anotationsHolder);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
InMemorySessionManager_ReflectionStruct refStructInMemorySessionManager;


