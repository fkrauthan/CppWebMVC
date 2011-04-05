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

	for(unsigned int i=0; i<mMappingsWithRegex.size(); i++) {
		boost::cmatch what;
		if(regex_match(request.getRequestURI().c_str(), what, mMappingsWithRegex[i].first)) {
			for(unsigned i2 = 0; i2<what.size()-1; i2++) {
				if(mMappingsGroupNames[i][i2]=="") {
					continue;
				}

				addAttributeToRequest(const_cast<HttpRequest&>(request), mMappingsGroupNames[i][i2], what[i2+1]);
			}

			return mMappingsWithRegex[i].second->handleRequest(request, response);
		}
	}

	//TODO Display 404 Error
	return true;
}

void SimpleUrlMapper::compileRegexs() {
	mMappingsWithRegex.clear();

	std::vector<std::pair<std::string, IBasicController*> >::iterator iter;
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
		mMappingsWithRegex.push_back(std::pair<boost::regex, IBasicController*>(boost::regex(iter->first), iter->second));
	}
}
