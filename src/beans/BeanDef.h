/*
 * BeanDef.h
 *
 *  Created on: 11.06.2010
 *      Author: fkrauthan
 */

#ifndef BEANDEF_H_
#define BEANDEF_H_

#include <string>
#include <vector>
#include <map>

class IObject;


struct BeanProperty {
	std::string value;

	bool isMap;
	std::vector<std::pair<std::string, std::string> > valueMap;

	bool isVector;
	std::vector<std::string> valueVector;
};

struct BeanDef {
	std::string id;
	std::string className;

	std::string factoryName;

	bool persistent;
	bool lazyLoading;

	std::vector<BeanProperty> constructorParameter;
	std::map<std::string, BeanProperty> propertieParameter;

	std::vector<IObject*> pointers;
};

#endif /* BEANDEF_H_ */
