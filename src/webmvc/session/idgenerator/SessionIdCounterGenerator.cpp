/*
 * SessionIdCounterGenerator.cpp
 *
 *  Created on: 21.07.2010
 *      Author: fkrauthan
 */

#include "SessionIdCounterGenerator.h"
#include <sstream>


SessionIdCounterGenerator::SessionIdCounterGenerator() {
	mCurCount = 0;
}

SessionIdCounterGenerator::~SessionIdCounterGenerator() {
}

std::string SessionIdCounterGenerator::generateSessionId(SessionManager* manager, const HttpRequest& request, HttpResponse& response) {
	std::stringstream str;

	do {
		mCurCount++;

		str.str("");
		str << "SESSION_" << mCurCount;
	} while(manager->existSessionId(str.str()));


	return str.str();
}
