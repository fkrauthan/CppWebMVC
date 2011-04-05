/*
 * InfoGenerator.h
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#ifndef INFOGENERATOR_H_
#define INFOGENERATOR_H_

#include "../Analyzer.h"
#include <vector>
#include <string>
#include <fstream>


class InfoGenerator {
	public:
		InfoGenerator(const std::string& className, const std::string& _namespace, bool generateSerialization, const AnalyzerNS::ObjectData& object, std::fstream& out);
		~InfoGenerator();

		void scan();

	private:
		void generateHeader();
		void generateFooter();

		void genCTorInfo(int pos, const AnalyzerNS::MethodInfo& ctor);
		void genMethodInfo(int pos, const AnalyzerNS::MethodInfo& method);

		void genMemberInfo(const AnalyzerNS::FieldInfo& fieldInfo);
		void genMemberSerializerConverter(const AnalyzerNS::TypeInfo& typeInfo);

		void genAnotationsInfo(const std::vector<AnalyzerNS::Annotation>& anotations);

		std::string buildReflectionType(const AnalyzerNS::TypeInfo& typeInfo);

		bool shouldPrintFunction(const AnalyzerNS::MethodInfo& method);

	private:
		std::string mClassName;
		std::string mNamespace;

		std::string mNamePrefix;

		bool mGenerateSerialization;

		const AnalyzerNS::ObjectData& mObject;
		std::fstream& mOut;
};

#endif /* INFOGENERATOR_H_ */
