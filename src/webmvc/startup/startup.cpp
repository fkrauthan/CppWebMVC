/*
 * startup.cpp
 *
 *  Created on: 13.07.2010
 *      Author: fkrauthan
 */

#include "startup.h"

#include <iostream>
#include <beans/BeanFactory.h>
#include <beans/BeanFactoryException.h>
#include "../core/standalone/Server.h"
#include "../core/application/Application.h"
#include "../core/IApplication.h"


bool startFramework(const std::string& beanConfig, bool runStandAlone, const std::string& webXMLConfig) {
	std::cout << "CppWebMVC start programm\n" << std::endl;

	BeanFactory factory;
	std::cout << "Read beans from xml..."; std::flush(std::cout);
	try {
		factory.loadFromXML(beanConfig);
	} catch(const BeanFactoryException& e) {
		std::cout << "error\nCan't load beans xml: " << e.what() << std::endl;
		return false;
	}
	std::cout << "success" << std::endl;


	//Create application instance
	IApplication* webApplication = factory.getBean<IApplication>("applicationContext");
	if(!webApplication) {
		std::cout << "Can't create webapplication instance. There is no bean \"applicationContext\" defined" << std::endl;
		return false;
	}
	webApplication->setBeanFactory(&factory);


	if(runStandAlone) {
		Server& server = Server::getInstance();
		server.readConfig(webXMLConfig);
		server.runServer(&factory);
	}

	return true;
}
