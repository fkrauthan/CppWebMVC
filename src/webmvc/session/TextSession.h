/*
 * TextSession.h
 *
 *  Created on: 14.07.2010
 *      Author: fkrauthan
 */

#ifndef TEXTSESSION_H_
#define TEXTSESSION_H_

#include "../data/HttpSession.h"


class TextSession : public HttpSession {
	public:
		TextSession();
		~TextSession();

		std::string& getId();

		std::string& getAttribute(const std::string& name);
		std::vector<std::string> getAttributeNames();
		bool hasAttribute(const std::string& name);

		long getCreationTime();
		long getLastAccessedTime();
		int getMaxInactiveInterval();

		bool isNew();

		void removeAttribute(const std::string& name);
		void setAttribute(const std::string& name, const std::string& value);

		void invalidate();
		void startNewSession();


		HttpSession* createSession(const HttpRequest& request, HttpResponse& response);
		void removeSession(HttpSession* session);

	private:
		std::string mId;
		long mCreationTime;
		long mLastAccessdTime;
		int mMaxInactiveInterval;

		bool mNew;
		bool mInvalidated;

		std::map<std::string, std::string> mAttributes;
};

#endif /* TEXTSESSION_H_ */
