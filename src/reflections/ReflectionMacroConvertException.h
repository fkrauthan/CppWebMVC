/*
 * ReflectionMacroConvertException.h
 *
 *  Created on: 22.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONMACROCONVERTEXCEPTION_H_
#define REFLECTIONMACROCONVERTEXCEPTION_H_

#include <stdexcept>
#include <string>


class ReflectionMacroConvertException : public std::runtime_error {
	public:
		ReflectionMacroConvertException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* REFLECTIONMACROCONVERTEXCEPTION_H_ */
