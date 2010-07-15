/*
 * ReflectionMember.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONMEMBER_H_
#define REFLECTIONMEMBER_H_

#include <string>


class ReflectionMember {
	public:
		ReflectionMember(const std::string& name, const std::string& typeIdName, const std::string& type, int offset);
		~ReflectionMember();

		std::string& getName();
		std::string& getTypeIdName();
		std::string& getType();
		int getOffset();

	private:
		std::string mName;
		std::string mTypeIdName;
		std::string mType;
		int mOffset;
};

#endif /* REFLECTIONMEMBER_H_ */
