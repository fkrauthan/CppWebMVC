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
#include "ReflectionAnotation.h"
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
		ReflectionClass(const std::string& name, const std::string& typeIdName, const std::string& pointerTypeIdName, const std::vector<std::string>& superClasses, const std::vector<ReflectionCTor*>& ctors, const std::vector<ReflectionFunction*>& functions, std::vector<ReflectionMember*> vars, ClassType classType, const std::map<std::string, ReflectionAnotation*>& anotations);
		~ReflectionClass();

		std::string& getName();
		std::string& getTypeIdName();
		std::string& getPointerTypeIdName();
		std::vector<std::string>& getSuperClasses();

		std::vector<ReflectionCTor*>& getCTors();

		std::vector<ReflectionFunction*>& getMemberFunctions();
		std::vector<ReflectionFunction*> getMemberFunctions(const std::string& name);

		std::vector<ReflectionMember*>& getMemberVars();
		ReflectionMember* getMemberVar(const std::string& name);

		ClassType getClassType();

		const std::map<std::string, ReflectionAnotation*>& getAnotations();
		ReflectionAnotation* getAnotation(const std::string& name);

	private:
		std::string mName;
		std::string mTypeIdName;
		std::string mPointerTypeIdName;
		std::vector<std::string> mSuperClasses;
		std::vector<ReflectionCTor*> mCTors;
		std::vector<ReflectionFunction*> mMemberFunctions;
		std::vector<ReflectionMember*> mMemberVars;
		std::map<std::string, std::vector<ReflectionFunction*> > mSortedMemberFunctions;

		std::map<std::string, ReflectionAnotation*> mAnotations;

		ClassType mClassType;
};

#endif /* REFLECTIONCLASS_H_ */
