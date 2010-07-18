/*
 * IApplication.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef IAPPLICATION_H_
#define IAPPLICATION_H_

#include <webmvc/data/HttpRequest.h>
#include <webmvc/data/HttpResponse.h>
#include <beans/BeanFactory.h>
#include <boost/function.hpp>


class IApplication : public IObject {
	public:
		virtual ~IApplication() {};

		virtual BeanFactory* getBeanFactory() = 0;
		virtual void setBeanFactory(BeanFactory* beanFactory) = 0;

		virtual void setThreadPoolSize(int size) = 0;
		virtual void handleRequest(boost::function<void (HttpRequest*&, HttpResponse*&, void*)> convertData, void* data, boost::function<void (HttpRequest*, HttpResponse*)> requestFinish) = 0;

	protected:
		void setContextToRequest(HttpRequest* request) {
			request->setApplicationContext(this);
		}
		void setSession(HttpRequest* request, HttpSession* session) {
			request->setSession(session);
		}
};

#endif /* IAPPLICATION_H_ */
