/*
 * CallGenerator.cpp
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#include "CallGenerator.h"
#include <boost/algorithm/string/replace.hpp>


CallGenerator::CallGenerator(const std::string& className, const std::string& _namespace, const std::vector<AnalyzerNS::MethodInfo>& methodInfos, std::fstream& out)
	: mClassName(className), mNamespace(_namespace), mMethodInfos(methodInfos), mOut(out) {
	mNamePrefix = mNamespace+mClassName;
	boost::algorithm::replace_all(mNamePrefix, "::", "__");
}

CallGenerator::~CallGenerator() {
}

void CallGenerator::scan() {
	bool hasDefaultCTor = false;

	for(unsigned int i=0; i<mMethodInfos.size(); i++) {
		if(mMethodInfos[i].mIsClassConstructor) {
			hasDefaultCTor = true;
		}

		if(mMethodInfos[i].mQualifier == AnalyzerNS::Qualifier::Public) {
			if(mMethodInfos[i].mIsClassConstructor) {
				genCTorCall(i, mMethodInfos[i]);
			}
			else if(!mMethodInfos[i].mIsAbstract && !mMethodInfos[i].mIsClassDestructor) {
				genMethodCall(i, mMethodInfos[i]);
			}
		}
	}

	if(!hasDefaultCTor) {
		AnalyzerNS::MethodInfo tmpInfo;
		genCTorCall(mMethodInfos.size(), tmpInfo);
	}
}

void CallGenerator::genMethodCall(int pos, const AnalyzerNS::MethodInfo& method) {
	mOut << "boost::any " << mNamePrefix << "CallFunction_" << method.mName << pos << "(void* instance, const std::vector<boost::any>& params) {\n";

	if(method.mType.mTypeName == "void") {
		mOut << "\t((" << mNamespace << mClassName << "*)instance)->" << method.mName << "(";
	}
	else {
		mOut << "\treturn boost::any(((" << mNamespace << mClassName << "*)instance)->" << method.mName << "(";
	}

	for(unsigned int i=0; i<method.mParameters.size(); i++) {
		if(i!=0) {
			mOut << ", ";
		}
		genParamCode(i, method.mParameters[i]);
	}

	if(method.mType.mTypeName == "void") {
		mOut << ");\n";
		mOut << "\treturn boost::any(0);\n}\n\n";
	}
	else {
		mOut << "));\n}\n\n";
	}
}

void CallGenerator::genCTorCall(int pos, const AnalyzerNS::MethodInfo& ctor) {
	mOut << "void* " << mNamePrefix << "ConstructorCreateFunction" << pos << "(const std::vector<boost::any>& params) {\n";
	mOut << "\treturn (void*)new " << mNamespace << mClassName << "(";

	for(unsigned int i=0; i<ctor.mParameters.size(); i++) {
		if(i!=0) {
			mOut << ", ";
		}
		genParamCode(i, ctor.mParameters[i]);
	}
	mOut << ");\n}\n\n";
}

void CallGenerator::genParamCode(int index, const AnalyzerNS::FieldInfo& fieldInfo) {
	if((fieldInfo.mType.mTypeName == "vector" || fieldInfo.mType.mTypeName == "std::vector")
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter.size()==0
			&& !fieldInfo.mType.mTemplateParameter[0].mIsPointer) {
		mOut << "ReflectionConverter::convertVector<" << fieldInfo.mType.mTemplateParameter[0].mTypeName << ">(boost::any_cast<std::vector<boost::any> >(params[" << index << "]))";
	}
	else if((fieldInfo.mType.mTypeName == "vector" || fieldInfo.mType.mTypeName == "std::vector")
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter.size()==0
			&& fieldInfo.mType.mTemplateParameter[0].mIsPointer) {
		mOut << "ReflectionConverter::convertVector<" << fieldInfo.mType.mTemplateParameter[0].mTypeName << "*>(boost::any_cast<std::vector<boost::any> >(params[" << index << "]))";
	}
	else if((fieldInfo.mType.mTypeName == "vector" || fieldInfo.mType.mTypeName == "std::vector")
			&& (fieldInfo.mType.mTemplateParameter[0].mTypeName == "pair" || fieldInfo.mType.mTemplateParameter[0].mTypeName == "std::pair")
			&& !fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[1].mIsPointer
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTemplateParameter.size() == 0
			&& (fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTypeName == "string" || fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTypeName == "std::string")
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[1].mTemplateParameter.size() == 0) {
		mOut << "ReflectionConverter::convertVectorPair<" << fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTypeName << ", " << fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[1].mTypeName << ">(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[" << index << "]))";
	}
	else if((fieldInfo.mType.mTypeName == "vector" || fieldInfo.mType.mTypeName == "std::vector")
			&& (fieldInfo.mType.mTemplateParameter[0].mTypeName == "pair" || fieldInfo.mType.mTemplateParameter[0].mTypeName == "std::pair")
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[1].mIsPointer
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTemplateParameter.size() == 0
			&& (fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTypeName == "string" || fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTypeName == "std::string")
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[1].mTemplateParameter.size() == 0) {
		mOut << "ReflectionConverter::convertVectorPairWithPointer<" << fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[0].mTypeName << ", " << fieldInfo.mType.mTemplateParameter[0].mTemplateParameter[1].mTypeName << "*>(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[" << index << "]))";
	}
	else if((fieldInfo.mType.mTypeName == "map" || fieldInfo.mType.mTypeName == "std::map")
			&& !fieldInfo.mType.mTemplateParameter[1].mIsPointer
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter.size() == 0
			&& (fieldInfo.mType.mTemplateParameter[0].mTypeName == "string" || fieldInfo.mType.mTemplateParameter[0].mTypeName == "std::string")
			&& fieldInfo.mType.mTemplateParameter[1].mTemplateParameter.size() == 0) {
		mOut << "ReflectionConverter::convertMap<" << fieldInfo.mType.mTemplateParameter[0].mTypeName << ", " << fieldInfo.mType.mTemplateParameter[1].mTypeName << ">(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[" << index << "]))";
	}
	else if((fieldInfo.mType.mTypeName == "map" || fieldInfo.mType.mTypeName == "std::map")
			&& fieldInfo.mType.mTemplateParameter[1].mIsPointer
			&& fieldInfo.mType.mTemplateParameter[0].mTemplateParameter.size() == 0
			&& (fieldInfo.mType.mTemplateParameter[0].mTypeName == "string" || fieldInfo.mType.mTemplateParameter[0].mTypeName == "std::string")
			&& fieldInfo.mType.mTemplateParameter[1].mTemplateParameter.size() == 0) {
		mOut << "ReflectionConverter::convertMapWithPointer<" << fieldInfo.mType.mTemplateParameter[0].mTypeName << ", " << fieldInfo.mType.mTemplateParameter[1].mTypeName << "*>(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[" << index << "]))";
	}
	else if(fieldInfo.mType.mIsPointer && fieldInfo.mType.mTemplateParameter.size() == 0) {
		mOut << "ReflectionConverter::convertPointer<" << fieldInfo.mType.mTypeName << "*>(params[" << index << "])";
	}
	else {
		mOut << "boost::any_cast< " << buildReflectionType(fieldInfo.mType) << " >(params[" << index << "])";
	}
}

std::string CallGenerator::buildReflectionType(const AnalyzerNS::TypeInfo& typeInfo) {
	std::string typeString = typeInfo.mTypeName;
	if(typeInfo.mTemplateParameter.size() > 0) {
		typeString.append("< ");
		for(unsigned int i=0; i<typeInfo.mTemplateParameter.size(); i++) {
			if(i>0) {
				typeString.append(", ");
			}
			typeString.append(buildReflectionType(typeInfo.mTemplateParameter[i]));
		}
		typeString.append(" >");
	}
	if(typeInfo.mIsPointer) {
		typeString.append("*");
	}
	return typeString;
}
