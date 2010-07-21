/*
 * SessionNotFoundException.h
 *
 *  Created on: 21.07.2010
 *      Author: fkrauthan
 */

#ifndef SESSIONNOTFOUNDEXCEPTION_H_
#define SESSIONNOTFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class SessionNotFoundException : public std::runtime_error {
	public:
		SessionNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* SESSIONNOTFOUNDEXCEPTION_H_ */
