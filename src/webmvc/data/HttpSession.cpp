/*
 * HttpSession.cpp
 *
 *  Created on: 18.07.2010
 *      Author: fkrauthan
 */

#include "HttpSession.h"
#include "../exceptions/AttributeNotFoundException.h"


HttpSession::HttpSession(const std::string& id, long creationTime, long lastAccessTime, bool isNew, const std::map<std::string, std::string>& attributes) :
	mId(id), mCreationTime(creationTime), mLastAccessdTime(lastAccessTime), mNew(isNew), mInvalidated(false), mAttributes(attributes) {
}

HttpSession::~HttpSession() {

}

std::string& HttpSession::getId() {
	return mId;
}

std::string& HttpSession::getAttribute(const std::string& name) {
	std::map<std::string, std::string>::iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		throw AttributeNotFoundException("The attribute with name \""+name+"\" was not found");
	}

	return iter->second;
}

std::map<std::string, std::string>& HttpSession::getAttributes() {
	return mAttributes;
}

std::vector<std::string> HttpSession::getAttributeNames() {
	std::vector<std::string> tmpRet;
	std::map<std::string, std::string>::const_iterator iter;
	for(iter=mAttributes.begin(); iter!=mAttributes.end(); ++iter) {
		tmpRet.push_back(iter->first);
	}

	return tmpRet;
}

bool HttpSession::hasAttribute(const std::string& name) {
	std::map<std::string, std::string>::const_iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		return false;
	}

	return true;
}

long HttpSession::getCreationTime() {
	return mCreationTime;
}

long HttpSession::getLastAccessedTime() {
	return mLastAccessdTime;
}

bool HttpSession::isNew() {
	return mNew;
}

void HttpSession::removeAttribute(const std::string& name) {
	std::map<std::string, std::string>::iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		return;
	}

	mAttributes.erase(iter);
}

void HttpSession::setAttribute(const std::string& name, const std::string& value) {
	mAttributes[name] = value;
}

void HttpSession::invalidate() {
	mInvalidated = true;
}

bool HttpSession::isInvalid() {
	return mInvalidated;
}
