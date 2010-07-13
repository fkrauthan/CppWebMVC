/*
 * Server.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <webserver/mongoose.h>
#include "../IApplication.h"
#include <boost/thread/condition_variable.hpp>
#include <string>


class Server {
	private:
		struct ServerSettings {
			std::string ports;
			std::string sslCert;
		};

	public:
		Server();
		~Server();

		void readConfig(const std::string& config);
		void runServer(BeanFactory* factory);

		void siteRequest(struct mg_connection* conn, const struct mg_request_info* request_info);
		void convertRequestData(HttpRequest*& request, HttpResponse*& response, void* data, struct mg_connection* conn);
		void requestFinish(HttpRequest* request, HttpResponse* response, struct mg_connection* conn, boost::condition_variable* cv, boost::mutex* mutex);

		void sendData(const std::string& content, struct mg_connection* conn);

	public:
		static Server& getInstance();

	private:
		struct mg_context* mCtx;

		ServerSettings mServerSettings;
		IApplication* mApplication;
};

#endif /* SERVER_H_ */
