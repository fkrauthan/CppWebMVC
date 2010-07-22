/*
 * Serializer.cpp
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#include "Serializer.h"
#include "NoSerializeConverterFoundException.h"
#include "../reflections/Reflection.h"


Serializer& Serializer::getInstance() {
	static Serializer instance;
	return instance;
}

SerializerDataConverter* Serializer::findConverter(const std::string& type) {
	for(unsigned int i = 0; i < mDataConverters.size(); ++i) {
		if(mDataConverters[i]->isMatchingConverter(type)) {
			return mDataConverters[i];
		}
	}

	return NULL;
}

void Serializer::registerDataConverter(SerializerDataConverter* dataConverter) {
	mDataConverters.push_back(dataConverter);
}

std::string Serializer::serializeToText(const std::string& type, const std::string& typeIdName, void* data) {
	std::string finalType = type;

	bool isPointer = false;
	if(finalType[finalType.size()-1] == '*') {
		isPointer = true;
		finalType.resize(finalType.size() - 1);
		data = (void*)*(void**)data;
		if(data == NULL) {
			return "NULL";
		}
	}


	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(typeIdName);
	if(reflectionClass == NULL) {
		reflectionClass = Reflection::getInstance().getClass(finalType);
	}

	if(reflectionClass == NULL) {
		SerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL) {
			converter = findConverter(typeIdName);
		}

		if(converter == NULL) {
			throw NoSerializeConverterFoundException("Unable to serialize type " + finalType + ".");
		}
		return converter->convertFromText(data);
	}

	std::stringstream result;
	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i) {
		if(i != 0) {
			result << "|";
		}

		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)data) + member->getOffset());

		SerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL) {
			result << serializeToText(member->getType(), member->getTypeIdName(), currentDataSection);
		}
		else {
			result << converter->convertFromText(currentDataSection);
		}
	}

	return result.str();
}

void Serializer::deserializeFromText(std::stringstream& input, const std::string& type, void* output) {
	std::string finalType = type;

	bool isPointer = false;
	if(finalType[finalType.size()-1] == '*') {
		isPointer = true;
		finalType.resize(finalType.size() - 1);
		std::stringstream::pos_type pos = input.tellg();
		char null[4];
		input.read(null, 4);
		input.seekg(pos);
		if(std::string(null, 4) == "NULL") {
			void** a = (void**)output;
			void* b = NULL;
			*a = b;
			return;
		}
	}

	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(finalType);
	if(reflectionClass == NULL) {
		reflectionClass = Reflection::getInstance().getClass(finalType);
	}

	if(reflectionClass == NULL) {
		SerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL) {
			throw NoSerializeConverterFoundException("Unable to deserialize type " + finalType + ".");
		}

		if(isPointer) {
			void** a = (void**)output;
			void* b = converter->create();
			*a = b;
			output = (void*)*(void**)output;
		}

		converter->convertToText(input, output);
		return;
	}

	if(isPointer) {
		void** a = (void**)output;
		void* b = NULL;
		if(reflectionClass->getCTors().size() > 0) {
			const std::vector<ReflectionCTor*>& cTors = reflectionClass->getCTors();
			for(unsigned int i=0; i<cTors.size(); ++i) {
				if(cTors[i]->getParams().size()==0) {
					b = cTors[i]->createInstance();
					break;
				}
			}
		}
		*a = b;
		output = (void*)*(void**)output;
	}

	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i) {
		char delimiter;
		if(i != 0) {
			input.read(&delimiter, 1);
		}

		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)output) + member->getOffset());

		SerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL) {
			deserializeFromText(input, member->getType(), currentDataSection);
		}
		else {
			converter->convertToText(input, currentDataSection);
		}
	}
}

void Serializer::serializeToXML(const std::string& name, const std::string& type, const std::string& typeIdName, void* data, rapidxml::xml_node<>* root)
{
	rapidxml::xml_document<> tmpDoc;
	rapidxml::xml_document<>& doc = root == NULL ? tmpDoc : *root->document();
	if (root == NULL)
	{
		rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
		decl->append_attribute(doc.allocate_attribute("version", "1.0"));
		decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
		doc.append_node(decl);

		root = &doc;
	}

	std::string finalType = type;

	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(typeIdName);
	if(reflectionClass == NULL)
	{
		reflectionClass = Reflection::getInstance().getClass(finalType);
	}

	if(reflectionClass == NULL)
	{
		SerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL)
		{
			converter = findConverter(typeIdName);
		}

		if(converter == NULL)
		{
			throw NoSerializeConverterFoundException("Unable to serialize type " + finalType + ".");
		}
		converter->convertFromXML(data, false, name, *root);
		return;
	}

	rapidxml::xml_node<>* thisNode = doc.allocate_node(rapidxml::node_element, doc.allocate_string(name.c_str()));
	root->append_node(thisNode);

	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i)
	{
		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)data) + member->getOffset());

		SerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL)
		{
			serializeToXML(member->getName(), member->getType(), member->getTypeIdName(), currentDataSection, thisNode);
		}
		else
		{
			converter->convertFromXML(currentDataSection, false, member->getName(), *thisNode);
		}
	}
}

void Serializer::deserializeFromXML(const std::string& name, const std::string& type, rapidxml::xml_node<>* root, void* output)
{
	std::string finalType = type;

	bool isPointer = false;
	if(finalType[finalType.size()-1] == '*')
	{
		isPointer = true;
		finalType.resize(finalType.size() - 1);
	}

	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(finalType);
	if(reflectionClass == NULL)
	{
		reflectionClass = Reflection::getInstance().getClass(finalType);
	}

	if(reflectionClass == NULL)
	{
		SerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL)
		{
			throw NoSerializeConverterFoundException("Unable to deserialize type " + finalType + ".");
		}

		if(isPointer)
		{
			void** a = (void**)output;
			void* b = converter->create();
			*a = b;
			output = (void*)*(void**)output;
		}

		converter->convertToXML(output, false, name.c_str(), *root);
		return;
	}

	if(isPointer)
	{
		void** a = (void**)output;
		void* b = NULL;
		if(reflectionClass->getCTors().size() > 0)
		{
			const std::vector<ReflectionCTor*>& cTors = reflectionClass->getCTors();
			for(unsigned int i=0; i<cTors.size(); ++i)
			{
				if(cTors[i]->getParams().size()==0)
				{
					b = cTors[i]->createInstance();
					break;
				}
			}
		}
		*a = b;
		output = (void*)*(void**)output;
	}

	rapidxml::xml_node<>* thisNode = root->first_node(name.c_str());

	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i)
	{
		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)output) + member->getOffset());

		SerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL)
		{
			deserializeFromXML(member->getName(), member->getTypeIdName(), thisNode, currentDataSection);
		}
		else
		{
			converter->convertToXML(currentDataSection, false, member->getName(), *thisNode);
		}
	}
}
