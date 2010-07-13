/*
 * View.h
 *
 *  Created on: 01.07.2010
 *      Author: fkrauthan
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "../data/HttpRequest.h"
#include "../data/HttpResponse.h"
#include <beans/IObject.h>
#include <map>
#include <string>
#include <boost/any.hpp>


class View {
	public:
		virtual ~View() {};

		virtual void renderView(const HttpRequest& request, HttpResponse& response, const std::map<std::string, boost::any>& model) = 0;
};
#endif /* VIEW_H_ */
