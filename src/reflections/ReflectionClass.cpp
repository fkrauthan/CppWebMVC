/*
 * ReflectionClass.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionClass.h"
#include <iostream>

ReflectionClass::ReflectionClass(const std::string& name, const std::string& typeIdName, const std::vector<std::string>& superClasses, const std::vector<ReflectionCTor*>& ctors, const std::vector<ReflectionFunction*>& functions, std::vector<ReflectionMember*> vars, ClassType classType) {
	mName = name;
	mTypeIdName = typeIdName;
	mSuperClasses = superClasses;
	mCTors = ctors;
	mMemberFunctions = functions;
	mMemberVars = vars;
	mClassType = classType;

	for(unsigned int i=0; i<mMemberFunctions.size(); i++) {
		mSortedMemberFunctions[mMemberFunctions[i]->getName()].push_back(mMemberFunctions[i]);
	}
}

ReflectionClass::~ReflectionClass() {
	for(unsigned int i=0; i<mMemberFunctions.size(); i++) {
		delete mMemberFunctions[i];
	}

	for(unsigned int i=0; i<mMemberVars.size(); i++) {
		delete mMemberVars[i];
	}
}

std::string& ReflectionClass::getName() {
	return mName;
}

std::string& ReflectionClass::getTypeIdName() {
	return mTypeIdName;
}

std::vector<std::string>& ReflectionClass::getSuperClasses() {
	return mSuperClasses;
}

std::vector<ReflectionCTor*>& ReflectionClass::getCTors() {
	return mCTors;
}

std::vector<ReflectionFunction*>& ReflectionClass::getMemberFunctions() {
	return mMemberFunctions;
}

std::vector<ReflectionFunction*> ReflectionClass::getMemberFunctions(const std::string& name) {
	std::map<std::string, std::vector<ReflectionFunction*> >::iterator iter = mSortedMemberFunctions.find(name);
	if(iter == mSortedMemberFunctions.end()) {
		return std::vector<ReflectionFunction*>();
	}

	return iter->second;
}

std::vector<ReflectionMember*>& ReflectionClass::getMemberVars() {
	return mMemberVars;
}

ReflectionMember* ReflectionClass::getMemberVar(const std::string& name) {
	for(unsigned int i=0; i<mMemberVars.size(); i++) {
		if(mMemberVars[i]->getName() == name) {
			return mMemberVars[i];
		}
	}

	return NULL;
}

ReflectionClass::ClassType ReflectionClass::getClassType() {
	return mClassType;
}
