/*
 * ReflectionMember.cpp
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#include "ReflectionMember.h"


ReflectionMember::ReflectionMember(const std::string& name, const std::string& typeIdName, const std::string& type, int offset, const std::map<std::string, ReflectionAnotation*>& anotations) {
	mName = name;
	mTypeIdName = typeIdName;
	mType = type;
	mOffset = offset;
	mAnotations = anotations;
}

ReflectionMember::~ReflectionMember() {
	std::map<std::string, ReflectionAnotation*>::iterator iter;
	for(iter=mAnotations.begin(); iter!=mAnotations.end(); ++iter) {
		delete iter->second;
	}
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

const std::map<std::string, ReflectionAnotation*>& ReflectionMember::getAnotations() {
	return mAnotations;
}

ReflectionAnotation* ReflectionMember::getAnotation(const std::string& name) {
	std::map<std::string, ReflectionAnotation*>::iterator iter = mAnotations.find(name);
	if(iter==mAnotations.end()) {
		return NULL;
	}

	return iter->second;
}
