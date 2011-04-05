/*
 * TestController2.cpp
 *
 *  Created on: 05.04.2011
 *      Author: fkrauthan
 */

#include "TestController2.h"
#include <webmvc/view/RedirectView.h>
#include <webmvc/data/HttpSession.h>


TestController2::TestController2() {

}

TestController2::~TestController2() {

}

ModelAndView TestController2::testFunction(HttpRequest* request, HttpResponse* response) {
	*response << "Hello World";
	if(request->containsCookie("TestCookie")) {
		*response << ": Cookie value=" << request->getCookie("TestCookie").getValue();
	}
	if(request->hasAttribute("view")) {
		*response << "<br />View id is: " << request->getAttribute("view");
	}

	return ModelAndView();
}
