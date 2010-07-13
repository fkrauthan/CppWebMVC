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

void SimpleUrlMapper::setMappings(std::map<std::string, IBasicController*> mappings) {
	mMappings = mappings;
}

std::map<std::string, IBasicController*>& SimpleUrlMapper::getMappings() {
	return mMappings;
}

bool SimpleUrlMapper::dispatchUrl(const HttpRequest& request, HttpResponse& response) {
	//TODO run interceptors before

	std::map<std::string, IBasicController*>::iterator iter = mMappings.find(request.getRequestURI());
	if(iter == mMappings.end()) {
		//TODO Display 404 Error
		return true;
	}
	return iter->second->handleRequest(request, response);
}
