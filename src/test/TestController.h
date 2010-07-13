/*
 * TestController.h
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#ifndef TESTCONTROLLER_H_
#define TESTCONTROLLER_H_

#include <webmvc/controller/BasicController.h>


class TestController : public BasicController {
	public:
		TestController();
		~TestController();

	protected:
		ModelAndView handleRequestInternal(const HttpRequest& request, HttpResponse& response);
};

#endif /* TESTCONTROLLER_H_ */
