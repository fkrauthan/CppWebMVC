/*
 * ClearSilverDefaultViewManager.cpp
 *
 *  Created on: 26.07.2010
 *      Author: fkrauthan
 */

#include "ClearSilverDefaultViewManager.h"
#include "ClearSilverView.h"


ClearSilverDefaultViewManager::ClearSilverDefaultViewManager() {
}

ClearSilverDefaultViewManager::~ClearSilverDefaultViewManager() {
}

View* ClearSilverDefaultViewManager::createView(const std::string& name) {
	return new ClearSilverView();
}
