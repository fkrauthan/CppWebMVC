/*
 * ReflectionClass.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONCLASS_H_
#define REFLECTIONCLASS_H_

#include "ReflectionFunction.h"
#include "ReflectionCTor.h"
#include <string>
#include <vector>
#include <map>


class ReflectionClass {
	public:
		ReflectionClass(const std::string& name, const std::vector<std::string>& superClasses, const std::vector<ReflectionCTor*>& ctors, const std::vector<ReflectionFunction*>& functions);
		~ReflectionClass();

		std::string& getName();
		std::vector<std::string>& getSuperClasses();

		std::vector<ReflectionCTor*>& getCTors();

		std::vector<ReflectionFunction*>& getMemberFunctions();
		std::vector<ReflectionFunction*> getMemberFunctions(const std::string& name);

	private:
		std::string mName;
		std::vector<std::string> mSuperClasses;
		std::vector<ReflectionCTor*> mCTors;
		std::vector<ReflectionFunction*> mMemberFunctions;
		std::map<std::string, std::vector<ReflectionFunction*> > mSortedMemberFunctions;
};

#endif /* REFLECTIONCLASS_H_ */
