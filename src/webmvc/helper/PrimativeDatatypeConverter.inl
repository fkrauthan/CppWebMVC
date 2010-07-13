
#include <boost/lexical_cast.hpp>

template<typename T> inline T PrimativeDatatypeConverter::fromString(const std::string& value) {
	return boost::lexical_cast<T>(value);
}

template<typename T> inline std::string PrimativeDatatypeConverter::toString(const T& value) {
	return boost::lexical_cast<std::string>(value);
}

/*#define BASECONVERT(t) \
	template<> inline t PrimativeDatatypeConverter::fromString(const std::string& value) { \
		int myVar; \
    	std::stringstream str; \
    	str << value; \
    	str >> myVar; \
    	return myVar; \
	} \
	template<> inline std::string PrimativeDatatypeConverter::toString(t value) { \
		std::stringstream str; \
		str << value; \
		return str.str(); \
	}

    BASECONVERT(float)
    BASECONVERT(int)
    BASECONVERT(bool)
    BASECONVERT(double)
    BASECONVERT(long)
    BASECONVERT(short)
    BASECONVERT(char)
    BASECONVERT(unsigned long)
    BASECONVERT(unsigned int)
    BASECONVERT(unsigned short)
    BASECONVERT(unsigned char)
#undef BASECONVERT
    
template<> inline const char* PrimativeDatatypeConverter::fromString(const std::string& value) {
    return value.c_str();
}

template<> inline std::string PrimativeDatatypeConverter::fromString(const std::string& value) {
    return value;
}

template<> inline std::string PrimativeDatatypeConverter::toString(const char* value) {
    return value;
}

template<> inline std::string PrimativeDatatypeConverter::toString(const std::string& value) {
    return value;
}*/
