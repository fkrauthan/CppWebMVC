/*
 * BeanFactory.cpp
 *
 *  Created on: 10.06.2010
 *      Author: fkrauthan
 */

#include "BeanFactory.h"
#include "BeanFactoryException.h"
#include "BeanFactoryManager.h"
#include "IObject.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <boost/lexical_cast.hpp>

using namespace rapidxml;


BeanFactory::BeanFactory() {
}

BeanFactory::~BeanFactory() {
	std::map<std::string, BeanDef*>::iterator iter;
	for(iter=beanObjects.begin(); iter!=beanObjects.end(); ++iter) {
		for(unsigned int i=0; i<iter->second->pointers.size(); i++) {
			delete iter->second->pointers[i];
		}

		delete iter->second;
	}
}

void BeanFactory::loadFromXML(const std::string& file) {
	xml_document<> doc;

	std::ifstream ifs(file.c_str());
	if(!ifs.is_open()) {
		throw BeanFactoryException("Can't open bean defenition file");
	}
	std::string xmlDoc((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	std::vector<char> xml_copy(xmlDoc.begin(),xmlDoc.end());
	xml_copy.push_back('\0');

	//Parsing the document
	doc.parse<0>(&xml_copy[0]);
	xml_node<>* beans_node = doc.first_node("beans");
	if(!beans_node) {
		throw BeanFactoryException("No beans tag found");
	}


	//Parsing file
	xml_node<>* node = beans_node->first_node();
	while(node) {
		if(std::strcmp(node->name(), "import") == 0) {
			parseImport(node);
		}
		else if(std::strcmp(node->name(), "bean") == 0) {
			parseBean(node);
		}

		node = node->next_sibling();
	}
}

bool BeanFactory::existBean(const std::string& id) {
	std::map<std::string, BeanDef*>::iterator iter = beanObjects.find(id);
	return iter!=beanObjects.end();
}

IObject* BeanFactory::getBean(const std::string& id) {
	std::map<std::string, BeanDef*>::iterator iter = beanObjects.find(id);
	if(iter == beanObjects.end()) {
		return NULL;
	}

	BeanDef* beanDef = iter->second;
	if((beanDef->lazyLoading && beanDef->pointers.size()<=0)||!beanDef->persistent) {
		if(!createBean(beanDef)) {
			throw BeanFactoryException("Can't create a instance of a bean");
		}
		return beanDef->pointers[beanDef->pointers.size()-1];
	}
	else if(beanDef->pointers.size()<=0) {
		throw BeanFactoryException("No bean instances created. This should never happend.");
	}
	else {
		return beanDef->pointers[0];
	}
}

void BeanFactory::parseImport(xml_node<>* import_node) {
	std::string resource = import_node->first_attribute("resource")->value();
	loadFromXML(resource);
}

void BeanFactory::parseBean(xml_node<>* bean_node) {
	BeanDef* def = new BeanDef();
	def->lazyLoading = false;
	def->persistent = true;
	def->factoryName = "ReflectionFactory";

	xml_attribute<>* attr = bean_node->first_attribute("factory");
	if(attr) {
		def->factoryName = attr->value();
	}

	attr = bean_node->first_attribute("class");
	if(attr) {
		def->className = attr->value();
	}

	attr = bean_node->first_attribute("id");
	if(attr) {
		def->id = attr->value();
	}
	else {
		def->id = def->className;
	}

	if(existBean(def->id)) {
		delete def;
		throw BeanFactoryException("A bean with this id exists already");
	}

	attr = bean_node->first_attribute("lazyloading");
	if(attr) {
		if(std::strcmp(attr->value(), "true") == 0) {
			def->lazyLoading = true;
		}
	}

	attr = bean_node->first_attribute("persistent");
	if(attr) {
		if(std::strcmp(attr->value(), "false") == 0) {
			def->persistent = false;
		}
	}

	//Load ctor params
	rapidxml::xml_node<>* cTorNode = bean_node->first_node("constructor-arg");
	while(cTorNode) {
		BeanProperty prop;
		prop.isMap = false;
		prop.isVector = false;

		//Read map
		rapidxml::xml_node<>* tmpNode = cTorNode->first_node("map");
		if(tmpNode) {
			prop.isMap = true;
			tmpNode = tmpNode->first_node("item");
			while(tmpNode) {
				std::string key = tmpNode->first_attribute("key")->value();
				prop.valueMap.push_back(std::pair<std::string, std::string>(key, tmpNode->value()));

				tmpNode = tmpNode->next_sibling("item");
			}
		}

		//Read vector
		tmpNode = cTorNode->first_node("list");
		if(tmpNode && !prop.isMap) {
			prop.isVector = true;
			tmpNode = tmpNode->first_node("item");
			while(tmpNode) {
				prop.valueVector.push_back(tmpNode->value());

				tmpNode = tmpNode->next_sibling("item");
			}
		}

		//Read value
		if(!prop.isMap && !prop.isVector) {
			prop.value = cTorNode->value();
		}

		def->constructorParameter.push_back(prop);
		cTorNode = cTorNode->next_sibling("constructor-arg");
	}

	//Load property params
	rapidxml::xml_node<>* propNode = bean_node->first_node("property");
	while(propNode) {
		BeanProperty prop;
		prop.isMap = false;
		prop.isVector = false;


		std::string name = propNode->first_attribute("name")->value();
		attr = propNode->first_attribute("ref");
		if(attr) {
			prop.value = attr->value();
			if(!existBean(prop.value)) {
				delete def;
				throw BeanFactoryException("A referenced bean dosen't exist");
			}
		}
		else {
			//Read map
			rapidxml::xml_node<>* tmpNode = propNode->first_node("map");
			if(tmpNode) {
				prop.isMap = true;
				tmpNode = tmpNode->first_node("item");
				while(tmpNode) {
					std::string key = tmpNode->first_attribute("key")->value();
					prop.valueMap.push_back(std::pair<std::string, std::string>(key, tmpNode->value()));

					tmpNode = tmpNode->next_sibling("item");
				}
			}

			//Read vector
			tmpNode = propNode->first_node("list");
			if(tmpNode && !prop.isMap) {
				prop.isVector = true;
				tmpNode = tmpNode->first_node("item");
				while(tmpNode) {
					prop.valueVector.push_back(tmpNode->value());

					tmpNode = tmpNode->next_sibling("item");
				}
			}

			if(!prop.isMap && !prop.isVector) {
				prop.value = propNode->first_attribute("value")->value();
			}
		}

		def->propertieParameter[name] = prop;


		propNode = propNode->next_sibling("property");
	}

	beanObjects[def->id] = def;
	if(!def->lazyLoading) {
		try {
			createBean(def);
		} catch(const BeanFactoryException& ex) {
			std::map<std::string, BeanDef*>::iterator iter = beanObjects.find(def->id);
			if(iter != beanObjects.end()) {
				beanObjects.erase(iter);
			}
			delete def;

			throw BeanFactoryException(ex.what());
		}
	}
}

bool BeanFactory::createBean(BeanDef* def) {
	//Get factory
	IBeanFactory* myFactory = BeanFactoryManager::getInstance().getFactory(def->factoryName);
	if(!myFactory) {
		throw BeanFactoryException("Can't find factory "+def->factoryName);
	}

	//Create the object
	IObject* tmpInstance = myFactory->getInstance(def, this);

	//Save pointer to instance
	def->pointers.push_back(tmpInstance);

	return true;
}

boost::any BeanFactory::convertStringtoBoostAny(const BeanProperty& prop, const std::string& to) {
	//Convert map
	if(prop.isMap&&(to.substr(0, to.find_first_of('<'))=="vector" || to.substr(0, to.find_first_of('<'))=="std::vector")) {
		std::vector<std::pair<boost::any, boost::any> > tmpMapVec;
		std::vector<std::pair<std::string, std::string> >::const_iterator iter;

		size_t commaPos = 0;
		size_t findStart = to.find_first_of('<');
		findStart = to.find_first_of('<', findStart+1)+1;
		std::string keyType = to.substr(findStart, (commaPos=to.find_first_of(','))-findStart);
		std::string valueType = to.substr(commaPos+1, to.find_first_of('>')-commaPos-1);

		for(iter = prop.valueMap.begin(); iter != prop.valueMap.end(); ++iter) {
			BeanProperty tmpProp;
			tmpProp.isMap = false; tmpProp.isVector = false;
			tmpProp.value = iter->first;
			boost::any keyVar = convertStringtoBoostAny(tmpProp, trim(keyType));

			tmpProp.value = iter->second;
			boost::any valueVar = convertStringtoBoostAny(tmpProp, trim(valueType));

			tmpMapVec.push_back(std::pair<boost::any, boost::any>(keyVar, valueVar));
		}

		return boost::any(tmpMapVec);
	}
	else if(prop.isMap) {
		std::vector<std::pair<boost::any, boost::any> > tmpMapVec;
		std::vector<std::pair<std::string, std::string> >::const_iterator iter;

		size_t commaPos = 0;
		size_t findStart = to.find_first_of('<')+1;
		std::string keyType = to.substr(findStart, (commaPos=to.find_first_of(','))-findStart);
		std::string valueType = to.substr(commaPos+1, to.find_first_of('>')-commaPos-1);

		for(iter = prop.valueMap.begin(); iter != prop.valueMap.end(); ++iter) {
			BeanProperty tmpProp;
			tmpProp.isMap = false; tmpProp.isVector = false;
			tmpProp.value = iter->first;
			boost::any keyVar = convertStringtoBoostAny(tmpProp, trim(keyType));

			tmpProp.value = iter->second;
			boost::any valueVar = convertStringtoBoostAny(tmpProp, trim(valueType));

			tmpMapVec.push_back(std::pair<boost::any, boost::any>(keyVar, valueVar));
		}

		return boost::any(tmpMapVec);
	}

	//Convert vector
	if(prop.isVector) {
		std::vector<boost::any> tmpVector;

		size_t findStart = to.find_first_of('<')+1;
		std::string type = to.substr(findStart, to.find_last_of('>')-findStart);
		for(unsigned int i=0; i<prop.valueVector.size(); i++) {
			BeanProperty tmpProp;
			tmpProp.isMap = false; tmpProp.isVector = false;
			tmpProp.value = prop.valueVector[i];
			boost::any value = convertStringtoBoostAny(tmpProp, trim(type));
			tmpVector.push_back(value);
		}

		return boost::any(tmpVector);
	}

#define BASECONVERT(t) \
	if(#t == to) { \
		try { \
			return boost::lexical_cast<t>(prop.value); \
		} \
		catch(const boost::bad_lexical_cast& ex) { \
		} \
	}

	BASECONVERT(float)
	BASECONVERT(int)
	BASECONVERT(bool)
	BASECONVERT(double)
	BASECONVERT(long)
	BASECONVERT(short)
	BASECONVERT(char)
	BASECONVERT(unsigned long)
	BASECONVERT(unsigned int)
	BASECONVERT(unsigned short)
	BASECONVERT(unsigned char)
#undef BASECONVERT
	if(to=="const char*") {
		return boost::any(prop.value.c_str()); \
	}
	if(to=="std::string") {
		return boost::any(prop.value); \
	}
	if(to.substr(to.size()-1) == "*") {
		return boost::any((void*)getBean(prop.value));
	}

	std::cout << "Type not found: " << to << std::endl;
	throw BeanFactoryException("The type "+to+" has no converter.");

	return (void*)NULL;
}

std::string BeanFactory::trim(std::string str) {
	std::string::size_type pos = str.find_first_not_of(" \t\n\r");
	str = str.erase(0, pos);
	pos = str.find_last_not_of(" \t\n\r") + 1;
	str = str.erase(pos);

	return str;
}
