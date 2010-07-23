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
	mRegisteredClassesByPointerTypeId[refClass->getPointerTypeIdName()] = refClass;
}

ReflectionClass* Reflection::getClass(const std::string& name) {
	std::map<std::string, ReflectionClass*>::iterator iter = mRegisteredClasses.find(name);
	if(iter == mRegisteredClasses.end()) {
		return NULL;
	}

	return iter->second;
}

ReflectionClass* Reflection::getClassByTypeId(const std::string& typeId, bool* pointer) {
	if(pointer) {
		*pointer = true;
	}

	std::map<std::string, ReflectionClass*>::iterator iter = mRegisteredClassesByTypeId.find(typeId);
	if(iter == mRegisteredClassesByTypeId.end()) {
		iter = mRegisteredClassesByPointerTypeId.find(typeId);
		if(iter == mRegisteredClassesByPointerTypeId.end()) {
			return NULL;
		}
		else {
			return iter->second;
		}
	}
	else {
		if(pointer) {
			*pointer = false;
		}

		return iter->second;
	}
}

Reflection& Reflection::getInstance() {
	static Reflection instance;
	return instance;
}
