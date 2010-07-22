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
	virtual bool isMatchingConverter(const std::string& type) {
		return typeid(std::map<T, U>).name() == type;
	}

	virtual std::string convertFromText(void* input) {
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

	virtual void convertToText(std::stringstream& input, void* destination) {
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

	virtual void convertFromXML(void* input, bool asAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		if (asAttribute)
		{
			throw SerializationXmlAttributeNotSupportException("Attribute is not support for map");
		}

		std::map<T, U> realInput = *(std::map<T, U>*)input;

		rapidxml::xml_document<>* doc = root.document();

		rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, doc->allocate_string(name.c_str()));
		root.append_node(node);

		for(typename std::map<T, U>::const_iterator iter = realInput.begin(); iter != realInput.end(); ++iter)
		{
			rapidxml::xml_node<>* subNode = doc->allocate_node(rapidxml::node_element, doc->allocate_string("entry"));
			node->append_node(subNode);

			Serializer::getInstance().serializeToXML(iter->first, "Key", subNode);
			Serializer::getInstance().serializeToXML(iter->second, "Value", subNode);
		}
	}

	virtual void convertToXML(void* output, bool fromAttribute, const std::string& name, rapidxml::xml_node<>& root)
	{
		rapidxml::xml_node<>* node = name.empty() ? &root : root.first_node(name.c_str());
		if (node == NULL)
			return;

		std::map<T, U> result;

		for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
		{
			T first;
			U second;

			Serializer::getInstance().deserializeFromXML<T>(child, first, "Key");
			Serializer::getInstance().deserializeFromXML<U>(child, second, "Value");
			result[first] = second;
		}

		*((std::map<T, U>*)output) = result;
	}

	virtual void* create() {
		return new std::map<T, U>();
	}
};

#endif /* MAPDATACONVERTER_H_ */
