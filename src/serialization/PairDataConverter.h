/*
 * PairDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef PAIRDATACONVERTER_H_
#define PAIRDATACONVERTER_H_

#include "TextSerializerDataConverter.h"


template <typename T, typename U> class PairDataConverter : public TextSerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::pair<T, U>).name() == type;
	}

	virtual std::string convertFrom(void* input) {
		std::pair<T, U> realInput = *(std::pair<T, U>*)input;
		std::stringstream result;

		result << TextSerializer::getInstance().serialize<T>(realInput.first);
		result << "|";
		result << TextSerializer::getInstance().serialize<U>(realInput.second);

		return result.str();
	}

	virtual void convertTo(std::stringstream& input, void* destination) {
		std::vector<T> result;
		char delimiter;

		T first;
		U second;

		TextSerializer::getInstance().deserialize(input, first);
		input >> delimiter;
		TextSerializer::getInstance().deserialize(input, second);

		*((std::pair<T, U>*)destination) = std::make_pair(first, second);
	}

	virtual void* create() {
		return new std::pair<T, U>();
	}
};

#endif /* PAIRDATACONVERTER_H_ */
