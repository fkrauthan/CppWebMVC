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

boost::any InMemorySessionManagerCallFunction_setSessionIdInCookie2(void* instance, const std::vector<boost::any>& params) {
	((InMemorySessionManager*)instance)->setSessionIdInCookie(boost::any_cast< bool >(params[0]));
	return boost::any(0);
}

boost::any InMemorySessionManagerCallFunction_getSessionIdInCookie3(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((InMemorySessionManager*)instance)->getSessionIdInCookie());
}

boost::any InMemorySessionManagerCallFunction_setSessionIdCookieName4(void* instance, const std::vector<boost::any>& params) {
	((InMemorySessionManager*)instance)->setSessionIdCookieName(boost::any_cast< std::string >(params[0]));
	return boost::any(0);
}

boost::any InMemorySessionManagerCallFunction_getSessionIdCookieName5(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((InMemorySessionManager*)instance)->getSessionIdCookieName());
}

boost::any InMemorySessionManagerCallFunction_setSessionCookieLifeTime6(void* instance, const std::vector<boost::any>& params) {
	((InMemorySessionManager*)instance)->setSessionCookieLifeTime(boost::any_cast< int >(params[0]));
	return boost::any(0);
}

boost::any InMemorySessionManagerCallFunction_getSessionCookieLifeTime7(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((InMemorySessionManager*)instance)->getSessionCookieLifeTime());
}

boost::any InMemorySessionManagerCallFunction_setSessionIdInGetOrPost8(void* instance, const std::vector<boost::any>& params) {
	((InMemorySessionManager*)instance)->setSessionIdInGetOrPost(boost::any_cast< bool >(params[0]));
	return boost::any(0);
}

boost::any InMemorySessionManagerCallFunction_getSessionIdInGetOrPost9(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((InMemorySessionManager*)instance)->getSessionIdInGetOrPost());
}

boost::any InMemorySessionManagerCallFunction_setSessionIdRequestName10(void* instance, const std::vector<boost::any>& params) {
	((InMemorySessionManager*)instance)->setSessionIdRequestName(boost::any_cast< std::string >(params[0]));
	return boost::any(0);
}

boost::any InMemorySessionManagerCallFunction_getSessionIdRequestName11(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((InMemorySessionManager*)instance)->getSessionIdRequestName());
}


struct InMemorySessionManager_ReflectionStruct {
	InMemorySessionManager_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		superClasses.push_back("HttpSession");

		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &InMemorySessionManagerConstructorCreateFunction0));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionIdInCookie", typeid(bool).name(), "bool"));
		functionsHolder.push_back(new ReflectionFunction("setSessionIdInCookie", "void", paramsHolder, &InMemorySessionManagerCallFunction_setSessionIdInCookie2));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getSessionIdInCookie", "bool", paramsHolder, &InMemorySessionManagerCallFunction_getSessionIdInCookie3));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionIdCookieName", typeid(std::string).name(), "std::string"));
		functionsHolder.push_back(new ReflectionFunction("setSessionIdCookieName", "void", paramsHolder, &InMemorySessionManagerCallFunction_setSessionIdCookieName4));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getSessionIdCookieName", "std::string", paramsHolder, &InMemorySessionManagerCallFunction_getSessionIdCookieName5));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionCookieLifeTime", typeid(int).name(), "int"));
		functionsHolder.push_back(new ReflectionFunction("setSessionCookieLifeTime", "void", paramsHolder, &InMemorySessionManagerCallFunction_setSessionCookieLifeTime6));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getSessionCookieLifeTime", "int", paramsHolder, &InMemorySessionManagerCallFunction_getSessionCookieLifeTime7));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionIdInGetOrPost", typeid(bool).name(), "bool"));
		functionsHolder.push_back(new ReflectionFunction("setSessionIdInGetOrPost", "void", paramsHolder, &InMemorySessionManagerCallFunction_setSessionIdInGetOrPost8));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getSessionIdInGetOrPost", "bool", paramsHolder, &InMemorySessionManagerCallFunction_getSessionIdInGetOrPost9));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionIdRequestName", typeid(std::string).name(), "std::string"));
		functionsHolder.push_back(new ReflectionFunction("setSessionIdRequestName", "void", paramsHolder, &InMemorySessionManagerCallFunction_setSessionIdRequestName10));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getSessionIdRequestName", "std::string", paramsHolder, &InMemorySessionManagerCallFunction_getSessionIdRequestName11));


		ReflectionClass* tmpClass = new ReflectionClass("InMemorySessionManager", typeid(InMemorySessionManager).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
InMemorySessionManager_ReflectionStruct refStructInMemorySessionManager;

