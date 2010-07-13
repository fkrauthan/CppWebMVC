
#include <webmvc/helper/PrimativeDatatypeConverter.h>

template<typename T> T HttpRequest::getHeader(const std::string& name) const {
	return PrimativeDatatypeConverter::fromString<T>(getHeader(name));
}

template<typename T> T HttpRequest::getAttribute(const std::string& name) const {
	return PrimativeDatatypeConverter::fromString<T>(getAttribute(name));
}
