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

		void startNewSession();


		HttpSession* createSession(const HttpRequest& request, HttpResponse& response);
		void removeSession(HttpSession* session);
};

#endif /* TEXTSESSION_H_ */
