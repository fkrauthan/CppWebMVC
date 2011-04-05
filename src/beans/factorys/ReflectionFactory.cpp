/*
 * ReflectionFactory.cpp
 *
 *  Created on: 16.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionFactory.h"
#include "../BeanFactoryException.h"
#include <reflectionlib/Reflection.h>
#include <algorithm>
#include <vector>
#include <iostream>


ReflectionFactory::ReflectionFactory() {
	BeanFactoryManager::getInstance().registerFactory("ReflectionFactory", this);
}

ReflectionFactory::~ReflectionFactory() {
	BeanFactoryManager::getInstance().deRegisterFactory("ReflectionFactory");
}

IObject* ReflectionFactory::getInstance(BeanDef* def, BeanFactory* factory) {
	ReflectionClass* refClass = Reflection::getInstance().getClass(def->className);
	if(!refClass) {
		throw BeanFactoryException("Can't find class with classname "+def->className);
	}

	//Find cTor
	const std::vector<ReflectionCTor*>& cTors = refClass->getCTors();
	ReflectionCTor* cTor = NULL;
	for(unsigned int i=0; i<cTors.size(); i++) {
		if(cTors[i]->getParams().size() == def->constructorParameter.size()) {
			cTor = cTors[i];
			break;
		}
	}
	if(!cTor) {
		throw BeanFactoryException("Can't find matching ctor for class "+def->className);
	}

	//Call CTor
	std::vector<boost::any> params;
	const std::vector<ReflectionParam*>& cTorParams = cTor->getParams();
	for(unsigned int i=0; i<cTorParams.size(); i++) {
		params.push_back(factory->convertStringtoBoostAny(def->constructorParameter[i], cTorParams[i]->getType()));
	}
	IObject* tmpInstance = cTor->createInstance<IObject>(params);
	if(!tmpInstance) {
		throw BeanFactoryException("Can't create a instance of class "+def->className);
	}

	//Call Setter
	std::map<std::string, BeanProperty>::iterator iter;
	for(iter = def->propertieParameter.begin(); iter!=def->propertieParameter.end(); ++iter) {
		std::string functionName = iter->first;
		std::transform(functionName.begin(), functionName.begin()+1, functionName.begin(), ::toupper);
		std::vector<ReflectionFunction*> functions = refClass->getMemberFunctions("set"+functionName);
		ReflectionFunction* function = NULL;
		for(unsigned int i=0; i<functions.size(); i++) {
			if(functions[i]->getParams().size()==1) {
				function = functions[i];
				break;
			}
		}
		if(!function) {
			//TODO Exception?
			continue;
		}
		params.clear();
		params.push_back(factory->convertStringtoBoostAny(iter->second, function->getParams()[0]->getType()));
		function->invoke(tmpInstance, params);
	}

	return tmpInstance;
}


//Register a instance
ReflectionFactory reflectionFactoryInstance;
