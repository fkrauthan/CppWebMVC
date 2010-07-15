/*
 * ReflectionClass.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONCLASS_H_
#define REFLECTIONCLASS_H_

#include "ReflectionMember.h"
#include "ReflectionFunction.h"
#include "ReflectionCTor.h"
#include <string>
#include <vector>
#include <map>


class ReflectionClass {
	public:
		enum ClassType {
			CLASS,
			STRUCT
		};

	public:
		ReflectionClass(const std::string& name, const std::string& typeIdName, const std::vector<std::string>& superClasses, const std::vector<ReflectionCTor*>& ctors, const std::vector<ReflectionFunction*>& functions, std::vector<ReflectionMember*> vars, ClassType classType);
		~ReflectionClass();

		std::string& getName();
		std::string& getTypeIdName();
		std::vector<std::string>& getSuperClasses();

		std::vector<ReflectionCTor*>& getCTors();

		std::vector<ReflectionFunction*>& getMemberFunctions();
		std::vector<ReflectionFunction*> getMemberFunctions(const std::string& name);

		std::vector<ReflectionMember*>& getMemberVars();
		ReflectionMember* getMemberVar(const std::string& name);

		ClassType getClassType();
	private:
		std::string mName;
		std::string mTypeIdName;
		std::vector<std::string> mSuperClasses;
		std::vector<ReflectionCTor*> mCTors;
		std::vector<ReflectionFunction*> mMemberFunctions;
		std::vector<ReflectionMember*> mMemberVars;
		std::map<std::string, std::vector<ReflectionFunction*> > mSortedMemberFunctions;

		ClassType mClassType;
};

#endif /* REFLECTIONCLASS_H_ */
