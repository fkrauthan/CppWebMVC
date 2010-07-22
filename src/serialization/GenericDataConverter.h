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
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(T).name() == type;
	}

	virtual std::string convertFromText(void* input) {
		T realInput = *(T*)input;
		std::stringstream result;
		result << realInput;
		return result.str();
	}

	virtual void convertToText(std::stringstream& input, void* destination) {
		T result;
		input >> result;
		*((T*)destination) = result;
	}

	virtual void convertFromXML(void* input, bool asAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		T realInput = *(T*)input;
		std::stringstream result;
		result << realInput;
		std::string content = result.str();

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
		std::stringstream stream;
		if (!fromAttribute)
		{
			rapidxml::xml_node<>* node = name.empty() ? &root : root.first_node(name.c_str());
			if (node == NULL)
				return;
			stream << std::string(node->value(), node->value_size());
		}
		else
		{
			rapidxml::xml_attribute<> * attribute = root.first_attribute(name.c_str());
			if (attribute == NULL)
				return;
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
