/*
 * BeanFactoryManager.h
 *
 *  Created on: 16.06.2010
 *      Author: fkrauthan
 */

#ifndef BEANFACTORYMANAGER_H_
#define BEANFACTORYMANAGER_H_

#include "IBeanFactory.h"
#include <string>
#include <map>


class BeanFactoryManager {
	public:
		BeanFactoryManager();
		~BeanFactoryManager();

		void registerFactory(const std::string& id, IBeanFactory* instance);
		void deRegisterFactory(const std::string& id);

		IBeanFactory* getFactory(const std::string& id);

	public:
		static BeanFactoryManager& getInstance();

	private:
		std::map<std::string, IBeanFactory*> mFactorys;
};

#endif /* BEANFACTORYMANAGER_H_ */
