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

	virtual std::string convertToText(void* input) {
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

	virtual void convertFromText(std::stringstream& input, void* destination) {
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

	virtual void convertToXML(void* input, bool asAttribute, rapidxml::xml_node<>& root)
	{
		if (asAttribute)
		{
			throw SerializationXmlAttributeNotSupportException("Attribute is not support for vector");
		}

		std::vector<T> realInput = *(std::vector<T>*)input;

		rapidxml::xml_document<>* doc = root.document();
		rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;

		for(unsigned int i = 0; i < realInput.size(); i++)
		{
			rapidxml::xml_node<>* subNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("entry"));
			node->append_node(subNode);
			Serializer::getInstance().serializeToXML<T>(realInput[i], subNode);
		}
	}

	virtual void convertFromXML(void* output, bool fromAttribute, rapidxml::xml_node<>& root)
	{
		rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;

		std::vector<T> result;
		for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
		{
			T entry;
			Serializer::getInstance().deserializeFromXML<T>(child, entry);
			result.push_back(entry);
		}
		*((std::vector<T>*)output) = result;
	}

	virtual void* create() {
		return new std::vector<T>();
	}
};

#endif /* VECTORDATACONVERTER_H_ */
