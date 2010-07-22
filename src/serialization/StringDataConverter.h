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
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::string).name() == type;
	}

	virtual std::string convertFromText(void* input) {
		std::string realInput = *(std::string*)input;
		std::stringstream result;
		result << realInput.size() << "|";
		result << realInput;
		return result.str();
	}

	virtual void convertToText(std::stringstream& input, void* destination) {
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

	virtual void convertFromXML(void* input, bool asAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		std::string content = *(std::string*)input;

		rapidxml::xml_document<>* doc = root.document();

		if (!asAttribute)
		{
			rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, doc->allocate_string(name.c_str()), doc->allocate_string(content.c_str()));
			root.append_node(node);
		}
		else
			root.append_attribute(doc->allocate_attribute(doc->allocate_string(name.c_str()), doc->allocate_string(content.c_str())));
	}

	virtual void convertToXML(void* output, bool fromAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		std::string result;
		if (!fromAttribute)
		{
			rapidxml::xml_node<>* node = name.empty() ? &root : root.first_node(name.c_str());
			if (node == NULL)
				return;
			result = std::string(node->value(), node->value_size());
		}
		else
		{
			rapidxml::xml_attribute<> * attribute = root.first_attribute(name.c_str());
			if (attribute == NULL)
				return;
			result = std::string(attribute->value(), attribute->value_size());
		}


		*((std::string*)output) = result;
	}

	virtual void* create() {
		return new std::string();
	}
};

#endif /* STRINGDATACONVERTER_H_ */
