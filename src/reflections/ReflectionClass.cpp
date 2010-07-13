/*
 * ReflectionClass.cpp
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#include "ReflectionClass.h"
#include <iostream>

ReflectionClass::ReflectionClass(const std::string& name, const std::vector<std::string>& superClasses, const std::vector<ReflectionCTor*>& ctors, const std::vector<ReflectionFunction*>& functions) {
	mName = name;
	mSuperClasses = superClasses;
	mCTors = ctors;
	mMemberFunctions = functions;

	for(unsigned int i=0; i<mMemberFunctions.size(); i++) {
		mSortedMemberFunctions[mMemberFunctions[i]->getName()].push_back(mMemberFunctions[i]);
	}
}

ReflectionClass::~ReflectionClass() {
	for(unsigned int i=0; i<mMemberFunctions.size(); i++) {
		delete mMemberFunctions[i];
	}
}

std::string& ReflectionClass::getName() {
	return mName;
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
