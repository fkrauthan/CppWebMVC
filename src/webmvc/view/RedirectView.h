/*
 * RedirectView.h
 *
 *  Created on: 02.07.2010
 *      Author: fkrauthan
 */

#ifndef REDIRECTVIEW_H_
#define REDIRECTVIEW_H_

#include "../modelandview/View.h"
#include <string>


class RedirectView : public View {
	public:
		RedirectView(const std::string& target, bool relativ=true);

		void renderView(const HttpRequest& request, HttpResponse& response, const std::map<std::string, boost::any>& model);

	private:
		bool mRelativ;
		std::string mTarget;

};

#endif /* REDIRECTVIEW_H_ */
