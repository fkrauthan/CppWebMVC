/*
 * ReflectionMember.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONMEMBER_H_
#define REFLECTIONMEMBER_H_

#include "ReflectionAnotation.h"
#include <string>


class ReflectionMember {
	public:
		ReflectionMember(const std::string& name, const std::string& typeIdName, const std::string& type, int offset, const std::map<std::string, ReflectionAnotation*>& anotations);
		~ReflectionMember();

		std::string& getName();
		std::string& getTypeIdName();
		std::string& getType();
		int getOffset();

		const std::map<std::string, ReflectionAnotation*>& getAnotations();
		ReflectionAnotation* getAnotation(const std::string& name);

	private:
		std::string mName;
		std::string mTypeIdName;
		std::string mType;
		int mOffset;

		std::map<std::string, ReflectionAnotation*> mAnotations;
};

#endif /* REFLECTIONMEMBER_H_ */
