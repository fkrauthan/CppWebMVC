/*
 * GenericDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef GENERICDATACONVERTER_H_
#define GENERICDATACONVERTER_H_

#include "SerializerDataConverter.h"
#include <iostream>

template <typename T> class GenericDataConverter : public SerializerDataConverter {
	virtual std::string getMatchingType() {
		return typeid(T).name();
	}

	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(T).name() == type;
	}

	virtual std::string convertToText(void* input) {
		T realInput = *(T*)input;
		std::stringstream result;
		result << realInput;
		return result.str();
	}

	virtual void convertFromText(std::stringstream& input, void* destination) {
		T result;
		input >> result;
		*((T*)destination) = result;
	}

	virtual void convertToXML(void* input, bool asAttribute, rapidxml::xml_node<>& root)
	{
		T realInput = *(T*)input;
		std::stringstream result;
		result << realInput;
		std::string content = result.str();

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
		std::stringstream stream;
		if (!fromAttribute)
		{
			rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;
			stream << std::string(node->value(), node->value_size());
		}
		else
		{
			rapidxml::xml_attribute<>* attribute = (rapidxml::xml_attribute<>*)&root;
			stream << std::string(attribute->value(), attribute->value_size());
		}

		T result;
		stream >> result;
		*((T*)output) = result;
	}

	virtual void* create() {
		return new T;
	}
};

#endif /* GENERICDATACONVERTER_H_ */
