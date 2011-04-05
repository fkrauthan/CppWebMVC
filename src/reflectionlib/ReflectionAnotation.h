/*
 * ReflectionAnotation.h
 *
 *  Created on: 19.09.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONANOTATION_H_
#define REFLECTIONANOTATION_H_

#include <string>
#include <map>


class ReflectionAnotation {
	public:
		ReflectionAnotation(const std::string& name, const std::map<std::string, std::string>& params);
		~ReflectionAnotation();

		std::string& getName();

		std::string getParam(const std::string& name, std::string defaultValue = "");
		template<typename T> T getParam(const std::string& name, T defaultValue);

		const std::map<std::string, std::string>& getParams();

		bool hasParam(const std::string& name);

	private:
		std::string mName;
		std::map<std::string, std::string> mParams;
};

#include "ReflectionAnotation.inl"

#endif /* REFLECTIONANOTATION_H_ */
