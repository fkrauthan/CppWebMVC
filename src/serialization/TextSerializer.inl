
#include <typeinfo>


template <typename T> TextSerializerDataConverter* TextSerializer::findConverter() {
	return findConverter(typeid(T).name());
}

/*template <typename T> bool TextSerializer::canSerialize(const T& data) {
	ReflectionData* reflectionData = Reflection::getInstance().FindReflection<T>();
	if(reflectionData != NULL) {
		return true;
	}

	TextSerializerDataConverter* converter = TextSerializer::getInstance().findConverter<T>();
	if(converter != NULL) {
		return true;
	}
	
	return false;
}*/

template <typename T> std::string TextSerializer::serialize(const T& data) {
	return serialize(typeid(T).name(), typeid(T).name(), (void*)&data);
}

template <typename T> T* TextSerializer::deserialize(const std::string& input) {
	T* result = new T();
	deserialize(input, *result);
	return result;
}

template <typename T> void TextSerializer::deserialize(const std::string& input, T& output) {
	std::stringstream inputStream(input);
	deserialize(inputStream, output);
}

template <typename T> void TextSerializer::deserialize(std::stringstream& input, T& output) {
	deserialize(input, typeid(T).name(), &output);
}