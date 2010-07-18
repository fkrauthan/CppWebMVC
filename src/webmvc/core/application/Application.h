/*
 * Application.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "../IApplication.h"
#include <boost/threadpool.hpp>


class Application : public IApplication {
	public:
		Application();
		~Application();


		BeanFactory* getBeanFactory();
		void setBeanFactory(BeanFactory* beanFactory);

		void setThreadPoolSize(int size);
		void setSessionManager(HttpSession* session);

		void handleRequest(boost::function<void (HttpRequest*&, HttpResponse*&, void*)> convertData, void* data, boost::function<void (HttpRequest*, HttpResponse*)> requestFinish);

	private:
		void executeRequest(boost::function<void (HttpRequest*&, HttpResponse*&, void*)> convertData, void* data, boost::function<void (HttpRequest*, HttpResponse*)> requestFinish);

	private:
		BeanFactory* mBeanFactory;
		HttpSession* mSessionManager;

		boost::threadpool::pool* mThreadPool;
};

#endif /* APPLICATION_H_ */
