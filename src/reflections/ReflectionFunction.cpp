/*
 * ReflectionFunction.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionFunction.h"


ReflectionFunction::ReflectionFunction(const std::string& name, const std::string& retType, const std::vector<ReflectionParam*>& params, boost::any (*invokeFunction)(void*, const std::vector<boost::any>&)) {
	mName = name;
	mRetType = retType;
	mParams = params;
	mInvoke = invokeFunction;
}

ReflectionFunction::~ReflectionFunction() {
	for(unsigned int i = 0; i<mParams.size(); i++) {
		delete mParams[i];
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
