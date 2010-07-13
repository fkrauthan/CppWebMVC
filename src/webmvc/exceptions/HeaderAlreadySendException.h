/*
 * HeaderAlreadySendException.h
 *
 *  Created on: 24.06.2010
 *      Author: fkrauthan
 */

#ifndef HEADERALREADYSENDEXCEPTION_H_
#define HEADERALREADYSENDEXCEPTION_H_

#include <stdexcept>
#include <string>


class HeaderAlreadySendException : public std::runtime_error {
	public:
		HeaderAlreadySendException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* HEADERALREADYSENDEXCEPTION_H_ */
