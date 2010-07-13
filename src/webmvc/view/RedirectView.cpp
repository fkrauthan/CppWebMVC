/*
 * RedirectView.cpp
 *
 *  Created on: 02.07.2010
 *      Author: fkrauthan
 */

#include "RedirectView.h"


RedirectView::RedirectView(const std::string& target, bool relativ) {
	mRelativ = relativ;
	mTarget = target;
}

void RedirectView::renderView(const HttpRequest& request, HttpResponse& response, const std::map<std::string, boost::any>& model) {
	std::string tmpTarget = mTarget;
	if(mRelativ) {
		//TODO relativ path info
	}

	response.sendRedirect(tmpTarget);
	response.flush();
}
