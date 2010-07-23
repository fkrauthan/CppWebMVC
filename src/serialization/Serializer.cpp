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

std::string Serializer::serializeToText(const std::string& type, void* data) {
	std::string finalType = type;

	bool isPointer = isTypeAPointer(finalType);
	if(isPointer) {
		data = (void*)*(void**)data;
		if(data == NULL) {
			return "NULL";
		}
	}


	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(finalType);
	if(reflectionClass == NULL) {
		SerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL) {
			throw NoSerializeConverterFoundException("Unable to serialize type " + finalType + ".");
		}
		return converter->convertToText(data);
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
			result << serializeToText(member->getTypeIdName(), currentDataSection);
		}
		else {
			result << converter->convertToText(currentDataSection);
		}
	}

	return result.str();
}

void Serializer::deserializeFromText(std::stringstream& input, const std::string& type, void* output) {
	std::string finalType = type;

	bool isPointer = isTypeAPointer(finalType);
	if(isPointer) {
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

		converter->convertFromText(input, output);
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
			deserializeFromText(input, member->getTypeIdName(), currentDataSection);
		}
		else {
			converter->convertFromText(input, currentDataSection);
		}
	}
}

void Serializer::serializeToXML(const std::string& type, void* data, rapidxml::xml_node<>* root)
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
	bool isPointer = isTypeAPointer(finalType);
	if(isPointer) {
		data = (void*)*(void**)data;
		if(data == NULL) {
			root->append_attribute(doc.allocate_attribute(doc.allocate_string("i:isnull"), doc.allocate_string("true")));
			root->append_attribute(doc.allocate_attribute(doc.allocate_string("xmlns:i"), doc.allocate_string("xmlserializer")));
			return;
		}
	}

	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(finalType);
	if(reflectionClass == NULL)
	{
		SerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL)
		{
			throw NoSerializeConverterFoundException("Unable to serialize type " + finalType + ".");
		}
		converter->convertToXML(data, false, *root);
		return;
	}


	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i)
	{
		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)data) + member->getOffset());


		rapidxml::xml_node<>* thisNode = doc.allocate_node(rapidxml::node_element, doc.allocate_string(member->getName().c_str()));
		root->append_node(thisNode);

		SerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL)
		{
			serializeToXML(member->getTypeIdName(), currentDataSection, thisNode);
		}
		else
		{
			converter->convertToXML(currentDataSection, false, *thisNode);
		}
	}
}

void Serializer::deserializeFromXML(const std::string& type, rapidxml::xml_node<>* root, void* output)
{
	std::string finalType = type;
	bool isPointer = isTypeAPointer(finalType);
	if(isPointer) {
		rapidxml::xml_attribute<>* isNull = root->first_attribute("i:isnull");
		if(isNull) {
			if(std::string(isNull->value(), isNull->value_size()) == "true") {
				void** a = (void**)output;
				void* b = NULL;
				*a = b;
				return;
			}
		}
	}


	ReflectionClass* reflectionClass = Reflection::getInstance().getClassByTypeId(finalType);
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

		converter->convertFromXML(output, false, *root);
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

	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i)
	{
		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)output) + member->getOffset());

		rapidxml::xml_node<>* thisNode = root->first_node(member->getName().c_str());
		if(!thisNode) {
			throw SerializationXmlNodeNotFoundException("The node \""+member->getName()+"\" was not found");
		}

		SerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL)
		{
			deserializeFromXML(member->getTypeIdName(), thisNode, currentDataSection);
		}
		else
		{
			converter->convertFromXML(currentDataSection, false, *thisNode);
		}
	}
}

bool Serializer::isTypeAPointer(std::string& finalType) {
#ifdef MSVC
	if(finalType[finalType.size()-1] == '*')  {
		finalType.resize(finalType.size() - 1);
#elif __GNUG__
	if(finalType[0] == 'P')  {
		finalType.erase(finalType.begin());
#else
	if(1==2) {
#endif
		return true;
	}

	return false;
}
