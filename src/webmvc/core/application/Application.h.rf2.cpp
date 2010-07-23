/*
 * Reflection registration for header: Application.h
 *
 *   Created on: 20.07.2010
 *       Author: CodeGenerator V1.0
 */

#include "Application.h"
#include <reflections/Reflection.h>
#include <reflections/ReflectionConverter.h>
#include <stddef.h>
#include <boost/any.hpp>


void* ApplicationConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new Application();
}

boost::any ApplicationCallFunction_getBeanFactory2(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((Application*)instance)->getBeanFactory());
}

boost::any ApplicationCallFunction_setBeanFactory3(void* instance, const std::vector<boost::any>& params) {
	((Application*)instance)->setBeanFactory(ReflectionConverter::convertPointer<BeanFactory*>(params[0]));
	return boost::any(0);
}

boost::any ApplicationCallFunction_setThreadPoolSize4(void* instance, const std::vector<boost::any>& params) {
	((Application*)instance)->setThreadPoolSize(boost::any_cast< int >(params[0]));
	return boost::any(0);
}

boost::any ApplicationCallFunction_setSessionManager5(void* instance, const std::vector<boost::any>& params) {
	((Application*)instance)->setSessionManager(ReflectionConverter::convertPointer<SessionManager*>(params[0]));
	return boost::any(0);
}


struct Application_ReflectionStruct {
	Application_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		superClasses.push_back("IApplication");

		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &ApplicationConstructorCreateFunction0));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getBeanFactory", "BeanFactory*", paramsHolder, &ApplicationCallFunction_getBeanFactory2));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("beanFactory", typeid(BeanFactory*).name(), "BeanFactory*"));
		functionsHolder.push_back(new ReflectionFunction("setBeanFactory", "void", paramsHolder, &ApplicationCallFunction_setBeanFactory3));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("size", typeid(int).name(), "int"));
		functionsHolder.push_back(new ReflectionFunction("setThreadPoolSize", "void", paramsHolder, &ApplicationCallFunction_setThreadPoolSize4));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionManager", typeid(SessionManager*).name(), "SessionManager*"));
		functionsHolder.push_back(new ReflectionFunction("setSessionManager", "void", paramsHolder, &ApplicationCallFunction_setSessionManager5));


		ReflectionClass* tmpClass = new ReflectionClass("Application", typeid(Application).name(), typeid(Application*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
Application_ReflectionStruct refStructApplication;

