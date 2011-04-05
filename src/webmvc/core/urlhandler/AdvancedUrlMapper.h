/*
 * AdvancedUrlMapper.h
 *
 *  Created on: 05.04.2011
 *      Author: fkrauthan
 */

#ifndef ADVANCEDURLMAPPER_H_
#define ADVANCEDURLMAPPER_H_

#include "../IUrlHandler.h"
#include "../IInterceptor.h"
#include "../../controller/IBasicController.h"
#include <string>
#include <vector>
#include <map>
#include <boost/regex.hpp>


class AdvancedUrlMapper : public IUrlHandler {
	public:
		AdvancedUrlMapper();
		~AdvancedUrlMapper();

		void setInterceptors(std::vector<IInterceptor*> interceptors);
		std::vector<IInterceptor*>& getInterceptors();

		void setMappings(std::vector<std::pair<std::string, std::pair<std::string, IBasicController*> > > mappings);
		std::vector<std::pair<std::string, std::pair<std::string, IBasicController*> > >& getMappings();


		bool dispatchUrl(const HttpRequest& request, HttpResponse& response);

	private:
		void compileRegexs();

	private:
		std::vector<IInterceptor*> mInterceptors;
		std::vector<std::pair<std::string, std::pair<std::string, IBasicController*> > > mMappings;
		std::vector<std::pair<boost::regex, std::pair<IBasicController*> > > mMappingsWithRegex;
		std::vector<std::vector<std::string> > mMappingsGroupNames;
};

#endif /* ADVANCEDURLMAPPER_H_ */
