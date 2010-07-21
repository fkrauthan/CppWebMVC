/*
 * InMemorySessionManager.cpp
 *
 *  Created on: 20.07.2010
 *      Author: fkrauthan
 */

#include "InMemorySessionManager.h"


InMemorySessionManager::InMemorySessionManager() {
}

InMemorySessionManager::~InMemorySessionManager() {
	std::map<std::string, HttpSession*>::iterator iter;
	for(iter = mSessionStorage.begin(); iter!=mSessionStorage.end(); ++iter) {
		delete iter->second;
	}
}

void InMemorySessionManager::endSession(HttpSession* session, const HttpRequest& request, HttpResponse& response) {
	if(session->isInvalid()) {
		std::map<std::string, HttpSession*>::iterator iter = mSessionStorage.find(session->getId());
		if(iter!=mSessionStorage.end()) {
			delete iter->second;
			mSessionStorage.erase(iter);
		}
	}
}

bool InMemorySessionManager::existSessionId(const std::string& id) {
	return getSessionWithId(id) != NULL;
}

HttpSession* InMemorySessionManager::startSessionInternal(const std::string& sessionId, bool sessionIdFound, const HttpRequest& request, HttpResponse& response) {
	std::string sessionIdTmp = sessionId;

	time_t seconds;
	seconds = time(NULL);

	if(sessionIdFound) {
		HttpSession* session = getSessionWithId(sessionIdTmp);
		if(session) {
			HttpSession* tmpSession = new HttpSession(session->getId(), session->getCreationTime(), seconds, false, session->getAttributes());
			delete mSessionStorage[sessionIdTmp];
			mSessionStorage[sessionIdTmp] = tmpSession;
			return tmpSession;
		}
		else {
			sessionIdTmp = generateSessionId(request, response);
		}
	}

	HttpSession* session = new HttpSession(sessionIdTmp, seconds, seconds, true);
	mSessionStorage[sessionIdTmp] = session;

	return session;
}

void InMemorySessionManager::cleanUpOldSessions() {
	time_t seconds;
	seconds = time(NULL);

	std::map<std::string, HttpSession*>::iterator iter;
	for(iter = mSessionStorage.begin(); iter!=mSessionStorage.end();) {
		if(seconds-iter->second->getLastAccessedTime() > mSessionLifeTime) {
			delete iter->second;
			mSessionStorage.erase(iter++);
		}
		else {
			++iter;
		}
	}
}

HttpSession* InMemorySessionManager::getSessionWithId(const std::string& sessionId) {
	std::map<std::string, HttpSession*>::iterator iter = mSessionStorage.find(sessionId);
	if(iter==mSessionStorage.end()) {
		return NULL;
	}

	return iter->second;
}
