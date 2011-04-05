/*
 * SerializerDataConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef SERIALIZERDATACONVERTER_H_
#define SERIALIZERDATACONVERTER_H_

#include <string>
#include <sstream>
#include <rapidxml/rapidxml.hpp>


class SerializerDataConverter {
	public:
		virtual bool isMatchingConverter(const std::string& type) = 0;

		virtual std::string convertToText(void* input) = 0;
		virtual void convertFromText(std::stringstream& input, void* destination) = 0;

		virtual void convertToXML(void* input, bool asAttribute, rapidxml::xml_node<>& root) = 0;
		virtual void convertFromXML(void* output, bool fromAttribute, rapidxml::xml_node<>& root) = 0;

		virtual void* create() = 0;
};

#endif /* SERIALIZERDATACONVERTER_H_ */
