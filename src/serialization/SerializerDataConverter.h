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
#include "../xml/rapidxml.hpp"


class SerializerDataConverter {
	public:
		virtual bool isMatchingConverter(const std::string& type) = 0;

		virtual std::string convertFromText(void* input) = 0;
		virtual void convertToText(std::stringstream& input, void* destination) = 0;

		virtual void convertFromXML(void* input, bool asAttribute, const std::string& name, rapidxml::xml_node<>& root) = 0;
		virtual void convertToXML(void* output, bool fromAttribute, const std::string& name, rapidxml::xml_node<>& root) = 0;

		virtual void* create() = 0;
};

#endif /* SERIALIZERDATACONVERTER_H_ */
