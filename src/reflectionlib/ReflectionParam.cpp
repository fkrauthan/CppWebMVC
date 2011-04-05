/*
 * ReflectionParam.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionParam.h"


ReflectionParam::ReflectionParam(const std::string& name, const std::string& typeIdName, const std::string& type) {
	mName = name;
	mTypeIdName = typeIdName;
	mType = type;
}

ReflectionParam::~ReflectionParam() {
}

std::string& ReflectionParam::getName() {
	return mName;
}

std::string& ReflectionParam::getTypeIdName() {
	return mTypeIdName;
}

std::string& ReflectionParam::getType() {
	return mType;
}
