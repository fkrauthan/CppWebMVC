/*
 * HttpClientInfo.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef HTTPCLIENTINFO_H_
#define HTTPCLIENTINFO_H_

#include <string>


class HttpClientInfo {
	public:
		HttpClientInfo(long ip, int port, const std::string& user);

		long getIp() const;
		int getPort() const;
		const std::string& getUser() const;

	private:
		long mIp;
		int mPort;
		std::string mUser;
};

#endif /* HTTPCLIENTINFO_H_ */
