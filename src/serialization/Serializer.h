/*
 * Serializer.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include "SerializerDataConverter.h"
#include "../xml/rapidxml.hpp"
#include <vector>


class Serializer {
	public:
		static Serializer& getInstance();

	public:
		template <typename T> SerializerDataConverter* findConverter();
		SerializerDataConverter* findConverter(const std::string& type);

		void registerDataConverter(SerializerDataConverter* dataConverter);


		//Text serializer
		std::string serializeToText(const std::string& type, const std::string& typeIdName, void* data);
		template <typename T> std::string serializeToText(const T& data);

		template <typename T> T* deserializeFromText(const std::string& input);
		template <typename T> void deserializeFromText(const std::string& input, T& output);
		template <typename T> void deserializeFromText(std::stringstream& input, T& output);
		void deserializeFromText(std::stringstream& input, const std::string& type, void* output);


		//XML serializer
		void serializeToXML(const std::string& name, const std::string& type, const std::string& typeIdName, void* data, rapidxml::xml_node<>* root = NULL);
		template <typename T> void serializeToXML(const T& data, const std::string& name, rapidxml::xml_node<>* root);
		template <typename T> std::string serializeToXML(const T& data, const std::string& name = "root");

		template <typename T> T* deserializeFromXML(const std::string& input, const std::string& name = "root");
		template <typename T> void deserializeFromXML(rapidxml::xml_node<>* root, T& output, const std::string& name = "root");
		void deserializeFromXML(const std::string& name, const std::string& type, rapidxml::xml_node<>* root, void* output);

	private:
		Serializer() {}

		std::vector<SerializerDataConverter*> mDataConverters;
};


#include "Serializer.inl"

#endif /* SERIALIZER_H_ */
