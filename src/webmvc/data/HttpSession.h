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
#include <map>
#include "HttpRequest.h"
#include "HttpResponse.h"


class HttpSession {
	public:
		HttpSession();
		virtual ~HttpSession();

		virtual std::string& getId();

		virtual std::string& getAttribute(const std::string& name);
		template<typename T> T getAttribute(const std::string& name);
		virtual std::vector<std::string> getAttributeNames();
		virtual bool hasAttribute(const std::string& name);

		virtual long getCreationTime();
		virtual long getLastAccessedTime();
		virtual int getMaxInactiveInterval();

		virtual bool isNew();


		virtual void removeAttribute(const std::string& name);
		virtual void setAttribute(const std::string& name, const std::string& value);
		template<typename T> void setAttribute(const std::string& name, T value);

		virtual void invalidate();


		virtual void startNewSession() = 0;


		virtual HttpSession* createSession(const HttpRequest& request, HttpResponse& response) = 0;
		virtual void removeSession(HttpSession* session) = 0;

	protected:
		std::string mId;
		long mCreationTime;
		long mLastAccessdTime;
		int mMaxInactiveInterval;

		bool mNew;
		bool mInvalidated;

		std::map<std::string, std::string> mAttributes;
};

#endif /* HTTPSESSION_H_ */
