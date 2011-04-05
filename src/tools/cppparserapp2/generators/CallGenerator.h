/*
 * CallGenerator.h
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#ifndef CALLGENERATOR_H_
#define CALLGENERATOR_H_

#include "../Analyzer.h"
#include <vector>
#include <string>
#include <fstream>


class CallGenerator {
	public:
		CallGenerator(const std::string& className, const std::string& _namespace, const std::vector<AnalyzerNS::MethodInfo>& methodInfos, std::fstream& out);
		~CallGenerator();

		void scan();

	private:
		void genMethodCall(int pos, const AnalyzerNS::MethodInfo& method);
		void genCTorCall(int pos, const AnalyzerNS::MethodInfo& ctor);

		void genParamCode(int index, const AnalyzerNS::FieldInfo& fieldInfo);
		std::string buildReflectionType(const AnalyzerNS::TypeInfo& typeInfo);

	private:
		std::string mClassName;
		std::string mNamespace;

		std::string mNamePrefix;

		const std::vector<AnalyzerNS::MethodInfo>& mMethodInfos;
		std::fstream& mOut;

};

#endif /* CALLGENERATOR_H_ */
