/*
 * Reflection registration for header: Application.h
 *
 *   Created on: 05.04.2011
 *       Author: CodeGenerator V2.0
 */

#include "Application.h"
#include <reflectionlib/Reflection.h>
#include <reflectionlib/ReflectionConverter.h>
#include <vector>
#include <stddef.h>
#include <boost/any.hpp>
#include <serializationlib/Serializer.h>
#include <serializationlib/MapDataConverter.h>
#include <serializationlib/PairDataConverter.h>
#include <serializationlib/VectorDataConverter.h>

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

boost::any ApplicationCallFunction_handleRequest6(void* instance, const std::vector<boost::any>& params) {
	((Application*)instance)->handleRequest(boost::any_cast< boost::function< void* >* >(params[0]));
	return boost::any(0);
}


struct Application_ReflectionStruct {
	Application_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		std::map<std::string, std::string> paramsMap;
		std::map<std::string, ReflectionAnotation*> anotationsHolder;

		superClasses.push_back("IApplication");

		anotationsHolder.clear();
		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &ApplicationConstructorCreateFunction0, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getBeanFactory", "BeanFactory*", paramsHolder, &ApplicationCallFunction_getBeanFactory2, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("beanFactory", typeid(BeanFactory*).name(), "BeanFactory*"));
		functionsHolder.push_back(new ReflectionFunction("setBeanFactory", "void", paramsHolder, &ApplicationCallFunction_setBeanFactory3, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("size", typeid(int).name(), "int"));
		functionsHolder.push_back(new ReflectionFunction("setThreadPoolSize", "void", paramsHolder, &ApplicationCallFunction_setThreadPoolSize4, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("sessionManager", typeid(SessionManager*).name(), "SessionManager*"));
		functionsHolder.push_back(new ReflectionFunction("setSessionManager", "void", paramsHolder, &ApplicationCallFunction_setSessionManager5, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("", typeid(boost::function< void* >*).name(), "boost::function< void* >*"));
		functionsHolder.push_back(new ReflectionFunction("handleRequest", "void", paramsHolder, &ApplicationCallFunction_handleRequest6, anotationsHolder));


		anotationsHolder.clear();
		ReflectionClass* tmpClass = new ReflectionClass("Application", typeid(Application).name(), typeid(Application*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS, anotationsHolder);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
Application_ReflectionStruct refStructApplication;


