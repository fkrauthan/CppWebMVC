/*
 * HttpSession.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef HTTPSESSION_H_
#define HTTPSESSION_H_

#include <string>
#include <vector>
#include "HttpRequest.h"
#include "HttpResponse.h"


class HttpSession {
	public:
		virtual std::string& getId() = 0;

		virtual std::string& getAttribute(const std::string& name) = 0;
		template<typename T> T getAttribute(const std::string& name);
		virtual std::vector<std::string> getAttributeNames() = 0;
		virtual bool hasAttribute(const std::string& name) = 0;

		virtual long getCreationTime() = 0;
		virtual long getLastAccessedTime() = 0;
		virtual int getMaxInactiveInterval() = 0;

		virtual bool isNew() = 0;


		virtual void removeAttribute(const std::string& name) = 0;
		virtual void setAttribute(const std::string& name, const std::string& value) = 0;
		template<typename T> void setAttribute(const std::string& name, T value);

		virtual void invalidate() = 0;
		virtual void startNewSession() = 0;


		virtual HttpSession* createSession(const HttpRequest& request, HttpResponse& response) = 0;
		virtual void removeSession(HttpSession* session) = 0;
};

#endif /* HTTPSESSION_H_ */
