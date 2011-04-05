/*
 * ReflectionFunction.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionFunction.h"


ReflectionFunction::ReflectionFunction(const std::string& name, const std::string& retType, const std::vector<ReflectionParam*>& params, boost::any (*invokeFunction)(void*, const std::vector<boost::any>&), const std::map<std::string, ReflectionAnotation*>& anotations) {
	mName = name;
	mRetType = retType;
	mParams = params;
	mInvoke = invokeFunction;
	mAnotations = anotations;
}

ReflectionFunction::~ReflectionFunction() {
	for(unsigned int i = 0; i<mParams.size(); i++) {
		delete mParams[i];
	}

	std::map<std::string, ReflectionAnotation*>::iterator iter;
	for(iter=mAnotations.begin(); iter!=mAnotations.end(); ++iter) {
		delete iter->second;
	}
}

std::string& ReflectionFunction::getName() {
	return mName;
}

std::string& ReflectionFunction::getRetType() {
	return mRetType;
}

std::vector<ReflectionParam*>& ReflectionFunction::getParams() {
	return mParams;
}

void ReflectionFunction::invoke(void* instance, const std::vector<boost::any>& params) {
	mInvoke(instance, params);
}

const std::map<std::string, ReflectionAnotation*>& ReflectionFunction::getAnotations() {
	return mAnotations;
}

ReflectionAnotation* ReflectionFunction::getAnotation(const std::string& name) {
	std::map<std::string, ReflectionAnotation*>::iterator iter = mAnotations.find(name);
	if(iter==mAnotations.end()) {
		return NULL;
	}

	return iter->second;
}
