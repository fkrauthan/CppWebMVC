/*
 * ModelAndView.h
 *
 *  Created on: 01.07.2010
 *      Author: fkrauthan
 */

#ifndef MODELANDVIEW_H_
#define MODELANDVIEW_H_

#include "View.h"
#include <string>
#include <map>


class ModelAndView {
	public:
		ModelAndView();
		//TODO: ModelAndView(const std::string& templateName);
		//TODO: ModelAndView(const std::string& templateName, std::string params);
		ModelAndView(View* view);
		ModelAndView(View* view, const std::string& modelName, const boost::any& modelObject);
		ModelAndView(View* view, const std::map<std::string, boost::any>& model);
		~ModelAndView();

		View* getView();
		const std::map<std::string, boost::any>& getModel() const;

		void addModel(const std::string& name, const boost::any& object);
		const boost::any& getModel(const std::string& name) const;
		void removeModel(const std::string& name);

	private:
		View* mView;
		std::map<std::string, boost::any> mModel;
};

#endif /* MODELANDVIEW_H_ */
