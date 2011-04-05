/*
 * Scanner.h
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <string>
#include <vector>
#include <ctime>


class Scanner {
	public:
		Scanner(const std::vector<std::string>& fileExtensions, bool generateSerialization, bool timecheck, const std::string& appPath);
		~Scanner();

		void scan(const std::string& input);

	private:
		void scanFile(const std::string& file);
		void scanFolder(const std::string& folder);

	private:
		bool mGenerateSerialization;
		bool mTimecheck;
		std::vector<std::string> mFileExtensions;

		std::time_t mAppChangeDate;
};

#endif /* SCANNER_H_ */
