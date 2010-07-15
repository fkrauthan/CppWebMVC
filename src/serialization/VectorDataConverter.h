/*
 * VectorDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef VECTORDATACONVERTER_H_
#define VECTORDATACONVERTER_H_

#include "TextSerializerDataConverter.h"


template <typename T> class VectorDataConverter : public TextSerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::vector<T>).name() == type;
	}

	virtual std::string convertFrom(void* input) {
		std::vector<T> realInput = *(std::vector<T>*)input;

		std::stringstream result;
		result << realInput.size() << "|";
		for(unsigned int i = 0; i < realInput.size(); i++) {
			if(i != 0) {
				result << "|";
			}
			result << TextSerializer::getInstance().serialize<T>(realInput[i]);
		}
		return result.str();
	}

	virtual void convertTo(std::stringstream& input, void* destination) {
		std::vector<T> result;

		unsigned int count = 0;
		char delimiter;
		input >> count;
		input >> delimiter;

		for(unsigned int i = 0; i < count; i++) {
			if(i != 0) {
				input >> delimiter;
			}
			T value;
			TextSerializer::getInstance().deserialize(input, value);
			result.push_back(value);
		}

		*((std::vector<T>*)destination) = result;
	}

	virtual void* create() {
		return new std::vector<T>();
	}
};

#endif /* VECTORDATACONVERTER_H_ */
