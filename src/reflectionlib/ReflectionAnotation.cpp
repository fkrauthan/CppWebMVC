/*
 * ReflectionAnotation.cpp
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#include "ReflectionAnotation.h"


ReflectionAnotation::ReflectionAnotation(const std::string& name, const std::map<std::string, std::string>& params)
	: mName(name), mParams(params) {
}

ReflectionAnotation::~ReflectionAnotation() {
}

std::string& ReflectionAnotation::getName() {
	return mName;
}

std::string ReflectionAnotation::getParam(const std::string& name, std::string defaultValue) {
	std::map<std::string, std::string>::iterator iter = mParams.find(name);
	if(iter != mParams.end()) {
		return iter->second;
	}

	return defaultValue;
}

const std::map<std::string, std::string>& ReflectionAnotation::getParams() {
	return mParams;
}

bool ReflectionAnotation::hasParam(const std::string& name) {
	std::map<std::string, std::string>::iterator iter = mParams.find(name);
	if(iter != mParams.end()) {
		return true;
	}

	return false;
}
