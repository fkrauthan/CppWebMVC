/*
 * ReflectionConvertException.h
 *
 *  Created on: 22.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONCONVERTEXCEPTION_H_
#define REFLECTIONCONVERTEXCEPTION_H_

#include <stdexcept>
#include <string>


class ReflectionConvertException : public std::runtime_error {
	public:
		ReflectionConvertException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* REFLECTIONCONVERTEXCEPTION_H_ */
