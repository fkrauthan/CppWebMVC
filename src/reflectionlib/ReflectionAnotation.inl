
#include <sstream>

template<typename T> T ReflectionAnotation::getParam(const std::string& name, T defaultValue) {
	T ret;
	std::stringstream str;
	str << defaultValue;
	std::string tmpStr = getParam(name, str.str());
	str.str("");
	str << tmpStr;
	str >> ret;
	return ret;
}
