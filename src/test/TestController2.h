/*
 * TestController2.h
 *
 *  Created on: 05.04.2011
 *      Author: fkrauthan
 */

#ifndef TESTCONTROLLER2_H_
#define TESTCONTROLLER2_H_

#include <webmvc/controller/BasicController.h>


class TestController2 : public IObject {
	public:
		TestController2();
		~TestController2();

		// @Request (url="/text")
		ModelAndView testFunction(HttpRequest* request, HttpResponse* response);
};

#endif /* TESTCONTROLLER2_H_ */
