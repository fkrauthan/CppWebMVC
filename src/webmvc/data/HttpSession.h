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
		HttpSession(const std::string& id, long creationTime, long lastAccessTime, bool isNew, const std::map<std::string, std::string>& attributes = std::map<std::string, std::string>());
		~HttpSession();

		std::string& getId();

		std::string& getAttribute(const std::string& name);
		template<typename T> T getAttribute(const std::string& name);
		std::map<std::string, std::string>& getAttributes();
		std::vector<std::string> getAttributeNames();
		bool hasAttribute(const std::string& name);

		long getCreationTime();
		long getLastAccessedTime();

		bool isNew();


		void removeAttribute(const std::string& name);
		void setAttribute(const std::string& name, const std::string& value);
		template<typename T> void setAttribute(const std::string& name, T value);

		void invalidate();
		bool isInvalid();


		//virtual HttpSession* createSession(const HttpRequest& request, HttpResponse& response) = 0;
		//virtual void removeSession(HttpSession* session) = 0;

	protected:
		std::string mId;
		long mCreationTime;
		long mLastAccessdTime;

		bool mNew;
		bool mInvalidated;

		std::map<std::string, std::string> mAttributes;
};

#endif /* HTTPSESSION_H_ */
