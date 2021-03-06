/*
 * HttpRequest.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include "HttpClientInfo.h"
#include "HttpCookie.h"
#include "HttpSession.h"
#include <string>
#include <vector>
#include <map>

class IApplication;
class IUrlHandler;
class HttpSession;


class HttpRequest {
	friend class IApplication;
	friend class IUrlHandler;

	public:
		HttpRequest(const std::vector<HttpCookie>& cookies, const std::map<std::string, std::string>& headerFields,
					const std::string& method, const HttpClientInfo& clientInfo, const std::map<std::string, std::string>& attributes,
					const std::string& uri, const std::string& query);

		HttpRequest(const HttpRequest& request);

		const HttpCookie& getCookie(const std::string& name) const;
		const std::vector<HttpCookie>& getCookies() const;
		bool containsCookie(const std::string& name) const;

		const std::string& getHeader(const std::string& name) const;
		template<typename T> T getHeader(const std::string& name) const;
		std::vector<std::string> getHeaderNames() const;
		const std::map<std::string, std::string>& getHeaders() const;
		bool containsHeader(const std::string& name) const;

		const std::string& getMethod() const;
		const HttpClientInfo& getClientInfo() const;

		const std::string& getAttribute(const std::string& name) const;
		template<typename T> T getAttribute(const std::string& name) const;
		std::vector<std::string> getAttributeNames() const;
		bool hasAttribute(const std::string& name) const;

		const std::string& getRequestURI() const;
		const std::string& getRequestQuery() const;

		IApplication* getApplicationContext() const;
		HttpSession& getSession() const;
		bool hasSession() const;

	protected:
		void setApplicationContext(IApplication* context);
		void setSession(HttpSession* session);
		void addAttribute(const std::string& name, const std::string& value);

	private:
		std::vector<HttpCookie> mCookies;
		std::map<std::string, std::string> mHeaderFields;

		std::string mMethod;
		HttpClientInfo mClientInfo;

		std::map<std::string, std::string> mAttributes;

		std::string mUri;
		std::string mQuery;

		IApplication* mApplication;
		HttpSession* mSession;
};


#include "HttpRequest.inl"

#endif /* HTTPREQUEST_H_ */
