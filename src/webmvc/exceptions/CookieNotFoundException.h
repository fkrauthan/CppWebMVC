/*
 * CookieNotFoundException.h
 *
 *  Created on: 24.06.2010
 *      Author: fkrauthan
 */

#ifndef COOKIENOTFOUNDEXCEPTION_H_
#define COOKIENOTFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class CookieNotFoundException : public std::runtime_error {
	public:
		CookieNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* COOKIENOTFOUNDEXCEPTION_H_ */
