/*
 * BeanFactoryException.h
 *
 *  Created on: 11.06.2010
 *      Author: fkrauthan
 */

#ifndef BEANFACTORYEXCEPTION_H_
#define BEANFACTORYEXCEPTION_H_

#include <stdexcept>
#include <string>


class BeanFactoryException : public std::runtime_error {
	public:
		BeanFactoryException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif /* BEANFACTORYEXCEPTION_H_ */
