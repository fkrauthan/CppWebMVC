/*
 * SerializationXmlNodeNotFoundException.h
 *
 *  Created on: 23.07.2010
 *      Author: fkrauthan
 */

#ifndef SERIALIZATIONXMLNODENOTFOUNDEXCEPTION_H_
#define SERIALIZATIONXMLNODENOTFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class SerializationXmlNodeNotFoundException : public std::runtime_error {
	public:
		SerializationXmlNodeNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* SERIALIZATIONXMLNODENOTFOUNDEXCEPTION_H_ */
