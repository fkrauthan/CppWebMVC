/*
 * ReflectionCTor.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionCTor.h"


ReflectionCTor::ReflectionCTor(const std::vector<ReflectionParam*>& params, void* (*constructorMethod)(const std::vector<boost::any>&)) {
	mParams = params;
	mConstructorMethod = constructorMethod;
}

ReflectionCTor::~ReflectionCTor() {
	for(unsigned int i = 0; i<mParams.size(); i++) {
		delete mParams[i];
	}
}

std::vector<ReflectionParam*>& ReflectionCTor::getParams() {
	return mParams;
}

void* ReflectionCTor::createInstance(const std::vector<boost::any>& params) {
    return mConstructorMethod(params);
}
