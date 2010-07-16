/*
 * SimpleUrlMapper.h
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#ifndef SIMPLEURLMAPPER_H_
#define SIMPLEURLMAPPER_H_

#include "../IUrlHandler.h"
#include "../IInterceptor.h"
#include "../../controller/IBasicController.h"
#include <string>
#include <vector>
#include <map>
#include <boost/regex.hpp>


class SimpleUrlMapper : public IUrlHandler {
	public:
		SimpleUrlMapper();
		~SimpleUrlMapper();

		void setInterceptors(std::vector<IInterceptor*> interceptors);
		std::vector<IInterceptor*>& getInterceptors();

		void setMappings(std::vector<std::pair<std::string, IBasicController*> > mappings);
		std::vector<std::pair<std::string, IBasicController*> >& getMappings();


		bool dispatchUrl(const HttpRequest& request, HttpResponse& response);

	private:
		void compileRegexs();

	private:
		std::vector<IInterceptor*> mInterceptors;
		std::vector<std::pair<std::string, IBasicController*> > mMappings;
		std::vector<std::pair<boost::regex, IBasicController*> > mMappingsWithRegex;
};

#endif /* SIMPLEURLMAPPER_H_ */
