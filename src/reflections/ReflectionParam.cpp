/*
 * ReflectionParam.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionParam.h"


ReflectionParam::ReflectionParam(const std::string& name, const std::string& type) {
	mName = name;
	mType = type;
}

ReflectionParam::~ReflectionParam() {
}

std::string& ReflectionParam::getName() {
	return mName;
}

std::string& ReflectionParam::getType() {
	return mType;
}
