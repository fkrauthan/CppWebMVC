/*
 * CodeGeneration.cpp
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#include "CodeGeneration.h"
#include "Analyzer.h"
#include "generators/CallGenerator.h"
#include "generators/InfoGenerator.h"
#include <iostream>
#include <ctime>
#include <boost/filesystem.hpp>


CodeGeneration::CodeGeneration(const std::string& file, bool generateSerialization, bool timecheck, const std::time_t& appChangeDate)
	: mLastAppChange(appChangeDate), mFile(file), mGenerateSerialization(generateSerialization), mTimecheck(timecheck) {
}

CodeGeneration::~CodeGeneration() {
}

void CodeGeneration::scan() {
	std::cout << "Parse file: " << mFile << "...";
	boost::filesystem::path headerPath(mFile+".rf2.cpp");
	if(boost::filesystem::exists(headerPath) && mTimecheck) {
		std::time_t lastOutputWriteTime = boost::filesystem::last_write_time(headerPath);
		if(boost::filesystem::last_write_time(mFile)<=lastOutputWriteTime && mLastAppChange<=lastOutputWriteTime) {
			std::cout << "skipped" << std::endl;
			return;
		}
	}


	AnalyzerNS::Analyzer analyzer;
	analyzer.Analyze(mFile);
	if(analyzer.MainObjects.size() > 0) {
		mOut.open(std::string(mFile+".rf2.cpp").c_str(), std::ios::out);
		if(!mOut.is_open()) {
			std::cout << "failed (Can't create output file)" << std::endl;
			return;
		}

		//Generate header
		writeHeader();


		//Genereate infos for class
		for(unsigned int i=0; i<analyzer.MainObjects.size(); i++) {
			mNamespace = "";
			scanObjectData(analyzer.MainObjects[i]);
		}


		//Finish generating
		mOut << "\n";
		mOut.close();

		std::cout << "generated" << std::endl;
	}
	else {
		std::cout << "ignored" << std::endl;
	}
}

void CodeGeneration::scanObjectData(const AnalyzerNS::ObjectData& objectData) {
	if(objectData.mQualifier != AnalyzerNS::Qualifier::Public) {
		return;
	}

	if(objectData.mObjectType == AnalyzerNS::ObjectType::Namespace) {
		mNamespace += objectData.mName+"::";
		for(unsigned int i=0; i<objectData.mChildObjects.size(); i++) {
			scanObjectData(objectData.mChildObjects[i]);
		}
	}
	else if(objectData.mObjectType == AnalyzerNS::ObjectType::Class || objectData.mObjectType == AnalyzerNS::ObjectType::Struct) {
		scanObject(objectData);

		if(objectData.mChildObjects.size() > 0) {
			std::string tmpNamespace = mNamespace;
			mNamespace += objectData.mName+"::";
			for(unsigned int i=0; i<objectData.mChildObjects.size(); i++) {
				scanObjectData(objectData.mChildObjects[i]);
			}
			mNamespace = tmpNamespace;
		}
	}
}

void CodeGeneration::scanObject(const AnalyzerNS::ObjectData& objectData) {
	CallGenerator callGen(objectData.mName, mNamespace, objectData.mMethods, mOut);
	callGen.scan();
	mOut << "\n";

	InfoGenerator infoGen(objectData.mName, mNamespace, mGenerateSerialization, objectData, mOut);
	infoGen.scan();
	mOut << "\n";
}

void CodeGeneration::writeHeader() {
	std::time_t rawtime;
	struct std::tm * timeinfo;
	char buffer[11];

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);
	std::strftime(buffer, 11, "%d.%m.%Y", timeinfo);


	boost::filesystem::path filePath(mFile);
	mOut << "/*\n";
	mOut << " * Reflection registration for header: " << filePath.filename() << "\n *\n";
	mOut << " *   Created on: " << buffer << "\n";
	mOut << " *       Author: CodeGenerator V2.0\n";
	mOut << " */\n\n";
	mOut << "#include \"" + filePath.filename() + "\"\n";
	mOut << "#include <reflectionlib/Reflection.h>\n";
	mOut << "#include <reflectionlib/ReflectionConverter.h>\n";
	mOut << "#include <vector>\n";
	mOut << "#include <stddef.h>\n";
	mOut << "#include <boost/any.hpp>\n";

	if(mGenerateSerialization) {
		mOut << "#include <serializationlib/Serializer.h>\n";
		mOut << "#include <serializationlib/MapDataConverter.h>\n";
		mOut << "#include <serializationlib/PairDataConverter.h>\n";
		mOut << "#include <serializationlib/VectorDataConverter.h>\n";
	}

	mOut << "\n";
}
