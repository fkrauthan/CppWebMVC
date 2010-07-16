/*
 * TestController.cpp
 *
 *  Created on: 28.06.2010
 *      Author: fkrauthan
 */

#include "TestController.h"
#include <webmvc/view/RedirectView.h>


TestController::TestController() {

}

TestController::~TestController() {

}

ModelAndView TestController::handleRequestInternal(const HttpRequest& request, HttpResponse& response) {
	if(request.getRequestURI()=="/test2") {
		response << "Hello World2";
		if(request.hasAttribute("cookie")) {
			response << ": Cookie with value \"" << request.getAttribute("cookie") << "\" was set.";
			response.addCookie(HttpCookie("TestCookie", request.getAttribute("cookie")));
		}
	}
	else if(request.getRequestURI()=="/test3") {
		return ModelAndView(new RedirectView("http://localhost:8080/test2"));
	}
	else {
		response << "Hello World";
		if(request.containsCookie("TestCookie")) {
			response << ": Cookie value=" << request.getCookie("TestCookie").getValue();
		}
		if(request.hasAttribute("view")) {
			response << "<br />View id is: " << request.getAttribute("view");
		}
	}

	return ModelAndView();
}
