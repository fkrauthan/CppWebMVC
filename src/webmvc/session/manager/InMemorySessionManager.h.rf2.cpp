/*
 * Reflection registration for header: InMemorySessionManager.h
 *
 *   Created on: 20.07.2010
 *       Author: CodeGenerator V1.0
 */

#include "InMemorySessionManager.h"
#include <reflections/Reflection.h>
#include <reflections/ReflectionConverter.h>
#include <stddef.h>
#include <boost/any.hpp>


void* InMemorySessionManagerConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new InMemorySessionManager();
}


struct InMemorySessionManager_ReflectionStruct {
	InMemorySessionManager_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		superClasses.push_back("SessionManager");

		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &InMemorySessionManagerConstructorCreateFunction0));

		ReflectionClass* tmpClass = new ReflectionClass("InMemorySessionManager", typeid(InMemorySessionManager).name(), typeid(InMemorySessionManager*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
InMemorySessionManager_ReflectionStruct refStructInMemorySessionManager;

