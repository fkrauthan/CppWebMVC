/*
 * GenericDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef GENERICDATACONVERTER_H_
#define GENERICDATACONVERTER_H_

#include "TextSerializerDataConverter.h"
#include <iostream>

template <typename T> class GenericDataConverter : public TextSerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(T).name() == type;
	}

	virtual std::string convertFrom(void* input) {
		T realInput = *(T*)input;
		std::stringstream result;
		result << realInput;
		return result.str();
	}

	virtual void convertTo(std::stringstream& input, void* destination) {
		T result;
		input >> result;
		*((T*)destination) = result;
	}

	virtual void* create() {
		return new T;
	}
};

#endif /* GENERICDATACONVERTER_H_ */
