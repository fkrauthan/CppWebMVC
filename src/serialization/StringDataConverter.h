/*
 * StringDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef STRINGDATACONVERTER_H_
#define STRINGDATACONVERTER_H_

#include "TextSerializerDataConverter.h"


class StringDataConverter : public TextSerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::string).name() == type;
	}

	virtual std::string convertFrom(void* input) {
		std::string realInput = *(std::string*)input;
		std::stringstream result;
		result << realInput.size() << "|";
		result << realInput;
		return result.str();
	}

	virtual void convertTo(std::stringstream& input, void* destination) {
		int length = 0;
		char delimiter;
		input >> length;
		input >> delimiter;

		char* buffer = new char [length];
		input.read(buffer, length);
		std::string result(buffer, length);
		delete [] buffer;

		*((std::string*)destination) = result;
	}

	virtual void* create() {
		return new std::string();
	}
};

#endif /* STRINGDATACONVERTER_H_ */
