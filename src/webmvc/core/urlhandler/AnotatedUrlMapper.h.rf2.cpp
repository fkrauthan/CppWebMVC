/*
 * Reflection registration for header: AnotatedUrlMapper.h
 *
 *   Created on: 05.04.2011
 *       Author: CodeGenerator V2.0
 */

#include "AnotatedUrlMapper.h"
#include <reflectionlib/Reflection.h>
#include <reflectionlib/ReflectionConverter.h>
#include <vector>
#include <stddef.h>
#include <boost/any.hpp>
#include <serializationlib/Serializer.h>
#include <serializationlib/MapDataConverter.h>
#include <serializationlib/PairDataConverter.h>
#include <serializationlib/VectorDataConverter.h>

void* AnotatedUrlMapperConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new AnotatedUrlMapper(boost::any_cast< bool >(params[0]));
}

boost::any AnotatedUrlMapperCallFunction_setSearchForAnotatedClasses2(void* instance, const std::vector<boost::any>& params) {
	((AnotatedUrlMapper*)instance)->setSearchForAnotatedClasses(boost::any_cast< bool >(params[0]));
	return boost::any(0);
}

boost::any AnotatedUrlMapperCallFunction_getSearchForAnotatedClasses3(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((AnotatedUrlMapper*)instance)->getSearchForAnotatedClasses());
}

boost::any AnotatedUrlMapperCallFunction_setInterceptors4(void* instance, const std::vector<boost::any>& params) {
	((AnotatedUrlMapper*)instance)->setInterceptors(ReflectionConverter::convertVector<IInterceptor*>(boost::any_cast<std::vector<boost::any> >(params[0])));
	return boost::any(0);
}

boost::any AnotatedUrlMapperCallFunction_getInterceptors5(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((AnotatedUrlMapper*)instance)->getInterceptors());
}

boost::any AnotatedUrlMapperCallFunction_setClasses6(void* instance, const std::vector<boost::any>& params) {
	((AnotatedUrlMapper*)instance)->setClasses(ReflectionConverter::convertVector<IObject*>(boost::any_cast<std::vector<boost::any> >(params[0])));
	return boost::any(0);
}

boost::any AnotatedUrlMapperCallFunction_getClasses7(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((AnotatedUrlMapper*)instance)->getClasses());
}

boost::any AnotatedUrlMapperCallFunction_dispatchUrl8(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((AnotatedUrlMapper*)instance)->dispatchUrl(boost::any_cast< HttpRequest >(params[0]), boost::any_cast< HttpResponse >(params[1])));
}


struct AnotatedUrlMapper_ReflectionStruct {
	AnotatedUrlMapper_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		std::map<std::string, std::string> paramsMap;
		std::map<std::string, ReflectionAnotation*> anotationsHolder;

		superClasses.push_back("IUrlHandler");

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("search=false", typeid(bool).name(), "bool"));
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &AnotatedUrlMapperConstructorCreateFunction0, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("search", typeid(bool).name(), "bool"));
		functionsHolder.push_back(new ReflectionFunction("setSearchForAnotatedClasses", "void", paramsHolder, &AnotatedUrlMapperCallFunction_setSearchForAnotatedClasses2, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getSearchForAnotatedClasses", "bool", paramsHolder, &AnotatedUrlMapperCallFunction_getSearchForAnotatedClasses3, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("interceptors", typeid(std::vector< IInterceptor* >).name(), "std::vector< IInterceptor* >"));
		functionsHolder.push_back(new ReflectionFunction("setInterceptors", "void", paramsHolder, &AnotatedUrlMapperCallFunction_setInterceptors4, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getInterceptors", "std::vector< IInterceptor* >", paramsHolder, &AnotatedUrlMapperCallFunction_getInterceptors5, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("classes", typeid(std::vector< IObject* >).name(), "std::vector< IObject* >"));
		functionsHolder.push_back(new ReflectionFunction("setClasses", "void", paramsHolder, &AnotatedUrlMapperCallFunction_setClasses6, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getClasses", "std::vector< IObject* >", paramsHolder, &AnotatedUrlMapperCallFunction_getClasses7, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("request", typeid(HttpRequest).name(), "HttpRequest"));
		paramsHolder.push_back(new ReflectionParam("response", typeid(HttpResponse).name(), "HttpResponse"));
		functionsHolder.push_back(new ReflectionFunction("dispatchUrl", "bool", paramsHolder, &AnotatedUrlMapperCallFunction_dispatchUrl8, anotationsHolder));


		anotationsHolder.clear();
		ReflectionClass* tmpClass = new ReflectionClass("AnotatedUrlMapper", typeid(AnotatedUrlMapper).name(), typeid(AnotatedUrlMapper*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS, anotationsHolder);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
AnotatedUrlMapper_ReflectionStruct refStructAnotatedUrlMapper;


