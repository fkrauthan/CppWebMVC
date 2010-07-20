/*
 * InMemorySessionManager.cpp
 *
 *  Created on: 20.07.2010
 *      Author: fkrauthan
 */

#include "InMemorySessionManager.h"
#include "../exceptions/CookieNotFoundException.h"
#include "../exceptions/AttributeNotFoundException.h"


InMemorySessionManager::InMemorySessionManager() {
	mSessionIdInCookie = true;
	mSessionIdInGetOrPost = false;
	nextSessionId = 0;
	mSessionIdCookieName = "CPPSESSION";
	mSessionIdRequestName = "cppsession";
	mSessionCookieLifeTime = 0;

	mMaxInactiveInterval = 30;
}

InMemorySessionManager::InMemorySessionManager(InMemorySessionManager* manager) {
	mManager = manager;
}

InMemorySessionManager::~InMemorySessionManager() {
	std::map<std::string, InMemorySessionManager*>::iterator iter;
	for(iter = mSessionStorage.begin(); iter!=mSessionStorage.end(); ++iter) {
		delete iter->second;
	}
}

void InMemorySessionManager::setSessionIdInCookie(bool sessionIdInCookie) {
	mSessionIdInCookie = sessionIdInCookie;
}

bool InMemorySessionManager::getSessionIdInCookie() {
	return mSessionIdInCookie;
}

void InMemorySessionManager::setSessionIdCookieName(const std::string& sessionIdCookieName) {
	mSessionIdCookieName = sessionIdCookieName;
}

std::string& InMemorySessionManager::getSessionIdCookieName() {
	return mSessionIdCookieName;
}

void InMemorySessionManager::setSessionCookieLifeTime(int sessionCookieLifeTime) {
	mSessionCookieLifeTime = sessionCookieLifeTime;
}

int InMemorySessionManager::getSessionCookieLifeTime() {
	return mSessionCookieLifeTime;
}

void InMemorySessionManager::setSessionIdInGetOrPost(bool sessionIdInGetOrPost) {
	mSessionIdInGetOrPost = sessionIdInGetOrPost;
}

bool InMemorySessionManager::getSessionIdInGetOrPost() {
	return mSessionIdInGetOrPost;
}

void InMemorySessionManager::setSessionIdRequestName(const std::string& sessionIdRequestName) {
	mSessionIdRequestName = sessionIdRequestName;
}

std::string& InMemorySessionManager::getSessionIdRequestName() {
	return mSessionIdRequestName;
}

HttpSession* InMemorySessionManager::createSession(const HttpRequest& request, HttpResponse& response) {
	clearOldSessions();


	InMemorySessionManager* session = NULL;
	if(mSessionIdInCookie) {
		try {
			const HttpCookie& sessionCookie = request.getCookie(mSessionIdCookieName);
			session = getSessionWithId(sessionCookie.getValue());
			if(session) {
				session->initSession(false);
			}
		} catch(const CookieNotFoundException& ex) {
		}
	}
	if(!session && mSessionIdInGetOrPost) {
		try {
			session = getSessionWithId(request.getAttribute(mSessionIdRequestName));
			if(session) {
				session->initSession(false);
			}
		} catch(const AttributeNotFoundException& ex) {
		}
	}

	if(!session) {
		nextSessionId++;
		std::stringstream str;
		str << "SESSION_" << nextSessionId;

		session = new InMemorySessionManager(this);
		session->initSession(true, str.str());
		mSessionStorage[str.str()] = session;


		if(mSessionIdInCookie) {
			if(mSessionCookieLifeTime>0) {
				response.addCookie(HttpCookie(mSessionIdCookieName, str.str(), mSessionCookieLifeTime));
			}
			else {
				response.addCookie(HttpCookie(mSessionIdCookieName, str.str()));
			}
		}
	}

	return session;
}

void InMemorySessionManager::removeSession(HttpSession* session) {
	if(session->isInvalid()) {
		std::map<std::string, InMemorySessionManager*>::iterator iter = mSessionStorage.find(session->getId());
		if(iter!=mSessionStorage.end()) {
			delete iter->second;
			mSessionStorage.erase(iter);
		}
	}
}

InMemorySessionManager* InMemorySessionManager::getSessionWithId(const std::string& sessionId) {
	std::map<std::string, InMemorySessionManager*>::iterator iter = mSessionStorage.find(sessionId);
	if(iter==mSessionStorage.end()) {
		return NULL;
	}

	return iter->second;
}

void InMemorySessionManager::clearOldSessions() {
	time_t seconds;
	seconds = time(NULL);

	std::map<std::string, InMemorySessionManager*>::iterator iter;
	for(iter = mSessionStorage.begin(); iter!=mSessionStorage.end();) {
		if(seconds-iter->second->getLastAccessedTime() > mMaxInactiveInterval) {
			mSessionStorage.erase(iter++);
		}
		else {
			++iter;
		}
	}
}

void InMemorySessionManager::startNewSession() {

}

void InMemorySessionManager::initSession(bool newSession, const std::string& sessionId) {
	time_t seconds;
	seconds = time(NULL);

	mNew = newSession;
	mLastAccessdTime = seconds;

	if(mNew) {
		mId = sessionId;
		mInvalidated = false;
		mCreationTime = seconds;
	}
}
