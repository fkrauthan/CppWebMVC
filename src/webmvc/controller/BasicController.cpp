/*
 * BasicController.cpp
 *
 *  Created on: 30.06.2010
 *      Author: fkrauthan
 */

#include "BasicController.h"


BasicController::BasicController() {

}

BasicController::~BasicController() {

}

bool BasicController::handleRequest(const HttpRequest& request, HttpResponse& response) {
	ModelAndView mvc = handleRequestInternal(request, response);
	if(mvc.getView()) {
		mvc.getView()->renderView(request, response, mvc.getModel());
	}

	return true;
}
