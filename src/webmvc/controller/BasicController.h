/*
 * BasicController.h
 *
 *  Created on: 30.06.2010
 *      Author: fkrauthan
 */

#ifndef BASICCONTROLLER_H_
#define BASICCONTROLLER_H_

#include "IBasicController.h"
#include "../modelandview/ModelAndView.h"


class BasicController : public IBasicController {
	public:
		BasicController();
		virtual ~BasicController();

		bool handleRequest(const HttpRequest& request, HttpResponse& response);

	protected:
		virtual ModelAndView handleRequestInternal(const HttpRequest& request, HttpResponse& response) = 0;
};

#endif /* BASICCONTROLLER_H_ */
