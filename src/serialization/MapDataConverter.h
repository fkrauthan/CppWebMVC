/*
 * MapDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef MAPDATACONVERTER_H_
#define MAPDATACONVERTER_H_

#include "SerializerDataConverter.h"
#include "SerializationXmlAttributeNotSupportException.h"
#include "Serializer.h"
#include <map>


template <typename T, typename U> class MapDataConverter : public SerializerDataConverter {
	virtual std::string getMatchingType() {
		return typeid(std::map<T, U>).name();
	}

	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::map<T, U>).name() == type;
	}

	virtual std::string convertToText(void* input) {
		std::map<T, U> realInput = *(std::map<T, U>*)input;

		std::stringstream result;
		result << realInput.size() << "|";

		for(typename std::map<T, U>::const_iterator iter = realInput.begin(); iter != realInput.end(); ++iter) {
			if(iter != realInput.begin()) {
				result << "|";
			}

			result << Serializer::getInstance().serializeToText<T>(iter->first);
			result << "|";
			result << Serializer::getInstance().serializeToText<U>(iter->second);
		}
		return result.str();
	}

	virtual void convertFromText(std::stringstream& input, void* destination) {
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

			Serializer::getInstance().deserializeFromText(input, first);
			input >> delimiter;
			Serializer::getInstance().deserializeFromText(input, second);

			result[first] = second;
		}

		*((std::map<T, U>*)destination) = result;
	}

	virtual void convertToXML(void* input, bool asAttribute, rapidxml::xml_node<>& root)
	{
		if (asAttribute)
		{
			throw SerializationXmlAttributeNotSupportException("Attribute is not support for map");
		}

		std::map<T, U> realInput = *(std::map<T, U>*)input;

		rapidxml::xml_document<>* doc = root.document();
		rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;

		for(typename std::map<T, U>::const_iterator iter = realInput.begin(); iter != realInput.end(); ++iter)
		{
			rapidxml::xml_node<>* subNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("entry"));
			node->append_node(subNode);

			rapidxml::xml_node<>* subSubNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("key"));
			subNode->append_node(subSubNode);
			Serializer::getInstance().serializeToXML(iter->first, subSubNode);

			subSubNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("value"));
			subNode->append_node(subSubNode);
			Serializer::getInstance().serializeToXML(iter->second, subSubNode);
		}
	}

	virtual void convertFromXML(void* output, bool fromAttribute, rapidxml::xml_node<>& root)
	{
		rapidxml::xml_node<>* node = (rapidxml::xml_node<>*)&root;

		std::map<T, U> result;

		for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
		{
			T first;
			U second;

			rapidxml::xml_node<>* tmpNode = child->first_node("key");
			Serializer::getInstance().deserializeFromXML<T>(tmpNode, first);

			tmpNode = child->first_node("value");
			Serializer::getInstance().deserializeFromXML<U>(tmpNode, second);
			result[first] = second;
		}

		*((std::map<T, U>*)output) = result;
	}

	virtual void* create() {
		return new std::map<T, U>();
	}
};

#endif /* MAPDATACONVERTER_H_ */
