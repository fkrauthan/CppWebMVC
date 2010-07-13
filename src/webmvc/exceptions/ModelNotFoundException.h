/*
 * ModelNotFoundException.h
 *
 *  Created on: 02.07.2010
 *      Author: fkrauthan
 */

#ifndef MODELNOTFOUNDEXCEPTION_H_
#define MODELNOTFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class ModelNotFoundException : public std::runtime_error {
	public:
		ModelNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* MODELNOTFOUNDEXCEPTION_H_ */
