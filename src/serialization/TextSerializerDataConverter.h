/*
 * TextSerializerDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef TEXTSERIALIZERDATACONVERTER_H_
#define TEXTSERIALIZERDATACONVERTER_H_

#include <string>
#include <sstream>


class TextSerializerDataConverter {
	public:
		virtual bool isMatchingConverter(const std::string& type) = 0;
		virtual std::string convertFrom(void* input) = 0;
		virtual void convertTo(std::stringstream& input, void* destination) = 0;
		virtual void* create() = 0;
};

#endif /* TEXTSERIALIZERDATACONVERTER_H_ */
