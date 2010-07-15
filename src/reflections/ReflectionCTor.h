/*
 * ReflectionCTor.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONCTOR_H_
#define REFLECTIONCTOR_H_

#include "ReflectionParam.h"
#include <boost/any.hpp>
#include <vector>


class ReflectionCTor {
	public:
		ReflectionCTor(const std::vector<ReflectionParam*>& params, void* (*constructorMethod)(const std::vector<boost::any>&));
		~ReflectionCTor();

		std::vector<ReflectionParam*>& getParams();

		template<typename T> T* createInstance(const std::vector<boost::any>& params = std::vector<boost::any>());
		void* createInstance(const std::vector<boost::any>& params = std::vector<boost::any>());
	private:
		std::vector<ReflectionParam*> mParams;

		void* (*mConstructorMethod)(const std::vector<boost::any>&);
};


#include "ReflectionCTor.inl"

#endif /* REFLECTIONCTOR_H_ */
