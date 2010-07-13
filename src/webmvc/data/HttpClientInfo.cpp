/*
 * HttpClientInfo.cpp
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#include "HttpClientInfo.h"


HttpClientInfo::HttpClientInfo(long ip, int port, const std::string& user) : mIp(ip), mPort(port), mUser(user) {
}

long HttpClientInfo::getIp() const {
	return mIp;
}

int HttpClientInfo::getPort() const {
	return mPort;
}

const std::string& HttpClientInfo::getUser() const {
	return mUser;
}
