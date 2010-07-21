/*
 * InMemorySessionManager.h
 *
 *  Created on: 20.07.2010
 *      Author: fkrauthan
 */

#ifndef INMEMORYSESSIONMANAGER_H_
#define INMEMORYSESSIONMANAGER_H_

#include "../SessionManager.h"
#include <map>
#include <string>


class InMemorySessionManager : public SessionManager {
	public:
		InMemorySessionManager();
		~InMemorySessionManager();

		void endSession(HttpSession* session, const HttpRequest& request, HttpResponse& response);
		bool existSessionId(const std::string& id);

	protected:
		HttpSession* startSessionInternal(const std::string& sessionId, bool sessionIdFound);
		void cleanUpOldSessions();

	private:
		HttpSession* getSessionWithId(const std::string& sessionId);
		void clearOldSessions();
		void initSession(bool newSession, const std::string& sessionId = std::string(""));

	private:
		std::map<std::string, HttpSession*> mSessionStorage;
};

#endif /* INMEMORYSESSIONMANAGER_H_ */
