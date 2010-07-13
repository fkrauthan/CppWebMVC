/*
 * AttributeNotFoundException.h
 *
 *  Created on: 24.06.2010
 *      Author: fkrauthan
 */

#ifndef ATTRIBUTENOTFOUNDEXCEPTION_H_
#define ATTRIBUTENOTFOUNDEXCEPTION_H_

#include <stdexcept>
#include <string>


class AttributeNotFoundException : public std::runtime_error {
	public:
		AttributeNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* ATTRIBUTENOTFOUNDEXCEPTION_H_ */
