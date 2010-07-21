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
}

HttpSession* SessionManager::startSession(const HttpRequest& request, HttpResponse& response) {
	cleanUpOldSessions();


	HttpSession* session = NULL;
	if(mUseCookies) {
		try {
			const HttpCookie& sessionCookie = request.getCookie(mCookieName);
			session = startSessionInternal(sessionCookie.getValue(), true);
		} catch(const CookieNotFoundException& ex) {
		}
	}
	if(!session && mUseRequest) {
		try {
			session = startSessionInternal(request.getAttribute(mRequestName), true);
		} catch(const AttributeNotFoundException& ex) {
		}
	}
	if(!session) {
		session = startSessionInternal(generateSessionId(request, response), false);
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
