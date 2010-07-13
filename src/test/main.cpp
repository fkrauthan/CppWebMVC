/*
 * main.cpp
 *
 *  Created on: 13.07.2010
 *      Author: fkrauthan
 */

#include <webmvc/startup/startup.h>


int main(int argc, char **argv) {
	return startFramework("config/beans.xml", true, "config/web.xml");
}
