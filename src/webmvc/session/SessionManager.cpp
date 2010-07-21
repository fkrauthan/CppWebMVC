/*
 * SessionManager.cpp
 *
 *  Created on: 21.07.2010
 *      Author: fkrauthan
 */

#include "SessionManager.h"
#include "idgenerator/SessionIdCounterGenerator.h"
#include "../exceptions/CookieNotFoundException.h"
#include "../exceptions/AttributeNotFoundException.h"


SessionManager::SessionManager() {
	mUseCookies = true;
	mUseRequest = false;

	mCookieName = "cppsession";
	mRequestName = "cppsession";

	mCookieLifeTime = 0;
	mSessionLifeTime = 60;

	mSessionIdGenerator = new SessionIdCounterGenerator();
}

SessionManager::~SessionManager() {
	delete mSessionIdGenerator;
}

void SessionManager::setUseCookies(bool useCookies) {
	mUseCookies = useCookies;
}

bool SessionManager::useCookies() {
	return mUseCookies;
}

void SessionManager::setUserRequest(bool useRequest) {
	mUseRequest = useRequest;
}

bool SessionManager::useRequest() {
	return mUseRequest;
}

void SessionManager::setCookieName(const std::string& cookieName) {
	mCookieName = cookieName;
}

std::string& SessionManager::getCookieName() {
	return mCookieName;
}

void SessionManager::setRequestName(const std::string& requestName) {
	mRequestName = requestName;
}

std::string& SessionManager::getRequestName() {
	return mRequestName;
}

void SessionManager::setCookieLifeTime(int cookieLifeTime) {
	mCookieLifeTime = cookieLifeTime;
}

int SessionManager::getCookieLifeTime() {
	return mCookieLifeTime;
}

void SessionManager::setSessionLifeTime(long sessionLifeTime) {
	mSessionLifeTime = sessionLifeTime;
}

long SessionManager::getSessionLifeTime() {
	return mSessionLifeTime;
}

void SessionManager::setSessionIdGenerator(ISessionIdGenerator* sessionIdGenerator) {
	if(mSessionIdGenerator) {
		delete mSessionIdGenerator;
	}

	mSessionIdGenerator = sessionIdGenerator;
}

ISessionIdGenerator* SessionManager::getSessionIdGenerator() {
	return mSessionIdGenerator;
}

HttpSession* SessionManager::startSession(const HttpRequest& request, HttpResponse& response) {
	cleanUpOldSessions();


	HttpSession* session = NULL;
	if(mUseCookies) {
		try {
			const HttpCookie& sessionCookie = request.getCookie(mCookieName);
			session = startSessionInternal(sessionCookie.getValue(), true, request, response);
		} catch(const CookieNotFoundException& ex) {
		}
	}
	if(!session && mUseRequest) {
		try {
			session = startSessionInternal(request.getAttribute(mRequestName), true, request, response);
		} catch(const AttributeNotFoundException& ex) {
		}
	}
	if(!session) {
		session = startSessionInternal(generateSessionId(request, response), false, request, response);
	}


	if(mUseCookies && session) {
		if(mCookieLifeTime > 0) {
			response.addCookie(HttpCookie(mCookieName, session->getId(), mCookieLifeTime));
		}
		else {
			response.addCookie(HttpCookie(mCookieName, session->getId()));
		}
	}


	return session;
}

std::string SessionManager::generateSessionId(const HttpRequest& request, HttpResponse& response) {
	return mSessionIdGenerator->generateSessionId(this, request, response);
}
