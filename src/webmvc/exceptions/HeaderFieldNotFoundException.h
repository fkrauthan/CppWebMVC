/*
 * HeaderFieldNotFoundException.h
 *
 *  Created on: 24.06.2010
 *      Author: fkrauthan
 */

#ifndef HEADERFIELDNOTFOUNDEXCEPTION_H_
#define HEADERFIELDNOTFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class HeaderFieldNotFoundException : public std::runtime_error {
	public:
		HeaderFieldNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* HEADERFIELDNOTFOUNDEXCEPTION_H_ */
