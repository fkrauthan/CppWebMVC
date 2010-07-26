/*
 * IDefaultViewManager.h
 *
 *  Created on: 26.07.2010
 *      Author: fkrauthan
 */

#ifndef IDEFAULTVIEWMANAGER_H_
#define IDEFAULTVIEWMANAGER_H_

#include <beans/IObject.h>
#include "View.h"
#include <string>


class IDefaultViewManager : public IObject {
	public:
		~IDefaultViewManager() {};

		virtual View* createView(const std::string& name) = 0;
};

#endif /* IDEFAULTVIEWMANAGER_H_ */
