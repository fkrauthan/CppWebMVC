/*
 * ReflectionCTor.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionCTor.h"


ReflectionCTor::ReflectionCTor(const std::vector<ReflectionParam*>& params, void* (*constructorMethod)(const std::vector<boost::any>&), const std::map<std::string, ReflectionAnotation*>& anotations) {
	mParams = params;
	mConstructorMethod = constructorMethod;
	mAnotations = anotations;
}

ReflectionCTor::~ReflectionCTor() {
	for(unsigned int i = 0; i<mParams.size(); i++) {
		delete mParams[i];
	}

	std::map<std::string, ReflectionAnotation*>::iterator iter;
	for(iter=mAnotations.begin(); iter!=mAnotations.end(); ++iter) {
		delete iter->second;
	}
}

std::vector<ReflectionParam*>& ReflectionCTor::getParams() {
	return mParams;
}

void* ReflectionCTor::createInstance(const std::vector<boost::any>& params) {
    return mConstructorMethod(params);
}

const std::map<std::string, ReflectionAnotation*>& ReflectionCTor::getAnotations() {
	return mAnotations;
}

ReflectionAnotation* ReflectionCTor::getAnotation(const std::string& name) {
	std::map<std::string, ReflectionAnotation*>::iterator iter = mAnotations.find(name);
	if(iter==mAnotations.end()) {
		return NULL;
	}

	return iter->second;
}
