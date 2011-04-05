/*
 * TestController2.h
 *
 *  Created on: 05.04.2011
 *      Author: fkrauthan
 */

#ifndef TESTCONTROLLER2_H_
#define TESTCONTROLLER2_H_

#include <webmvc/controller/BasicController.h>


class TestController2 : public BasicController {
	public:
		TestController2();
		~TestController2();

	protected:
		// @Request (url="/text")
		ModelAndView testFunction(const HttpRequest& request, HttpResponse& response);
};

#endif /* TESTCONTROLLER2_H_ */
