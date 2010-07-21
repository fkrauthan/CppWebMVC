/*
 * ISessionIdGenerator.h
 *
 *  Created on: 21.07.2010
 *      Author: fkrauthan
 */

#ifndef ISESSIONIDGENERATOR_H_
#define ISESSIONIDGENERATOR_H_

#include <webmvc/data/HttpRequest.h>
#include <webmvc/data/HttpResponse.h>
#include "SessionManager.h"

class SessionManager;


class ISessionIdGenerator {
	public:
		virtual ~ISessionIdGenerator() {}

		virtual std::string generateSessionId(SessionManager* manager, const HttpRequest& request, HttpResponse& response) = 0;
};

#endif /* ISESSIONIDGENERATOR_H_ */
