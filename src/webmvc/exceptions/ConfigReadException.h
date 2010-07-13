/*
 * ConfigReadException.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef CONFIGREADEXCEPTION_H_
#define CONFIGREADEXCEPTION_H_

#include <stdexcept>
#include <string>


class ConfigReadException : public std::runtime_error {
	public:
		ConfigReadException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* CONFIGREADEXCEPTION_H_ */
