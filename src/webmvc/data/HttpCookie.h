/*
 * HttpCookie.h
 *
 *  Created on: 17.06.2010
 *      Author: fkrauthan
 */

#ifndef HTTPCOOKIE_H_
#define HTTPCOOKIE_H_

#include <string>


class HttpCookie {
	public:
		HttpCookie(const std::string& name, const std::string& value = "", int maxAge=0, const std::string& path = "", const std::string& domain = "");
		template<typename T> HttpCookie(const std::string& name, const T& value, int maxAge=0, const std::string& path = "", const std::string& domain = "");


		const std::string& getDomain() const;
		const std::string& getName() const;
		const std::string& getPath() const;

		int getMaxAge() const;

		const std::string& getValue() const;
		template<typename T> T getValue() const;


		void setDomain(const std::string& domain);
		void setName(const std::string& name);
		void setPath(const std::string& path);

		void setValue(const std::string& value);
		template<typename T> void setValue(T value);

		void setMaxAge(int expiry);

	private:
		std::string mName;
		std::string mValue;
		std::string mPath;
		std::string mDomain;
		int mMaxAge;
};


#include "HttpCookie.inl"

#endif /* HTTPCOOKIE_H_ */
