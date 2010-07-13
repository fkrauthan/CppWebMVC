/*
 * ReflectionFactory.h
 *
 *  Created on: 16.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONFACTORY_H_
#define REFLECTIONFACTORY_H_

#include "../BeanFactoryManager.h"
#include <string>


class ReflectionFactory : public IBeanFactory {
	public:
		ReflectionFactory();
		~ReflectionFactory();

		IObject* getInstance(BeanDef* def, BeanFactory* factory);
};

#endif /* REFLECTIONFACTORY_H_ */
