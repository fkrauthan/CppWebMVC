/*
 * IUrlHandler.h
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#ifndef IURLHANDLER_H_
#define IURLHANDLER_H_

#include <beans/IObject.h>
#include <webmvc/data/HttpRequest.h>
#include <webmvc/data/HttpResponse.h>


class IUrlHandler : public IObject {
	public:
		virtual ~IUrlHandler() {}

		virtual bool dispatchUrl(const HttpRequest& request, HttpResponse& response) = 0;
};

#endif /* IURLHANDLER_H_ */
