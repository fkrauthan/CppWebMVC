/*
 * HttpCookie.cpp
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#include "HttpCookie.h"


HttpCookie::HttpCookie(const std::string& name, const std::string& value, int maxAge, const std::string& path, const std::string& domain) :
	mName(name),
	mValue(value),
	mPath(path),
	mDomain(domain),
	mMaxAge(maxAge) {
}

const std::string& HttpCookie::getDomain() const {
	return mDomain;
}

const std::string& HttpCookie::getName() const {
	return mName;
}

const std::string& HttpCookie::getPath() const {
	return mPath;
}

int HttpCookie::getMaxAge() const {
	return mMaxAge;
}

const std::string& HttpCookie::getValue() const {
	return mValue;
}

void HttpCookie::setDomain(const std::string& domain) {
	mDomain = domain;
}

void HttpCookie::setName(const std::string& name) {
	mName = name;
}

void HttpCookie::setPath(const std::string& path) {
	mPath = path;
}

void HttpCookie::setValue(const std::string& value) {
	mValue = value;
}

void HttpCookie::setMaxAge(int expiry) {
	mMaxAge = expiry;
}
