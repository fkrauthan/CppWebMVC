/*
 * CodeGeneration.h
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#ifndef CODEGENERATION_H_
#define CODEGENERATION_H_

#include <string>
#include <fstream>
#include <ctime>
#include "Analyzer.h"


class CodeGeneration {
	public:
		CodeGeneration(const std::string& file, bool generateSerialization, bool timecheck, const std::time_t& appChangeDate);
		~CodeGeneration();

		void scan();

	private:
		void writeHeader();
		void scanObjectData(const AnalyzerNS::ObjectData& objectData);
		void scanObject(const AnalyzerNS::ObjectData& objectData);

	private:
		const std::time_t& mLastAppChange;

		std::string mFile;
		bool mGenerateSerialization;
		bool mTimecheck;

		std::fstream mOut;

		std::string mNamespace;
};

#endif /* CODEGENERATION_H_ */
