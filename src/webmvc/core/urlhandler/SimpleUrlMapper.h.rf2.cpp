/*
 * Reflection registration for header: SimpleUrlMapper.h
 *
 *   Created on: 05.04.2011
 *       Author: CodeGenerator V2.0
 */

#include "SimpleUrlMapper.h"
#include <reflectionlib/Reflection.h>
#include <reflectionlib/ReflectionConverter.h>
#include <vector>
#include <stddef.h>
#include <boost/any.hpp>
#include <serializationlib/Serializer.h>
#include <serializationlib/MapDataConverter.h>
#include <serializationlib/PairDataConverter.h>
#include <serializationlib/VectorDataConverter.h>

void* SimpleUrlMapperConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new SimpleUrlMapper();
}

boost::any SimpleUrlMapperCallFunction_setInterceptors2(void* instance, const std::vector<boost::any>& params) {
	((SimpleUrlMapper*)instance)->setInterceptors(ReflectionConverter::convertVector<IInterceptor*>(boost::any_cast<std::vector<boost::any> >(params[0])));
	return boost::any(0);
}

boost::any SimpleUrlMapperCallFunction_getInterceptors3(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((SimpleUrlMapper*)instance)->getInterceptors());
}

boost::any SimpleUrlMapperCallFunction_setMappings4(void* instance, const std::vector<boost::any>& params) {
	((SimpleUrlMapper*)instance)->setMappings(ReflectionConverter::convertVectorPairWithPointer<std::string, IBasicController*>(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[0])));
	return boost::any(0);
}

boost::any SimpleUrlMapperCallFunction_getMappings5(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((SimpleUrlMapper*)instance)->getMappings());
}

boost::any SimpleUrlMapperCallFunction_dispatchUrl6(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((SimpleUrlMapper*)instance)->dispatchUrl(boost::any_cast< HttpRequest >(params[0]), boost::any_cast< HttpResponse >(params[1])));
}


struct SimpleUrlMapper_ReflectionStruct {
	SimpleUrlMapper_ReflectionStruct() {
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
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &SimpleUrlMapperConstructorCreateFunction0, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("interceptors", typeid(std::vector< IInterceptor* >).name(), "std::vector< IInterceptor* >"));
		functionsHolder.push_back(new ReflectionFunction("setInterceptors", "void", paramsHolder, &SimpleUrlMapperCallFunction_setInterceptors2, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getInterceptors", "std::vector< IInterceptor* >", paramsHolder, &SimpleUrlMapperCallFunction_getInterceptors3, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("mappings", typeid(std::vector< std::pair< std::string, IBasicController* > >).name(), "std::vector< std::pair< std::string, IBasicController* > >"));
		functionsHolder.push_back(new ReflectionFunction("setMappings", "void", paramsHolder, &SimpleUrlMapperCallFunction_setMappings4, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getMappings", "std::vector< std::pair< std::string, IBasicController* > >", paramsHolder, &SimpleUrlMapperCallFunction_getMappings5, anotationsHolder));

		anotationsHolder.clear();
		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("request", typeid(HttpRequest).name(), "HttpRequest"));
		paramsHolder.push_back(new ReflectionParam("response", typeid(HttpResponse).name(), "HttpResponse"));
		functionsHolder.push_back(new ReflectionFunction("dispatchUrl", "bool", paramsHolder, &SimpleUrlMapperCallFunction_dispatchUrl6, anotationsHolder));


		anotationsHolder.clear();
		ReflectionClass* tmpClass = new ReflectionClass("SimpleUrlMapper", typeid(SimpleUrlMapper).name(), typeid(SimpleUrlMapper*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS, anotationsHolder);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
SimpleUrlMapper_ReflectionStruct refStructSimpleUrlMapper;


