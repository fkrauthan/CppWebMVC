/*
 * SerializationXmlAttributeNotSupportException.h
 *
 *  Created on: 22.07.2010
 *      Author: fkrauthan
 */

#ifndef SERIALIZATIONXMLATTRIBUTENOTSUPPORTEXCEPTION_H_
#define SERIALIZATIONXMLATTRIBUTENOTSUPPORTEXCEPTION_H_

#include <stdexcept>
#include <string>


class SerializationXmlAttributeNotSupportException : public std::runtime_error {
	public:
		SerializationXmlAttributeNotSupportException(const std::string& msg) : std::runtime_error(msg) {}
};


#endif /* SERIALIZATIONXMLATTRIBUTENOTSUPPORTEXCEPTION_H_ */
