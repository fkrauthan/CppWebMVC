
#include <webmvc/helper/PrimativeDatatypeConverter.h>


template<typename T> HttpCookie::HttpCookie(const std::string& name, const T& value, int maxAge, const std::string& path, const std::string& domain) 
	: mName(name),
	  mValue(PrimativeDatatypeConverter::toString(value)),
	  mPath(path),
	  mDomain(domain),
      mMaxAge(maxAge) {
}

template<typename T> T HttpCookie::getValue() const {
	return PrimativeDatatypeConverter::fromString<T>(getValue());
}

template<typename T> void HttpCookie::setValue(T value) {
	setValue(PrimativeDatatypeConverter::toString<T>(value));
}
