/*
 * AnotatedUrlMapper.cpp
 *
 *  Created on: 05.04.2011
 *      Author: fkrauthan
 */

#include "AnotatedUrlMapper.h"
#include <reflections/Reflection.h>


AnotatedUrlMapper::AnotatedUrlMapper(bool search) : mSearchForAntotatedClasses(search) {
	if(mSearchForAntotatedClasses) {
		searchForClasses();
	}
}

AnotatedUrlMapper::~AnotatedUrlMapper() {
}

void AnotatedUrlMapper::setSearchForAnotatedClasses(bool search) {
	mSearchForAntotatedClasses = search;

	if(mSearchForAntotatedClasses) {
		searchForClasses();
	}
}

bool AnotatedUrlMapper::getSearchForAnotatedClasses() {
	return mSearchForAntotatedClasses;
}

void AnotatedUrlMapper::setInterceptors(std::vector<IInterceptor*> interceptors) {
	mInterceptors = interceptors;
}

std::vector<IInterceptor*>& AnotatedUrlMapper::getInterceptors() {
	return mInterceptors;
}

void AnotatedUrlMapper::setClasses(std::vector<IObject*> classes) {
	mClasses = classes;

	searchForFunctions();
}

std::vector<IObject*>& AnotatedUrlMapper::getClasses() {
	return mClasses;
}

bool AnotatedUrlMapper::dispatchUrl(const HttpRequest& request, HttpResponse& response) {
	//TODO run interceptors before

	for(unsigned int i=0; i<mMappingsWithRegex.size(); i++) {
		boost::cmatch what;
		if(regex_match(request.getRequestURI().c_str(), what, mMappingsWithRegex[i].first)) {
			for(unsigned i2 = 0; i2<what.size()-1; i2++) {
				if(mMappingsGroupNames[i][i2]=="") {
					continue;
				}

				addAttributeToRequest(const_cast<HttpRequest&>(request), mMappingsGroupNames[i][i2], what[i2+1]);
			}

			std::vector<boost::any> params;
			params.push_back(request);
			params.push_back(response);
			return mMappingsWithRegex[i].second.second->invoke<bool>(mMappingsWithRegex[i].second.first, params);
		}
	}

	//TODO Display 404 Error
	return true;
}

void AnotatedUrlMapper::searchForClasses() {
	//TODO must be written
}

void AnotatedUrlMapper::searchForFunctions() {
	mMappings.clear();

	Reflection& reflection = Reflection::getInstance();
	for(unsigned int i=0; i<mClasses.size(); i++) {
		ReflectionClass* refClass = reflection.getClassByTypeId(typeid(*mClasses[i]).name());
		std::vector<ReflectionFunction*>& functions = refClass->getMemberFunctions();
		for(unsigned int i2=0; i2<functions.size(); i2++) {
			ReflectionFunction* function = functions[i2];
			//TODO Search for anotations
		}
	}

	compileRegexs();
}

void AnotatedUrlMapper::compileRegexs() {
	mMappingsWithRegex.clear();

	std::vector<std::pair<std::string, std::pair<IObject*, ReflectionFunction*> > >::iterator iter;
	for(iter = mMappings.begin(); iter!=mMappings.end(); ++iter) {
	    std::vector<std::string> tmpGroupNames;
		size_t findPos = 0;
		while((findPos = iter->first.find("(", findPos)) != std::string::npos) {
	        if(iter->first.substr(findPos+1, 2) != "?<") {
	            tmpGroupNames.push_back("");
	            findPos++;
				continue;
	        }

			size_t endPos = iter->first.find('>', findPos);
			if(endPos==std::string::npos) {
				findPos++;
				continue;
			}

			tmpGroupNames.push_back(iter->first.substr(findPos+3, endPos-findPos-3));
			iter->first.erase(findPos+1, endPos-findPos);
	        findPos++;
		}

		mMappingsGroupNames.push_back(tmpGroupNames);
		mMappingsWithRegex.push_back(std::pair<boost::regex, std::pair<IObject*, ReflectionFunction*> >(boost::regex(iter->first), iter->second));
	}
}
