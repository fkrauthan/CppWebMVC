/*
 * HttpResponse.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include "HttpCookie.h"
#include <boost/function.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <map>


class HttpResponse {
	public:
		enum SC {
			SC_ACCEPTED = 202,
			SC_BAD_GATEWAY = 502,
			SC_BAD_REQUEST = 400,
			SC_CONFLICT = 409,
			SC_CONTINUE = 100,
			SC_CREATED = 201,
			SC_EXPECTATION_FAILED = 417,
			SC_FORBIDDEN = 403,
			SC_FOUND = 302,
			SC_GATEWAY_TIMEOUT = 504,
			SC_GONE = 410,
			SC_HTTP_VERSION_NOT_SUPPORTED = 505,
			SC_INTERNAL_SERVER_ERROR = 500,
			SC_LENGTH_REQUIRED = 411,
			SC_METHOD_NOT_ALLOWED = 405,
			SC_MOVED_PERMANENTLY = 301,
			//SC_MOVED_TEMPORARILY = 302,
			SC_MULTIPLE_CHOICES = 300,
			SC_NO_CONTENT = 204,
			SC_NON_AUTHORITATIVE_INFORMATION = 203,
			SC_NOT_ACCEPTABLE = 406,
			SC_NOT_FOUND = 404,
			SC_NOT_IMPLEMENTED = 501,
			SC_NOT_MODIFIED = 304,
			SC_OK = 200,
			SC_PARTIAL_CONTENT = 206,
			SC_PAYMENT_REQUIRED = 402,
			SC_PRECONDITION_FAILED = 412,
			SC_PROXY_AUTHENTICATION_REQUIRED = 407,
			SC_REQUEST_ENTITY_TOO_LARGE = 413,
			SC_REQUEST_TIMEOUT = 408,
			SC_REQUEST_URI_TOO_LONG = 414,
			SC_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
			SC_RESET_CONTENT = 205,
			SC_SEE_OTHER = 303,
			SC_SERVICE_UNAVAILABLE = 503,
			SC_SWITCHING_PROTOCOLS = 101,
			SC_TEMPORARY_REDIRECT = 307,
			SC_UNAUTHORIZED = 401,
			SC_UNSUPPORTED_MEDIA_TYPE = 415,
			SC_USE_PROXY = 305,
		};

	public:
		HttpResponse(boost::function<void (const std::string&)> sendData);
		HttpResponse(const HttpResponse& response);

		const HttpCookie& getCookie(const std::string& name) const;
		const std::vector<HttpCookie>& getCookies() const;
		bool containsCookie(const std::string& name) const;

		void addCookie(const HttpCookie& cookie);
		void removeCookie(const std::string& name);

		const std::string& getHeader(const std::string& name) const;
		template<typename T> T getHeader(const std::string& name);
		std::vector<std::string> getHeaderNames() const;
		const std::map<std::string, std::string>& getHeaders() const;
		bool containsHeader(const std::string& name) const;

		void addHeader(const std::string& name, const std::string& value);
		template<typename T> void addHeader(const std::string& name, const T& value);
		void removeHeader(const std::string& name);

		SC getStatus() const;
		void setStatus(SC status);

		void sendRedirect(const std::string& newLocation, SC status=SC_MOVED_PERMANENTLY);

		const std::string& getContentType() const;
		void setContentType(const std::string& contentType);

		std::string getContent() const;
		void setContent(const std::string& content);

		void flush();
		template<typename T> HttpResponse& operator<<(const T& var); /* { stringstreamblabla; return r; }*/

	private:
		void sendStatusHeader();
		void sendCookieHeader(const HttpCookie& cookie);

	private:
		boost::function<void (const std::string&)> mSendData;

		bool mHeaderSend;
		std::vector<HttpCookie> mCookies;
		std::map<std::string, std::string> mHeaderFields;

		std::string mContentType;

		SC mStatus;

		std::stringstream mContent;
};


#include "HttpResponse.inl"

#endif /* HTTPRESPONSE_H_ */
