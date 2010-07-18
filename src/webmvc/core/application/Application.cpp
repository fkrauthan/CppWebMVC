/*
 * Application.cpp
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#include "Application.h"
#include "../IUrlHandler.h"
#include "../../data/HttpSession.h"
#include <iostream>


Application::Application() {
	mBeanFactory = NULL;
	mThreadPool = NULL;
	mSessionManager = NULL;

	setThreadPoolSize(1);
}

Application::~Application() {
	delete mThreadPool;
}

void Application::setThreadPoolSize(int size) {
	delete mThreadPool;
	mThreadPool = new boost::threadpool::pool(size);
}

void Application::setBeanFactory(BeanFactory* beanFactory) {
	mBeanFactory = beanFactory;
}

void Application::setSessionManager(HttpSession* session) {
	mSessionManager = session;
}

BeanFactory* Application::getBeanFactory() {
	return mBeanFactory;
}

void Application::handleRequest(boost::function<void (HttpRequest*&, HttpResponse*&, void*)> convertData, void* data, boost::function<void (HttpRequest*, HttpResponse*)> requestFinish) {
	mThreadPool->schedule(boost::bind<void>(&Application::executeRequest, this, convertData, data, requestFinish));
}

void Application::executeRequest(boost::function<void (HttpRequest*&, HttpResponse*&, void*)> convertData, void* data, boost::function<void (HttpRequest*, HttpResponse*)> requestFinish) {
	//Create request
	HttpRequest* request = NULL;
	HttpResponse* response = NULL;
	convertData(request, response, data);
	if(request==NULL||response==NULL) {
		requestFinish(request, response);

		return;
	}
	setContextToRequest(request);
	if(mSessionManager) {
		setSession(request, mSessionManager->createSession(*request, *response));
	}


	IUrlHandler* urlHandler = getBeanFactory()->getBean<IUrlHandler>("urlHandler");
	if(!urlHandler) {
		std::cout << "No URL Handler found set error page: 500" << std::endl;
		requestFinish(request, response);

		return;
	}
	if(!urlHandler->dispatchUrl(*request, *response)) {
		std::cout << "URL handle error set error page: 500" << std::endl;
		requestFinish(request, response);

		return;
	}


	response->flush();
	requestFinish(request, response);
}
