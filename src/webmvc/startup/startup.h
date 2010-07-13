/*
 * startup.h
 *
 *  Created on: 13.07.2010
 *      Author: fkrauthan
 */

#ifndef STARTUP_H_
#define STARTUP_H_

#include <string>


bool startFramework(const std::string& beanConfig = std::string("beans.xml"), bool runStandAlone = false, const std::string& webXMLConfig = std::string("web.xml"));

#endif /* STARTUP_H_ */
