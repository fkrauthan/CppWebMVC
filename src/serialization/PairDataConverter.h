/*
 * PairDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef PAIRDATACONVERTER_H_
#define PAIRDATACONVERTER_H_

#include "SerializerDataConverter.h"
#include "SerializationXmlAttributeNotSupportException.h"
#include "Serializer.h"
#include <utility>


template <typename T, typename U> class PairDataConverter : public SerializerDataConverter {
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::pair<T, U>).name() == type;
	}

	virtual std::string convertFromText(void* input) {
		std::pair<T, U> realInput = *(std::pair<T, U>*)input;
		std::stringstream result;

		result << Serializer::getInstance().serializeToText<T>(realInput.first);
		result << "|";
		result << Serializer::getInstance().serializeToText<U>(realInput.second);

		return result.str();
	}

	virtual void convertToText(std::stringstream& input, void* destination) {
		std::vector<T> result;
		char delimiter;

		T first;
		U second;

		Serializer::getInstance().deserializeFromText(input, first);
		input >> delimiter;
		Serializer::getInstance().deserializeFromText(input, second);

		*((std::pair<T, U>*)destination) = std::make_pair(first, second);
	}

	virtual void convertFromXML(void* input, bool asAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		if (asAttribute)
		{
			throw SerializationXmlAttributeNotSupportException("Attribute is not support for pair");
		}

		std::pair<T, U> realInput = *(std::pair<T, U>*)input;

		rapidxml::xml_document<>* doc = root.document();

		rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, doc->allocate_string(name.c_str()));
		root.append_node(node);

		Serializer::getInstance().serializeToXML<T>(realInput.first, "Key", node);
		Serializer::getInstance().serializeToXML<U>(realInput.second, "Value", node);
	}

	virtual void convertToXML(void* output, bool fromAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		rapidxml::xml_node<>* node = name.empty() ? &root : root.first_node(name.c_str());
		if (node == NULL)
			return;

		T first;
		U second;

		Serializer::getInstance().deserializeFromXML<T>(node, first, "Key");
		Serializer::getInstance().deserializeFromXML<U>(node, second, "Value");

		*((std::pair<T, U>*)output) = std::make_pair(first, second);
	}

	virtual void* create() {
		return new std::pair<T, U>();
	}
};

#endif /* PAIRDATACONVERTER_H_ */
