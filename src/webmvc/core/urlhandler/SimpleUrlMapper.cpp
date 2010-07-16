/*
 * SimpleUrlMapper.cpp
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#include "SimpleUrlMapper.h"


SimpleUrlMapper::SimpleUrlMapper() {
}

SimpleUrlMapper::~SimpleUrlMapper() {
}

void SimpleUrlMapper::setInterceptors(std::vector<IInterceptor*> interceptors) {
	mInterceptors = interceptors;
}

std::vector<IInterceptor*>& SimpleUrlMapper::getInterceptors() {
	return mInterceptors;
}

void SimpleUrlMapper::setMappings(std::vector<std::pair<std::string, IBasicController*> > mappings) {
	mMappings = mappings;

	compileRegexs();
}

std::vector<std::pair<std::string, IBasicController*> >& SimpleUrlMapper::getMappings() {
	return mMappings;
}

bool SimpleUrlMapper::dispatchUrl(const HttpRequest& request, HttpResponse& response) {
	//TODO run interceptors before

	std::vector<std::pair<boost::regex, IBasicController*> >::iterator iter;
	for(iter = mMappingsWithRegex.begin(); iter!=mMappingsWithRegex.end(); ++iter) {
		boost::cmatch what;
		if(regex_match(request.getRequestURI().c_str(), what, iter->first)) {
			return iter->second->handleRequest(request, response);
		}
	}

	//TODO Display 404 Error
	return true;
	/*std::map<std::string, IBasicController*>::iterator iter = mMappings.find(request.getRequestURI());
	if(iter == mMappings.end()) {
		//TODO Display 404 Error
		return true;
	}
	return iter->second->handleRequest(request, response);*/
}

void SimpleUrlMapper::compileRegexs() {
	mMappingsWithRegex.clear();

	std::vector<std::pair<std::string, IBasicController*> >::iterator iter;
	for(iter = mMappings.begin(); iter!=mMappings.end(); ++iter) {
		mMappingsWithRegex.push_back(std::pair<boost::regex, IBasicController*>(boost::regex(iter->first), iter->second));
	}
}
