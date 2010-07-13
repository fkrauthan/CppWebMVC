/*
 * ReflectionParam.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONPARAM_H_
#define REFLECTIONPARAM_H_

#include <string>


class ReflectionParam {
	public:
		ReflectionParam(const std::string& name, const std::string& type);
		~ReflectionParam();

		std::string& getName();
		std::string& getType();

	private:
		std::string mName;
		std::string mType;
};

#endif /* REFLECTIONPARAM_H_ */
