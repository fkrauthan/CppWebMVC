/*
 * SessionIdCounterGenerator.h
 *
 *  Created on: 21.07.2010
 *      Author: fkrauthan
 */

#ifndef SESSIONIDCOUNTERGENERATOR_H_
#define SESSIONIDCOUNTERGENERATOR_H_

#include "../ISessionIdGenerator.h"


class SessionIdCounterGenerator : public ISessionIdGenerator {
	public:
		SessionIdCounterGenerator();
		~SessionIdCounterGenerator();

		std::string generateSessionId(SessionManager* manager, const HttpRequest& request, HttpResponse& response);

	private:
		long mCurCount;
};

#endif /* SESSIONIDCOUNTERGENERATOR_H_ */
