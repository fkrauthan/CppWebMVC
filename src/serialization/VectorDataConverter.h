/*
 * VectorDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef VECTORDATACONVERTER_H_
#define VECTORDATACONVERTER_H_

#include "SerializerDataConverter.h"
#include "SerializationXmlAttributeNotSupportException.h"
#include "Serializer.h"
#include <vector>


template <typename T> class VectorDataConverter : public SerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::vector<T>).name() == type;
	}

	virtual std::string convertFromText(void* input) {
		std::vector<T> realInput = *(std::vector<T>*)input;

		std::stringstream result;
		result << realInput.size() << "|";
		for(unsigned int i = 0; i < realInput.size(); i++) {
			if(i != 0) {
				result << "|";
			}
			result << Serializer::getInstance().serializeToText<T>(realInput[i]);
		}
		return result.str();
	}

	virtual void convertToText(std::stringstream& input, void* destination) {
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
			Serializer::getInstance().deserializeFromText(input, value);
			result.push_back(value);
		}

		*((std::vector<T>*)destination) = result;
	}

	virtual void convertFromXML(void* input, bool asAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		if (asAttribute)
		{
			throw SerializationXmlAttributeNotSupportException("Attribute is not support for vector");
			// TODO: Not Supported Exception
		}

		std::vector<T> realInput = *(std::vector<T>*)input;

		rapidxml::xml_document<>* doc = root.document();

		rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, doc->allocate_string(name.c_str()));
		root.append_node(node);

		for(unsigned int i = 0; i < realInput.size(); i++)
			Serializer::getInstance().serializeToXML<T>(realInput[i], "entry", node);
	}

	virtual void convertToXML(void* output, bool fromAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		rapidxml::xml_node<>* node = name.empty() ? &root : root.first_node(name.c_str());
		if (node == NULL)
			return;

		std::vector<T> result;
		for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
		{
			T entry;
			Serializer::getInstance().deserializeFromXML<T>(child, entry, "");
			result.push_back(entry);
		}
		*((std::vector<T>*)output) = result;
	}

	virtual void* create() {
		return new std::vector<T>();
	}
};

#endif /* VECTORDATACONVERTER_H_ */
