/*
 * ClearSilverDefaultViewManager.h
 *
 *  Created on: 26.07.2010
 *      Author: fkrauthan
 */

#ifndef CLEARSILVERDEFAULTVIEWMANAGER_H_
#define CLEARSILVERDEFAULTVIEWMANAGER_H_

#include "../../modelandview/IDefaultViewManager.h"


class ClearSilverDefaultViewManager : public IDefaultViewManager {
	public:
		ClearSilverDefaultViewManager();
		~ClearSilverDefaultViewManager();

		View* createView(const std::string& name);
};

#endif /* CLEARSILVERDEFAULTVIEWMANAGER_H_ */
