/*
 * InMemorySessionManager.h
 *
 *  Created on: 20.07.2010
 *      Author: fkrauthan
 */

#ifndef INMEMORYSESSIONMANAGER_H_
#define INMEMORYSESSIONMANAGER_H_

#include "../data/HttpSession.h"
#include <map>
#include <string>


class InMemorySessionManager : public HttpSession {
	public:
		InMemorySessionManager();
		~InMemorySessionManager();


		//Config funktions
		void setSessionIdInCookie(bool sessionIdInCookie);
		bool getSessionIdInCookie();

		void setSessionIdCookieName(const std::string& sessionIdCookieName);
		std::string& getSessionIdCookieName();

		void setSessionCookieLifeTime(int sessionCookieLifeTime);
		int getSessionCookieLifeTime();

		void setSessionIdInGetOrPost(bool sessionIdInGetOrPost);
		bool getSessionIdInGetOrPost();

		void setSessionIdRequestName(const std::string& sessionIdRequestName);
		std::string& getSessionIdRequestName();


		//Session funktions
		void startNewSession();


		HttpSession* createSession(const HttpRequest& request, HttpResponse& response);
		void removeSession(HttpSession* session);

	private:
		InMemorySessionManager(InMemorySessionManager* manager);
		InMemorySessionManager* getSessionWithId(const std::string& sessionId);
		void clearOldSessions();
		void initSession(bool newSession, const std::string& sessionId = std::string(""));

	private:
		std::map<std::string, InMemorySessionManager*> mSessionStorage;
		bool mSessionIdInCookie;
		std::string mSessionIdCookieName;
		int mSessionCookieLifeTime;
		bool mSessionIdInGetOrPost;
		std::string mSessionIdRequestName;

		int nextSessionId;

	private:
		//Intern vars
		InMemorySessionManager* mManager;
};

#endif /* INMEMORYSESSIONMANAGER_H_ */
