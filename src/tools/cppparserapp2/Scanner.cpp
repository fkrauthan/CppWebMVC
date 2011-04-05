/*
 * Scanner.cpp
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#include "Scanner.h"
#include "CodeGeneration.h"
#include <boost/filesystem.hpp>


Scanner::Scanner(const std::vector<std::string>& fileExtensions, bool generateSerialization, bool timecheck, const std::string& appPath)
	: mFileExtensions(fileExtensions), mGenerateSerialization(generateSerialization), mTimecheck(timecheck), mAppChangeDate(boost::filesystem::last_write_time(appPath)) {
}

Scanner::~Scanner() {
}

void Scanner::scan(const std::string& input) {
	if(!boost::filesystem::exists(input)) return;

	if(boost::filesystem::is_directory(input)) {
		scanFolder(input);
	}
	else {
		scanFile(input);
	}
}

void Scanner::scanFolder(const std::string& folder) {
	boost::filesystem::directory_iterator end_itr;
	for(boost::filesystem::directory_iterator itr(folder); itr != end_itr; ++itr) {
		scan(itr->path().string());
	}
}

void Scanner::scanFile(const std::string& file) {
	boost::filesystem::path filePath(file);
	if(std::find(mFileExtensions.begin(), mFileExtensions.end(), filePath.extension()) == mFileExtensions.end()) {
		return;
	}

	CodeGeneration codeGen(file, mGenerateSerialization, mTimecheck, mAppChangeDate);
	codeGen.scan();
}
