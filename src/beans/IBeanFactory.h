/*
 * IBeanFactory.h
 *
 *  Created on: 16.06.2010
 *      Author: fkrauthan
 */

#ifndef IBEANFACTORY_H_
#define IBEANFACTORY_H_

#include "BeanDef.h"
#include "BeanFactory.h"


class IBeanFactory {
	public:
		virtual ~IBeanFactory() {};

		virtual IObject* getInstance(BeanDef* def, BeanFactory* factory) = 0;
};

#endif /* IBEANFACTORY_H_ */
