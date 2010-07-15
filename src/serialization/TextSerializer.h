/*
 * TextSerializer.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef TEXTSERIALIZER_H_
#define TEXTSERIALIZER_H_

#include "TextSerializerDataConverter.h"
#include <vector>


class TextSerializer {
	public:
		static TextSerializer& getInstance();

	public:
		template <typename T> TextSerializerDataConverter* findConverter();
		TextSerializerDataConverter* findConverter(const std::string& type);

		void registerDataConverter(TextSerializerDataConverter* dataConverter);

		//template <typename T> bool canSerialize(const T& data);

		std::string serialize(const std::string& type, const std::string& typeIdName, void* data);
		template <typename T> std::string serialize(const T& data);

		template <typename T> T* deserialize(const std::string& input);
		template <typename T> void deserialize(const std::string& input, T& output);
		template <typename T> void deserialize(std::stringstream& input, T& output);
		void deserialize(std::stringstream& input, const std::string& type, void* output);

	private:
		TextSerializer() {}

		std::vector<TextSerializerDataConverter*> mDataConverters;
};


#include "TextSerializer.inl"

#endif /* TEXTSERIALIZER_H_ */
