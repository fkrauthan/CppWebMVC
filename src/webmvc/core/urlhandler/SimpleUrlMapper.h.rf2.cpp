/*
 * Reflection registration for header: SimpleUrlMapper.h
 *
 *   Created on: 19.07.2010
 *       Author: CodeGenerator V1.0
 */

#include "SimpleUrlMapper.h"
#include <reflections/Reflection.h>
#include <stddef.h>
#include <boost/any.hpp>


void* SimpleUrlMapperConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new SimpleUrlMapper();
}

boost::any SimpleUrlMapperCallFunction_setInterceptors2(void* instance, const std::vector<boost::any>& params) {
	((SimpleUrlMapper*)instance)->setInterceptors(boost::any_cast< std::vector< IInterceptor* > >(params[0]));
	return boost::any(0);
}

boost::any SimpleUrlMapperCallFunction_getInterceptors3(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((SimpleUrlMapper*)instance)->getInterceptors());
}

boost::any SimpleUrlMapperCallFunction_setMappings4(void* instance, const std::vector<boost::any>& params) {
	((SimpleUrlMapper*)instance)->setMappings(boost::any_cast< std::vector< std::pair< std::string, IBasicController* > > >(params[0]));
	return boost::any(0);
}

boost::any SimpleUrlMapperCallFunction_getMappings5(void* instance, const std::vector<boost::any>& params) {
	return boost::any(((SimpleUrlMapper*)instance)->getMappings());
}


struct SimpleUrlMapper_ReflectionStruct {
	SimpleUrlMapper_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		superClasses.push_back("IUrlHandler");

		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &SimpleUrlMapperConstructorCreateFunction0));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("interceptors", typeid(std::vector< IInterceptor* >).name(), "std::vector< IInterceptor* >"));
		functionsHolder.push_back(new ReflectionFunction("setInterceptors", "void", paramsHolder, &SimpleUrlMapperCallFunction_setInterceptors2));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getInterceptors", "std::vector< IInterceptor* >", paramsHolder, &SimpleUrlMapperCallFunction_getInterceptors3));

		paramsHolder.clear();
		paramsHolder.push_back(new ReflectionParam("mappings", typeid(std::vector< std::pair< std::string, IBasicController* > >).name(), "std::vector< std::pair< std::string, IBasicController* > >"));
		functionsHolder.push_back(new ReflectionFunction("setMappings", "void", paramsHolder, &SimpleUrlMapperCallFunction_setMappings4));

		paramsHolder.clear();
		functionsHolder.push_back(new ReflectionFunction("getMappings", "std::vector< std::pair< std::string, IBasicController* > >", paramsHolder, &SimpleUrlMapperCallFunction_getMappings5));


		ReflectionClass* tmpClass = new ReflectionClass("SimpleUrlMapper", typeid(SimpleUrlMapper).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
SimpleUrlMapper_ReflectionStruct refStructSimpleUrlMapper;

