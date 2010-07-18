/*
 * TextSession.cpp
 *
 *  Created on: 14.07.2010
 *      Author: fkrauthan
 */

#include "TextSession.h"

TextSession::TextSession() {
}

TextSession::~TextSession() {

}

void TextSession::startNewSession() {
	//TODO: session starten
}

HttpSession* TextSession::createSession(const HttpRequest& request, HttpResponse& response) {
	return NULL;
}

void TextSession::removeSession(HttpSession* session) {
	delete session;
}
