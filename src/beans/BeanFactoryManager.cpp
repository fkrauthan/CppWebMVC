/*
 * BeanFactoryManager.cpp
 *
 *  Created on: 16.06.2010
 *      Author: fkrauthan
 */

#include "BeanFactoryManager.h"


BeanFactoryManager::BeanFactoryManager() {

}

BeanFactoryManager::~BeanFactoryManager() {

}

void BeanFactoryManager::registerFactory(const std::string& id, IBeanFactory* instance) {
	if(getFactory(id)) {
		//TODO exception schmeißen?
		return;
	}

	mFactorys[id] = instance;
}

void BeanFactoryManager::deRegisterFactory(const std::string& id) {
	std::map<std::string, IBeanFactory*>::iterator iter = mFactorys.find(id);
	if(iter != mFactorys.end()) {
		mFactorys.erase(iter);
	}
}

IBeanFactory* BeanFactoryManager::getFactory(const std::string& id) {
	std::map<std::string, IBeanFactory*>::iterator iter = mFactorys.find(id);
	if(iter == mFactorys.end()) {
		return NULL;
	}

	return iter->second;
}

BeanFactoryManager& BeanFactoryManager::getInstance() {
	static BeanFactoryManager instance;
	return instance;
}
