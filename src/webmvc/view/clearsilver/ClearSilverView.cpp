/*
 * ClearSilverView.cpp
 *
 *  Created on: 26.07.2010
 *      Author: fkrauthan
 */

#include "ClearSilverView.h"


ClearSilverView::ClearSilverView(const std::string& templateFile) : mTemplateFile(templateFile) {
}

ClearSilverView::~ClearSilverView() {
}

void ClearSilverView::renderView(const HttpRequest& request, HttpResponse& response, const std::map<std::string, boost::any>& model) {

}
