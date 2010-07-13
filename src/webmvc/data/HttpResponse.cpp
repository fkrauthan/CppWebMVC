/*
 * HttpResponse.cpp
 *
 *  Created on: 24.06.2010
 *      Author: fkrauthan
 */

#include "HttpResponse.h"
#include "../exceptions/CookieNotFoundException.h"
#include "../exceptions/HeaderFieldNotFoundException.h"
#include "../exceptions/HeaderAlreadySendException.h"


HttpResponse::HttpResponse(boost::function<void (const std::string&)> sendData) :
	mSendData(sendData),
	mHeaderSend(false),
	mContentType("text/html"),
	mStatus(SC_OK) {
}

const HttpCookie& HttpResponse::getCookie(const std::string& name) const {
	for(unsigned int i=0; i<mCookies.size(); i++) {
		if(mCookies[i].getName() == name) {
			return mCookies[i];
		}
	}

	throw CookieNotFoundException("The cookie with name \""+name+"\" was not found");
}

const std::vector<HttpCookie>& HttpResponse::getCookies() const {
	return mCookies;
}

bool HttpResponse::containsCookie(const std::string& name) const {
	for(unsigned int i=0; i<mCookies.size(); i++) {
		if(mCookies[i].getName() == name) {
			return true;
		}
	}

	return false;
}

void HttpResponse::addCookie(const HttpCookie& cookie) {
	if(mHeaderSend) {
		throw HeaderAlreadySendException("Can't set cookie becouse header is already send");
	}

	removeCookie(cookie.getName());
	mCookies.push_back(cookie);
}

void HttpResponse::removeCookie(const std::string& name) {
	std::vector<HttpCookie>::iterator iter;
	for(iter=mCookies.begin(); iter!=mCookies.end(); ++iter) {
		if((*iter).getName() == name) {
			mCookies.erase(iter);
			return;
		}
	}
}

const std::string& HttpResponse::getHeader(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator iter = mHeaderFields.find(name);
	if(iter == mHeaderFields.end()) {
		throw HeaderFieldNotFoundException("The header field with name \""+name+"\" was not found");
	}

	return iter->second;
}

std::vector<std::string> HttpResponse::getHeaderNames() const {
	std::vector<std::string> tmpRet;
	std::map<std::string, std::string>::const_iterator iter;
	for(iter=mHeaderFields.begin(); iter!=mHeaderFields.end(); ++iter) {
		tmpRet.push_back(iter->first);
	}

	return tmpRet;
}

const std::map<std::string, std::string>& HttpResponse::getHeaders() const {
	return mHeaderFields;
}

bool HttpResponse::containsHeader(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator iter = mHeaderFields.find(name);
	if(iter == mHeaderFields.end()) {
		return false;
	}

	return true;
}

void HttpResponse::addHeader(const std::string& name, const std::string& value) {
	if(mHeaderSend) {
		throw HeaderAlreadySendException("Can't set header \""+name+"\" becouse header is already send");
	}

	mHeaderFields[name] = value;
}

void HttpResponse::removeHeader(const std::string& name) {
	std::map<std::string, std::string>::iterator iter = mHeaderFields.find(name);
	if(iter == mHeaderFields.end()) {
		return;
	}

	mHeaderFields.erase(iter);
}

HttpResponse::SC HttpResponse::getStatus() const {
	return mStatus;
}

void HttpResponse::setStatus(HttpResponse::SC status) {
	if(mHeaderSend) {
		throw HeaderAlreadySendException("Can't set status becouse header is already send");
	}

	mStatus = status;
}

void HttpResponse::sendRedirect(const std::string& newLocation, SC status) {
	if(mHeaderSend) {
		throw HeaderAlreadySendException("Can't set redirect to \""+newLocation+"\" becouse header is already send");
	}

	setStatus(status);
	addHeader("Location", newLocation);
}

const std::string& HttpResponse::getContentType() const {
	return mContentType;
}

void HttpResponse::setContentType(const std::string& contentType) {
	mContentType = contentType;
}

std::string HttpResponse::getContent() const {
	return mContent.str();
}

void HttpResponse::setContent(const std::string& content) {
	mContent.str(content);
}

void HttpResponse::flush() {
	if(!mHeaderSend) {
		mHeaderSend = true;

		sendStatusHeader();
		if(!containsHeader("Content-Type")) {
			mSendData("Content-Type: "+mContentType+"\r\n");
		}

		//Send rest of header fields
		std::map<std::string, std::string>::iterator iter;
		for(iter=mHeaderFields.begin(); iter!=mHeaderFields.end(); ++iter) {
			mSendData(iter->first+": "+iter->second+"\r\n");
		}

		//Send cookie settings
		for(unsigned int i=0; i<mCookies.size(); i++) {
			sendCookieHeader(mCookies[i]);
		}

		//Finish sending header
		mSendData("\r\n");
	}

	mSendData(mContent.str());
	setContent("");
}

void HttpResponse::sendStatusHeader() {
	mSendData("HTTP/1.1 ");

	switch(mStatus) {
		case SC_ACCEPTED: mSendData("202 Accepted\r\n"); break;
		case SC_BAD_GATEWAY: mSendData("502 Bad Gateway\r\n"); break;
		case SC_BAD_REQUEST: mSendData("400 Bad Request\r\n"); break;
		case SC_CONFLICT: mSendData("409 Conflict\r\n"); break;
		case SC_CONTINUE: mSendData("100 Continue\r\n"); break;
		case SC_CREATED: mSendData("201 Created\r\n"); break;
		case SC_EXPECTATION_FAILED: mSendData("417 Expectation Failed\r\n"); break;
		case SC_FORBIDDEN: mSendData("403 Forbidden\r\n"); break;
		case SC_FOUND: mSendData("302 Found\r\n"); break;
		case SC_GATEWAY_TIMEOUT: mSendData("504 Gateway Timeout\r\n"); break;
		case SC_GONE: mSendData("410 Gone\r\n"); break;
		case SC_HTTP_VERSION_NOT_SUPPORTED: mSendData("505 HTTP Version Not Supported\r\n"); break;
		case SC_INTERNAL_SERVER_ERROR: mSendData("500 Internal Server Error\r\n"); break;
		case SC_LENGTH_REQUIRED: mSendData("411 Length Required\r\n"); break;
		case SC_METHOD_NOT_ALLOWED: mSendData("405 Method Not Allowed\r\n"); break;
		case SC_MOVED_PERMANENTLY: mSendData("301 Moved Permanently\r\n"); break;
		//case SC_MOVED_TEMPORARILY: mSendData("202 Accepted\r\n"); break;
		case SC_MULTIPLE_CHOICES: mSendData("300 Multiple Choices\r\n"); break;
		case SC_NO_CONTENT: mSendData("204 No Content\r\n"); break;
		case SC_NON_AUTHORITATIVE_INFORMATION: mSendData("203 Non-Authoritative Information\r\n"); break;
		case SC_NOT_ACCEPTABLE: mSendData("406 Not Acceptable\r\n"); break;
		case SC_NOT_FOUND: mSendData("404 Not Found\r\n"); break;
		case SC_NOT_IMPLEMENTED: mSendData("501 Not Implemented\r\n"); break;
		case SC_NOT_MODIFIED: mSendData("304 Not Modified\r\n"); break;
		case SC_OK: mSendData("200 OK\r\n"); break;
		case SC_PARTIAL_CONTENT: mSendData("206 Partial Content\r\n"); break;
		case SC_PAYMENT_REQUIRED: mSendData("402 Payment Required\r\n"); break;
		case SC_PRECONDITION_FAILED: mSendData("412 Precondition Failed\r\n"); break;
		case SC_PROXY_AUTHENTICATION_REQUIRED: mSendData("407 Proxy Authentication Required\r\n"); break;
		case SC_REQUEST_ENTITY_TOO_LARGE: mSendData("413 Request Entity Too Large\r\n"); break;
		case SC_REQUEST_TIMEOUT: mSendData("408 Request Timeout\r\n"); break;
		case SC_REQUEST_URI_TOO_LONG: mSendData("414 Request-URI Too Long\r\n"); break;
		case SC_REQUESTED_RANGE_NOT_SATISFIABLE: mSendData("416 Requested Range Not Satisfiable\r\n"); break;
		case SC_RESET_CONTENT: mSendData("205 Reset Content\r\n"); break;
		case SC_SEE_OTHER: mSendData("303 See Other\r\n"); break;
		case SC_SERVICE_UNAVAILABLE: mSendData("503 Service Unavailable\r\n"); break;
		case SC_SWITCHING_PROTOCOLS: mSendData("101 Switching Protocols\r\n"); break;
		case SC_TEMPORARY_REDIRECT: mSendData("307 Temporary Redirect\r\n"); break;
		case SC_UNAUTHORIZED: mSendData("401 Unauthorized\r\n"); break;
		case SC_UNSUPPORTED_MEDIA_TYPE: mSendData("415 Unsupported Media Type\r\n"); break;
		case SC_USE_PROXY: mSendData("305 Use Proxy\r\n"); break;
		default:
			break;
	}
}

void HttpResponse::sendCookieHeader(const HttpCookie& cookie) {
	mSendData("Set-Cookie: "+cookie.getName()+"="+cookie.getValue());
	if(cookie.getMaxAge() > 0) {
		std::stringstream str;
		str << cookie.getMaxAge();
		mSendData("; Max-Age="+str.str());
	}

	if(cookie.getPath()!="") {
		mSendData("; Path="+cookie.getPath());
	}

	if(cookie.getDomain()!="") {
		mSendData("; Domain="+cookie.getDomain());
	}
	mSendData("; Version=1\r\n");
}
