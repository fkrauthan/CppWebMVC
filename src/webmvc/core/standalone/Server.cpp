/*
 * Server.cpp
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#include "Server.h"
#include <webmvc/exceptions/ConfigReadException.h>
#include <rapidxml/rapidxml.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#ifndef WIN32
#include <signal.h>
#include <sys/wait.h>
#endif

using namespace rapidxml;

static void* ServerSiteRequestHandler(enum mg_event event, struct mg_connection* conn, const struct mg_request_info* request_info);
static void ServerSignalhandler(int sig_num);


Server::Server() {
	mCtx = NULL;
}

Server::~Server() {
	if(mCtx) {
		mg_stop(mCtx);
		mCtx = NULL;
	}
}

void Server::readConfig(const std::string& config) {
	xml_document<> doc;

	std::ifstream ifs(config.c_str());
	if(!ifs.is_open()) {
		throw ConfigReadException("Can't open config file: "+config);
	}
	std::string xmlDoc((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	std::vector<char> xml_copy(xmlDoc.begin(),xmlDoc.end());
	xml_copy.push_back('\0');


	//Parsing the document
	doc.parse<0>(&xml_copy[0]);
	xml_node<>* web_node = doc.first_node("web");
	if(!web_node) {
		throw ConfigReadException("No web root tag found in config file: "+config);
	}


	//Read settings
	xml_node<>* settings_node = web_node->first_node("settings");
	if(!settings_node) {
		throw ConfigReadException("No settings tag found in config file: "+config);
	}

	xml_node<>* setting_node = settings_node->first_node("ports");
	if(!setting_node) {
		throw ConfigReadException("No ports tag found in config file: "+config);
	}
	mServerSettings.ports = setting_node->value();

	setting_node = settings_node->first_node("sslcert");
	if(setting_node) {
		mServerSettings.sslCert = setting_node->value();
	}
	else {
		mServerSettings.sslCert = "";
	}
}

void Server::runServer(BeanFactory* factory) {
	//Get application context
	mApplication = factory->getBean<IApplication>("applicationContext");

#ifndef WIN32
        signal(SIGPIPE, SIG_IGN);
        signal(SIGCHLD, &ServerSignalhandler);
#endif

	static const char* options[] = {
		"listening_ports", mServerSettings.ports.c_str(),
		NULL, NULL,
		NULL
	};
	if(!mServerSettings.sslCert.empty()) {
		options[1] = "ssl_certificate";
		options[2] = mServerSettings.sslCert.c_str();
	}
	mCtx = mg_start(&ServerSiteRequestHandler, options);

	std::cout << "Press ENTER to exit server!!!" << std::endl;
	(void)getchar();
	mg_stop(mCtx);
	mCtx = NULL;
}

void Server::siteRequest(struct mg_connection* conn, const struct mg_request_info* request_info) {
	boost::mutex mutex;
	boost::condition_variable cv;
	boost::mutex::scoped_lock lock(mutex);

	mApplication->handleRequest(boost::bind(&Server::convertRequestData, this, _1, _2, _3, conn), (void*)request_info, boost::bind(&Server::requestFinish, this, _1, _2, conn, &cv, &mutex));

	cv.wait(lock);
}

void Server::convertRequestData(HttpRequest*& request, HttpResponse*& response, void* data, struct mg_connection* conn) {
	mg_request_info* request_info = (mg_request_info*)data;


	//Create header Fields
	std::map<std::string, std::string> headerFields;
	for(int i=0; i<request_info->num_headers; i++) {
		headerFields[request_info->http_headers[i].name] = request_info->http_headers[i].value;
	}

	//Create user info
	std::string clientUser = "";
	if(request_info->remote_user) {
		clientUser = request_info->remote_user;
	}
	HttpClientInfo clientInfo(request_info->remote_ip, request_info->remote_port, clientUser);

	//Create attributes
	std::map<std::string, std::string> attributes;
	std::string query_string = "";
	if(request_info->query_string) {
		query_string = request_info->query_string;

		std::vector<std::string> tmpAttributes;
		boost::algorithm::split(tmpAttributes, request_info->query_string, boost::algorithm::is_any_of("&"));

		for(unsigned int i=0; i<tmpAttributes.size(); i++) {
			size_t delemiter = tmpAttributes[i].find_first_of('=');
			if(delemiter != std::string::npos) {
				attributes[tmpAttributes[i].substr(0, delemiter)] = tmpAttributes[i].substr(delemiter+1);
			}
			else {
				attributes[tmpAttributes[i]] = "";
			}
		}
	}

	//Create cookies
	std::vector<HttpCookie> cookies;
	std::map<std::string, std::string>::iterator iter = headerFields.find("Cookie");
	if(iter!=headerFields.end()) {
		std::vector<std::string> tmpCookies;
		boost::algorithm::split(tmpCookies, iter->second, boost::algorithm::is_any_of("; "));

		for(unsigned int i=0; i<tmpCookies.size(); i++) {
			size_t delemiter = tmpCookies[i].find_first_of('=');
			std::string cookieName = "";
			std::string cookieValue = "";
			if(delemiter != std::string::npos) {
				cookieName = tmpCookies[i].substr(0, delemiter);
				cookieValue = tmpCookies[i].substr(delemiter+1);
			}
			else {
				cookieName = tmpCookies[i];
			}
			cookies.push_back(HttpCookie(cookieName, cookieValue));
		}
	}

	//Create request
	request = new HttpRequest(cookies, headerFields, request_info->request_method, clientInfo, attributes, request_info->uri, query_string);

	//Create response
	response = new HttpResponse(boost::bind(&Server::sendData, this, _1, conn));
}

void Server::requestFinish(HttpRequest* request, HttpResponse* response, struct mg_connection* conn, boost::condition_variable* cv, boost::mutex* mutex) {
	if(request==NULL||response==NULL) {
		//Print 500 Error
		if(request->getRequestURI()=="/wait") {
			sleep(30);
		}
		sendData("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<html><head><title>Error: 500</title></head><body><h1>Error: 500</h1></body></html>", conn);

		delete request;
		delete response;

		boost::mutex::scoped_lock lock(*mutex);
		lock.unlock();
		cv->notify_one();
		return;
	}

	delete request;
	delete response;

	boost::mutex::scoped_lock lock(*mutex);
	lock.unlock();
	cv->notify_one();
}

void Server::sendData(const std::string& content, struct mg_connection* conn) {
	mg_write(conn, content.c_str(), content.size());
}

Server& Server::getInstance() {
	static Server instance;
	return instance;
}


static void* ServerSiteRequestHandler(enum mg_event event, struct mg_connection* conn, const struct mg_request_info* request_info) {
	if(event == MG_NEW_REQUEST) {
		Server::getInstance().siteRequest(conn, request_info);
	}
	else {
		return NULL;
	}

	return conn;
}

static void ServerSignalhandler(int sig_num) {
    switch (sig_num) {
#ifndef WIN32
    	case SIGCHLD:
            while(waitpid(-1, &sig_num, WNOHANG) > 0) ;
            break;
#endif
    	default:
            break;
    }
}
