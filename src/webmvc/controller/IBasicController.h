/*
 * IBasicController.h
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#ifndef IBASICCONTROLLER_H_
#define IBASICCONTROLLER_H_

#include <beans/IObject.h>
#include "../data/HttpRequest.h"
#include "../data/HttpResponse.h"


class IBasicController : public IObject {
	public:
		virtual ~IBasicController() {}

		virtual bool handleRequest(const HttpRequest& request, HttpResponse& response) = 0;

};

#endif /* IBASICCONTROLLER_H_ */
