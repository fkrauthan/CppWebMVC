/*
 * TestController.cpp
 *
 *  Created on: 28.06.2010
 *      Author: fkrauthan
 */

#include "TestController.h"
#include <webmvc/view/RedirectView.h>
#include <webmvc/data/HttpSession.h>


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
	else if(request.getRequestURI()=="/session/info") {
		response << "Session Info<br />Instance: " << request.getSession() << "<br />";
		if(request.getSession()) {
			response << "Session ID: " << request.getSession()->getId() << "<br />";
			response << "Anz Session Items: " << request.getSession()->getAttributeNames().size();
		}

	}
	else if(request.hasAttribute("action")) {
		if(request.getAttribute("action") == "set") {
			response << "Session Set<br />" << "Set key: " << request.getAttribute("key") << "<br />";
			response << "Set value: " << request.getAttribute("value");

			request.getSession()->setAttribute(request.getAttribute("key"), request.getAttribute("value"));
		}
		else {
			response << "Session Get<br />" << "Get for key: " << request.getAttribute("key") << "<br />";
			response << "The Session value: " << request.getSession()->getAttribute(request.getAttribute("key"));
		}
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
