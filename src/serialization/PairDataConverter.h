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
	virtual std::string getMatchingType() {
		return typeid(std::pair<T, U>).name();
	}

	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::pair<T, U>).name() == type;
	}

	virtual std::string convertToText(void* input) {
		std::pair<T, U> realInput = *(std::pair<T, U>*)input;
		std::stringstream result;

		result << Serializer::getInstance().serializeToText<T>(realInput.first);
		result << "|";
		result << Serializer::getInstance().serializeToText<U>(realInput.second);

		return result.str();
	}

	virtual void convertFromText(std::stringstream& input, void* destination) {
		std::vector<T> result;
		char delimiter;

		T first;
		U second;

		Serializer::getInstance().deserializeFromText(input, first);
		input >> delimiter;
		Serializer::getInstance().deserializeFromText(input, second);

		*((std::pair<T, U>*)destination) = std::make_pair(first, second);
	}

	virtual void convertToXML(void* input, bool asAttribute, rapidxml::xml_node<>& root)
	{
		if (asAttribute)
		{
			throw SerializationXmlAttributeNotSupportException("Attribute is not support for pair");
		}

		std::pair<T, U> realInput = *(std::pair<T, U>*)input;

		rapidxml::xml_document<>* doc = root.document();
		rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;

		rapidxml::xml_node<>* subNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("key"));
		node->append_node(subNode);
		Serializer::getInstance().serializeToXML<T>(realInput.first, subNode);

		subNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("value"));
		node->append_node(subNode);
		Serializer::getInstance().serializeToXML<U>(realInput.second, subNode);
	}

	virtual void convertFromXML(void* output, bool fromAttribute, rapidxml::xml_node<>& root)
	{
		rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;

		T first;
		U second;

		rapidxml::xml_node<>* tmpNode = node->first_node("key");
		Serializer::getInstance().deserializeFromXML<T>(tmpNode, first);

		tmpNode = node->first_node("value");
		Serializer::getInstance().deserializeFromXML<U>(tmpNode, second);

		*((std::pair<T, U>*)output) = std::make_pair(first, second);
	}

	virtual void* create() {
		return new std::pair<T, U>();
	}
};

#endif /* PAIRDATACONVERTER_H_ */
