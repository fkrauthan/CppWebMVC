/*
 * ReflectionMember.cpp
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#include "ReflectionMember.h"


ReflectionMember::ReflectionMember(const std::string& name, const std::string& typeIdName, const std::string& type, int offset) {
	mName = name;
	mTypeIdName = typeIdName;
	mType = type;
	mOffset = offset;
}

ReflectionMember::~ReflectionMember() {
}

std::string& ReflectionMember::getName() {
	return mName;
}

std::string& ReflectionMember::getTypeIdName() {
	return mTypeIdName;
}

std::string& ReflectionMember::getType() {
	return mType;
}

int ReflectionMember::getOffset() {
	return mOffset;
}
