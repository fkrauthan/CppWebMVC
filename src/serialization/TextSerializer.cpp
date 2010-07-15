/*
 * TextSerializer.cpp
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#include "TextSerializer.h"
#include "NoSerializeConverterFoundException.h"
#include <reflections/Reflection.h>


TextSerializer& TextSerializer::getInstance() {
	static TextSerializer instance;
	return instance;
}

TextSerializerDataConverter* TextSerializer::findConverter(const std::string& type) {
	for(unsigned int i = 0; i < mDataConverters.size(); ++i) {
		if(mDataConverters[i]->isMatchingConverter(type)) {
			return mDataConverters[i];
		}
	}

	return NULL;
}

void TextSerializer::registerDataConverter(TextSerializerDataConverter* dataConverter) {
	mDataConverters.push_back(dataConverter);
}

std::string TextSerializer::serialize(const std::string& type, const std::string& typeIdName, void* data) {
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
		TextSerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL) {
			converter = findConverter(typeIdName);
		}

		if(converter == NULL) {
			throw NoSerializeConverterFoundException("Unable to serialize type " + finalType + ".");
		}
		return converter->convertFrom(data);
	}

	std::stringstream result;
	const std::vector<ReflectionMember*>& memberVars = reflectionClass->getMemberVars();
	for(unsigned int i = 0; i < memberVars.size(); ++i) {
		if(i != 0) {
			result << "|";
		}

		ReflectionMember* member = memberVars[i];
		void* currentDataSection = (void*)(((char*)data) + member->getOffset());

		TextSerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL) {
			result << serialize(member->getType(), member->getTypeIdName(), currentDataSection);
		}
		else {
			result << converter->convertFrom(currentDataSection);
		}
	}

	return result.str();
}

void TextSerializer::deserialize(std::stringstream& input, const std::string& type, void* output) {
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
		TextSerializerDataConverter* converter = findConverter(finalType);
		if(converter == NULL) {
			throw NoSerializeConverterFoundException("Unable to deserialize type " + finalType + ".");
		}

		if(isPointer) {
			void** a = (void**)output;
			void* b = converter->create();
			*a = b;
			output = (void*)*(void**)output;
		}

		converter->convertTo(input, output);
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

		TextSerializerDataConverter* converter = findConverter(member->getTypeIdName());
		if(converter == NULL) {
			deserialize(input, member->getType(), currentDataSection);
		}
		else {
			converter->convertTo(input, currentDataSection);
		}
	}
}
