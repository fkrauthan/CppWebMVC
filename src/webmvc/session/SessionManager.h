/*
 * SessionManager.h
 *
 *  Created on: 21.07.2010
 *      Author: fkrauthan
 */

#ifndef SESSIONMANAGER_H_
#define SESSIONMANAGER_H_

#include "ISessionIdGenerator.h"
#include <beans/IObject.h>
#include <webmvc/data/HttpRequest.h>
#include <webmvc/data/HttpResponse.h>
#include <webmvc/data/HttpSession.h>
#include <string>

class ISessionIdGenerator;


class SessionManager : public IObject {
	public:
		SessionManager();
		virtual ~SessionManager();


		void setUseCookies(bool useCookies);
		bool useCookies();

		void setUserRequest(bool useRequest);
		bool useRequest();

		void setCookieName(const std::string& cookieName);
		std::string& getCookieName();

		void setRequestName(const std::string& requestName);
		std::string& getRequestName();

		void setCookieLifeTime(int cookieLifeTime);
		int getCookieLifeTime();

		void setSessionLifeTime(long sessionLifeTime);
		long getSessionLifeTime();

		void setSessionIdGenerator(ISessionIdGenerator* sessionIdGenerator);
		ISessionIdGenerator* getSessionIdGenerator();


		HttpSession* startSession(const HttpRequest& request, HttpResponse& response);
		virtual void endSession(HttpSession* session, const HttpRequest& request, HttpResponse& response) = 0;
		virtual bool existSessionId(const std::string& id) = 0;

	protected:
		virtual HttpSession* startSessionInternal(const std::string& sessionId, bool sessionIdFoun, const HttpRequest& request, HttpResponse& responsed) = 0;
		virtual void cleanUpOldSessions() = 0;

		std::string generateSessionId(const HttpRequest& request, HttpResponse& response);

	protected:
		bool mUseCookies;
		bool mUseRequest;
		std::string mCookieName;
		std::string mRequestName;

		int mCookieLifeTime;
		long mSessionLifeTime;

		ISessionIdGenerator* mSessionIdGenerator;

};

#endif /* SESSIONMANAGER_H_ */
