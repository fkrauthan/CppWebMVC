/*
 * PrimativeDatatypeConverter.h
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#ifndef PRIMATIVEDATATYPECONVERTER_H_
#define PRIMATIVEDATATYPECONVERTER_H_

#include <string>


class PrimativeDatatypeConverter {
	public:
		template<typename T> static T fromString(const std::string& str);
		template<typename T> static std::string toString(const T& value);
};


#include "PrimativeDatatypeConverter.inl"

#endif /* PRIMATIVEDATATYPECONVERTER_H_ */
