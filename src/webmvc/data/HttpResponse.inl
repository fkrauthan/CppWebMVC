
#include <webmvc/helper/PrimativeDatatypeConverter.h>

template<typename T> T HttpResponse::getHeader(const std::string& name) {
	return PrimativeDatatypeConverter::fromString<T>(getHeader(name));
}

template<typename T> void HttpResponse::addHeader(const std::string& name, const T& value) {
	addHeader(name, PrimativeDatatypeConverter::toString(value));
}

template<typename T> HttpResponse& HttpResponse::operator<<(const T& var) {
	mContent << var;
	return *this;
}
