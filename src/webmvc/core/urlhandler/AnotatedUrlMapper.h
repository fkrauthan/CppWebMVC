/*
 * AnotatedUrlMapper.h
 *
 *  Created on: 05.04.2011
 *      Author: fkrauthan
 */

#ifndef ANOTATEDURLMAPPER_H_
#define ANOTATEDURLMAPPER_H_

#include "../IUrlHandler.h"
#include "../IInterceptor.h"
#include "../../controller/IBasicController.h"
#include <reflections/ReflectionFunction.h>
#include <string>
#include <vector>
#include <map>
#include <boost/regex.hpp>


class AnotatedUrlMapper : public IUrlHandler {
	public:
		AnotatedUrlMapper(bool search=false);
		~AnotatedUrlMapper();

		void setSearchForAnotatedClasses(bool search);
		bool getSearchForAnotatedClasses();

		void setInterceptors(std::vector<IInterceptor*> interceptors);
		std::vector<IInterceptor*>& getInterceptors();

		void setClasses(std::vector<IObject*> classes);
		std::vector<IObject*>& getClasses();


		bool dispatchUrl(const HttpRequest& request, HttpResponse& response);

	private:
		void searchForClasses();
		void searchForFunctions();

		void compileRegexs();

	private:
		bool mSearchForAntotatedClasses;

		std::vector<IInterceptor*> mInterceptors;
		std::vector<IObject*> mClasses;

		std::vector<std::pair<std::string, std::pair<IObject*, ReflectionFunction*> > > mMappings;

		std::vector<std::pair<boost::regex, std::pair<IObject*, ReflectionFunction*> > > mMappingsWithRegex;
		std::vector<std::vector<std::string> > mMappingsGroupNames;
};

#endif /* ANOTATEDURLMAPPER_H_ */
