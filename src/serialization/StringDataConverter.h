/*
 * StringDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef STRINGDATACONVERTER_H_
#define STRINGDATACONVERTER_H_

#include "SerializerDataConverter.h"


class StringDataConverter : public SerializerDataConverter {
	virtual std::string getMatchingType() {
		return typeid(std::string).name();
	}

	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::string).name() == type;
	}

	virtual std::string convertToText(void* input) {
		std::string realInput = *(std::string*)input;
		std::stringstream result;
		result << realInput.size() << "|";
		result << realInput;
		return result.str();
	}

	virtual void convertFromText(std::stringstream& input, void* destination) {
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

	virtual void convertToXML(void* input, bool asAttribute, rapidxml::xml_node<>& root)
	{
		std::string content = *(std::string*)input;

		rapidxml::xml_document<>* doc = root.document();

		if (!asAttribute)
		{
			rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;
			node->value(doc->allocate_string(content.c_str()));
		}
		else
		{
			rapidxml::xml_attribute<>* attribute = (rapidxml::xml_attribute<>*)&root;
			attribute->value(doc->allocate_string(content.c_str()));
		}
	}

	virtual void convertFromXML(void* output, bool fromAttribute, rapidxml::xml_node<>& root)
	{
		std::string result;
		if (!fromAttribute)
		{
			rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;
			result = std::string(node->value(), node->value_size());
		}
		else
		{
			rapidxml::xml_attribute<>* attribute = (rapidxml::xml_attribute<>*)&root;
			result = std::string(attribute->value(), attribute->value_size());
		}


		*((std::string*)output) = result;
	}

	virtual void* create() {
		return new std::string();
	}
};

#endif /* STRINGDATACONVERTER_H_ */
