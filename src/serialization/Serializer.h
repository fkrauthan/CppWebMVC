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
#include <map>
#include <string>


class Serializer {
	public:
		static Serializer& getInstance();

	public:
		template <typename T> SerializerDataConverter* findConverter();
		SerializerDataConverter* findConverter(const std::string& type);

		void registerDataConverter(SerializerDataConverter* dataConverter);


		//Text serializer
		std::string serializeToText(const std::string& type, void* data);
		template <typename T> std::string serializeToText(const T& data);

		template <typename T> T* deserializeFromText(const std::string& input);
		template <typename T> void deserializeFromText(const std::string& input, T& output);
		template <typename T> void deserializeFromText(std::stringstream& input, T& output);
		void deserializeFromText(std::stringstream& input, const std::string& type, void* output);


		//XML serializer
		void serializeToXML(const std::string& type, void* data, rapidxml::xml_node<>* root = NULL);
		template <typename T> void serializeToXML(const T& data, rapidxml::xml_node<>* root);
		template <typename T> std::string serializeToXML(const T& data, const std::string& name = "root");

		template <typename T> T* deserializeFromXML(const std::string& input, const std::string& name = "root");
		template <typename T> void deserializeFromXML(rapidxml::xml_node<>* root, T& output);
		void deserializeFromXML(const std::string& type, rapidxml::xml_node<>* root, void* output);

	private:
		Serializer() {}

		bool isTypeAPointer(std::string& finalType);

	private:
		std::map<std::string, SerializerDataConverter*> mDataConverters;
};


#include "Serializer.inl"

#endif /* SERIALIZER_H_ */
