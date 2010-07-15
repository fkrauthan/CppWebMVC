/*
 * TextSession.cpp
 *
 *  Created on: 14.07.2010
 *      Author: fkrauthan
 */

#include "TextSession.h"
#include "../exceptions/AttributeNotFoundException.h"


TextSession::TextSession() {
}

TextSession::~TextSession() {

}

std::string& TextSession::getId() {
	return mId;
}

std::string& TextSession::getAttribute(const std::string& name) {
	std::map<std::string, std::string>::iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		throw AttributeNotFoundException("The attribute with name \""+name+"\" was not found");
	}

	return iter->second;
}

std::vector<std::string> TextSession::getAttributeNames() {
	std::vector<std::string> tmpRet;
	std::map<std::string, std::string>::const_iterator iter;
	for(iter=mAttributes.begin(); iter!=mAttributes.end(); ++iter) {
		tmpRet.push_back(iter->first);
	}

	return tmpRet;
}

bool TextSession::hasAttribute(const std::string& name) {
	std::map<std::string, std::string>::const_iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		return false;
	}

	return true;
}

long TextSession::getCreationTime() {
	return mCreationTime;
}

long TextSession::getLastAccessedTime() {
	return mLastAccessdTime;
}

int TextSession::getMaxInactiveInterval() {
	return mMaxInactiveInterval;
}

bool TextSession::isNew() {
	return mNew;
}

void TextSession::removeAttribute(const std::string& name) {
	std::map<std::string, std::string>::iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		return;
	}

	mAttributes.erase(iter);
}

void TextSession::setAttribute(const std::string& name, const std::string& value) {
	mAttributes[name] = value;
}

void TextSession::invalidate() {
	mInvalidated = true;
}

void TextSession::startNewSession() {
	//TODO: session starten
}
