/*
 * BeanFactory.h
 *
 *  Created on: 10.06.2010
 *      Author: fkrauthan
 */

#ifndef BEANFACTORY_H_
#define BEANFACTORY_H_

#include <rapidxml/rapidxml.hpp>
#include <boost/any.hpp>
#include "BeanDef.h"
#include <map>


class BeanFactory {
	public:
		BeanFactory();
		~BeanFactory();

		void registerBeanCreator(const std::string& name, IObject* (*creator)(BeanDef*));
		void loadFromXML(const std::string& file);

		bool existBean(const std::string& id);
		IObject* getBean(const std::string& id);
		template<typename T> T* getBean(const std::string& id);


		boost::any convertStringtoBoostAny(const BeanProperty& prop, const std::string& to);
	private:
		void parseBean(rapidxml::xml_node<>* bean_node);
		void parseImport(rapidxml::xml_node<>* import_node);
		bool createBean(BeanDef* def);

		std::string trim(std::string str);
	private:
		std::map<std::string, BeanDef*> beanObjects;
};

#include "BeanFactory.inl"

#endif /* BEANFACTORY_H_ */
