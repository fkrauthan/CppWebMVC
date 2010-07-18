/*
 * MapDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef MAPDATACONVERTER_H_
#define MAPDATACONVERTER_H_

#include "TextSerializerDataConverter.h"
#include <map>


template <typename T, typename U> class MapDataConverter : public TextSerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::map<T, U>).name() == type;
	}

	virtual std::string convertFrom(void* input) {
		std::map<T, U> realInput = *(std::map<T, U>*)input;

		std::stringstream result;
		result << realInput.size() << "|";

		for(typename std::map<T, U>::const_iterator iter = realInput.begin(); iter != realInput.end(); ++iter) {
			if(iter != realInput.begin()) {
				result << "|";
			}

			result << TextSerializer::getInstance().serialize<T>(iter->first);
			result << "|";
			result << TextSerializer::getInstance().serialize<U>(iter->second);
		}
		return result.str();
	}

	virtual void convertTo(std::stringstream& input, void* destination) {
		std::map<T, U> result;

		unsigned int count = 0;
		char delimiter;
		input >> count;
		input >> delimiter;

		for(unsigned int i = 0; i < count; i++) {
			if(i != 0) {
				input >> delimiter;
			}
			T first;
			U second;

			TextSerializer::getInstance().deserialize(input, first);
			input >> delimiter;
			TextSerializer::getInstance().deserialize(input, second);

			result[first] = second;
		}

		*((std::map<T, U>*)destination) = result;
	}

	virtual void* create() {
		return new std::map<T, U>();
	}
};

#endif /* MAPDATACONVERTER_H_ */
