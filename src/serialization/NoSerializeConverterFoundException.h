/*
 * NoSerializeConverterFoundException.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef NOSERIALIZECONVERTERFOUNDEXCEPTION_H_
#define NOSERIALIZECONVERTERFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class NoSerializeConverterFoundException : public std::runtime_error {
	public:
		NoSerializeConverterFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* NOSERIALIZECONVERTERFOUNDEXCEPTION_H_ */
