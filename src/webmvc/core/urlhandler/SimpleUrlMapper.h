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


class SimpleUrlMapper : public IUrlHandler {
	public:
		SimpleUrlMapper();
		~SimpleUrlMapper();

		void setInterceptors(std::vector<IInterceptor*> interceptors);
		std::vector<IInterceptor*>& getInterceptors();

		void setMappings(std::map<std::string, IBasicController*> mappings);
		std::map<std::string, IBasicController*>& getMappings();


		bool dispatchUrl(const HttpRequest& request, HttpResponse& response);

	private:
		std::vector<IInterceptor*> mInterceptors;
		std::map<std::string, IBasicController*> mMappings;
};

#endif /* SIMPLEURLMAPPER_H_ */
