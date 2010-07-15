/*
 * Reflection.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "Reflection.h"


Reflection::Reflection() {
}

Reflection::~Reflection() {
	std::map<std::string, ReflectionClass*>::iterator iter;
	for(iter=mRegisteredClasses.begin(); iter!=mRegisteredClasses.end(); ++iter) {
		delete iter->second;
	}
}

void Reflection::registerClass(ReflectionClass* refClass) {
	if(getClass(refClass->getName())) {
		return;
	}

	mRegisteredClasses[refClass->getName()] = refClass;
	mRegisteredClassesByTypeId[refClass->getTypeIdName()] = refClass;
}

ReflectionClass* Reflection::getClass(const std::string& name) {
	std::map<std::string, ReflectionClass*>::iterator iter = mRegisteredClasses.find(name);
	if(iter == mRegisteredClasses.end()) {
		return NULL;
	}

	return iter->second;
}

ReflectionClass* Reflection::getClassByTypeId(const std::string& typeId) {
	std::map<std::string, ReflectionClass*>::iterator iter = mRegisteredClassesByTypeId.find(typeId);
	if(iter == mRegisteredClassesByTypeId.end()) {
		return NULL;
	}

	return iter->second;
}

Reflection& Reflection::getInstance() {
	static Reflection instance;
	return instance;
}
