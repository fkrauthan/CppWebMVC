/*
 * ClearSilverView.h
 *
 *  Created on: 26.07.2010
 *      Author: fkrauthan
 */

#ifndef CLEARSILVERVIEW_H_
#define CLEARSILVERVIEW_H_

#include "../../modelandview/View.h"
#include <string>


class ClearSilverView : public View {
	public:
		ClearSilverView(const std::string& templateFile);
		~ClearSilverView();

		void renderView(const HttpRequest& request, HttpResponse& response, const std::map<std::string, boost::any>& model);

	private:
		std::string mTemplateFile;
};

#endif /* CLEARSILVERVIEW_H_ */
