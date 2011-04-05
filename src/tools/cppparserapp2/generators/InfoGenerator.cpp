/*
 * InfoGenerator.cpp
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#include "InfoGenerator.h"
#include <boost/algorithm/string/replace.hpp>


InfoGenerator::InfoGenerator(const std::string& className, const std::string& _namespace, bool generateSerialization, const AnalyzerNS::ObjectData& object, std::fstream& out)
	: mClassName(className), mNamespace(_namespace), mGenerateSerialization(generateSerialization), mObject(object), mOut(out) {
	mNamePrefix = mNamespace+mClassName;
	boost::algorithm::replace_all(mNamePrefix, "::", "__");
}

InfoGenerator::~InfoGenerator() {
}

void InfoGenerator::scan() {
	//Generate header
	generateHeader();


	//Create function infos
	bool hasDefaultCTor = false;
	for(unsigned int i=0; i<mObject.mMethods.size(); i++) {
		if(mObject.mMethods[i].mIsClassConstructor) {
			hasDefaultCTor = true;
		}

		if(mObject.mMethods[i].mQualifier == AnalyzerNS::Qualifier::Public) {
			if(mObject.mMethods[i].mIsClassConstructor) {
				genCTorInfo(i, mObject.mMethods[i]);
			}
			else if(!mObject.mMethods[i].mIsAbstract && !mObject.mMethods[i].mIsClassDestructor) {
				genMethodInfo(i, mObject.mMethods[i]);
			}
		}
	}

	if(!hasDefaultCTor) {
		AnalyzerNS::MethodInfo tmpInfo;
		genCTorInfo(mObject.mMethods.size(), tmpInfo);
	}


	//Create member infos
	for(unsigned int i=0; i<mObject.mFields.size(); i++) {
		if(mObject.mFields[i].mQualifier == AnalyzerNS::Qualifier::Public
				&& !mObject.mFields[i].mType.mIsConst
				&& !mObject.mFields[i].mType.mIsReference
				&& !mObject.mFields[i].mType.mIsStatic) {

			genMemberInfo(mObject.mFields[i]);
		}
	}
	if(mObject.mFields.size()>0) mOut << "\n";


	//Generate Footer
	generateFooter();
}

void InfoGenerator::generateHeader() {
	mOut << "struct " << mNamePrefix << "_ReflectionStruct {\n";
	mOut << "\t" << mNamePrefix << "_ReflectionStruct() {\n";
	mOut  << "\t\tstd::vector<std::string> superClasses;\n";
	mOut  << "\t\tstd::vector<ReflectionMember*> membersHolder;\n";
	mOut  << "\t\tstd::vector<ReflectionCTor*> ctorsHolder;\n";
	mOut  << "\t\tstd::vector<ReflectionParam*> paramsHolder;\n";
	mOut  << "\t\tstd::vector<ReflectionFunction*> functionsHolder;\n\n";
	mOut  << "\t\tstd::map<std::string, std::string> paramsMap;\n";
	mOut  << "\t\tstd::map<std::string, ReflectionAnotation*> anotationsHolder;\n\n";


	for(unsigned int i=0; i<mObject.mBaseClasses.size(); i++) {
		mOut << "\t\tsuperClasses.push_back(\"" << buildReflectionType(mObject.mBaseClasses[i].mType) << "\");\n";
	}
	if(mObject.mBaseClasses.size() > 0) mOut << "\n";
}

void InfoGenerator::generateFooter() {
	genAnotationsInfo(mObject.mAnnotations);

	mOut << "\t\tReflectionClass* tmpClass = new ReflectionClass(\"" << mNamespace << mObject.mName << "\", typeid(" << mNamespace << mObject.mName << ").name(), typeid(" << mNamespace << mObject.mName << "*).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ";
	if(mObject.mObjectType == AnalyzerNS::ObjectType::Class) {
		mOut << "ReflectionClass::CLASS";
	}
	else {
		mOut << "ReflectionClass::STRUCT";
	}
	mOut << ", anotationsHolder);\n";
	mOut << "\t\tReflection::getInstance().registerClass(tmpClass);\n";
	mOut << "\t}\n};\n";
	mOut << mNamePrefix << "_ReflectionStruct refStruct" << mNamePrefix << ";\n";
}

void InfoGenerator::genCTorInfo(int pos, const AnalyzerNS::MethodInfo& ctor) {
	genAnotationsInfo(ctor.mAnnotations);

	mOut << "\t\tparamsHolder.clear();\n";
	for(unsigned int i=0; i<ctor.mParameters.size(); i++) {
		mOut << "\t\tparamsHolder.push_back(new ReflectionParam(\"" << ctor.mParameters[i].mName << "\", typeid(" << buildReflectionType(ctor.mParameters[i].mType) << ").name(), \"" << buildReflectionType(ctor.mParameters[i].mType) << "\"));\n";
	}
	mOut << "\t\tctorsHolder.push_back(new ReflectionCTor(paramsHolder, &" << mNamePrefix << "ConstructorCreateFunction" << pos << ", anotationsHolder));\n\n";
}

void InfoGenerator::genMethodInfo(int pos, const AnalyzerNS::MethodInfo& method) {
	genAnotationsInfo(method.mAnnotations);

	mOut << "\t\tparamsHolder.clear();\n";
	for(unsigned int i=0; i<method.mParameters.size(); i++) {
		mOut << "\t\tparamsHolder.push_back(new ReflectionParam(\"" << method.mParameters[i].mName << "\", typeid(" << buildReflectionType(method.mParameters[i].mType) << ").name(), \"" << buildReflectionType(method.mParameters[i].mType) << "\"));\n";
	}
	mOut << "\t\tfunctionsHolder.push_back(new ReflectionFunction(\"" << method.mName << "\", \"" << buildReflectionType(method.mType) << "\", paramsHolder, &" << mNamePrefix << "CallFunction_" << method.mName << pos << ", anotationsHolder));\n\n";
}

void InfoGenerator::genMemberInfo(const AnalyzerNS::FieldInfo& fieldInfo) {
	genAnotationsInfo(fieldInfo.mAnnotations);

	mOut << "\t\tmembersHolder.push_back(new ReflectionMember(\"" << fieldInfo.mName << "\", typeid(" << buildReflectionType(fieldInfo.mType) << ").name(), \"" << buildReflectionType(fieldInfo.mType) << "\", offsetof(" << mNamespace << mClassName << ", " << fieldInfo.mName << "), anotationsHolder));\n";

	if(mGenerateSerialization) {
		genMemberSerializerConverter(fieldInfo.mType);
	}
}

void InfoGenerator::genMemberSerializerConverter(const AnalyzerNS::TypeInfo& typeInfo) {
	if(typeInfo.mTypeName == "vector" || typeInfo.mTypeName == "std::vector") {
		mOut << "\t\tSerializer::getInstance().registerDataConverter(new VectorDataConverter< " << buildReflectionType(typeInfo.mTemplateParameter[0]) << " >());\n";
		if(typeInfo.mTemplateParameter[0].mTemplateParameter.size()>0) {
			genMemberSerializerConverter(typeInfo.mTemplateParameter[0]);
		}
	}
	else if(typeInfo.mTypeName == "map" || typeInfo.mTypeName == "std::map") {
		mOut << "\t\tSerializer::getInstance().registerDataConverter(new MapDataConverter< " << buildReflectionType(typeInfo.mTemplateParameter[0]) << ", " << buildReflectionType(typeInfo.mTemplateParameter[1]) << " >());\n";
		if(typeInfo.mTemplateParameter[0].mTemplateParameter.size()>0) {
			genMemberSerializerConverter(typeInfo.mTemplateParameter[0]);
		}
		if(typeInfo.mTemplateParameter[1].mTemplateParameter.size()>0) {
			genMemberSerializerConverter(typeInfo.mTemplateParameter[1]);
		}
	}
	else if(typeInfo.mTypeName == "pair" || typeInfo.mTypeName == "std::pair") {
		mOut << "\t\tSerializer::getInstance().registerDataConverter(new PairDataConverter< " << buildReflectionType(typeInfo.mTemplateParameter[0]) << ", " << buildReflectionType(typeInfo.mTemplateParameter[1]) << " >());\n";
		if(typeInfo.mTemplateParameter[0].mTemplateParameter.size()>0) {
			genMemberSerializerConverter(typeInfo.mTemplateParameter[0]);
		}
		if(typeInfo.mTemplateParameter[1].mTemplateParameter.size()>0) {
			genMemberSerializerConverter(typeInfo.mTemplateParameter[1]);
		}
	}
}

void InfoGenerator::genAnotationsInfo(const std::vector<AnalyzerNS::Annotation>& anotations) {
	mOut << "\t\tanotationsHolder.clear();\n";
	for(unsigned int i=0; i<anotations.size(); i++) {
		mOut << "\t\tparamsMap.clear();\n";
		std::map<std::string, std::string>::const_iterator iter;
		for(iter=anotations[i].mParameters.begin(); iter!=anotations[i].mParameters.end(); ++iter) {
			mOut << "\t\tparamsMap[\"" << iter->first << "\"] = \"" << iter->second << "\";";
		}
		mOut << "\t\tanotationsHolder[\"" << anotations[i].mName << "\"] = new ReflectionAnotation(\"" << anotations[i].mName << "\", paramsMap);\n";
	}
}

std::string InfoGenerator::buildReflectionType(const AnalyzerNS::TypeInfo& typeInfo) {
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
