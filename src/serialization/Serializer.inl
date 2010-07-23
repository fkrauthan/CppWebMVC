
#include <typeinfo>
#include "../xml/rapidxml_print.hpp"
#include "SerializationXmlNodeNotFoundException.h"


template <typename T> SerializerDataConverter* Serializer::findConverter() {
	return findConverter(typeid(T).name());
}

template <typename T> std::string Serializer::serializeToText(const T& data) {
	return serializeToText(typeid(T).name(), (void*)&data);
}

template <typename T> T* Serializer::deserializeFromText(const std::string& input) {
	T* result = new T();
	deserializeFromText(input, *result);
	return result;
}

template <typename T> void Serializer::deserializeFromText(const std::string& input, T& output) {
	std::stringstream inputStream(input);
	deserializeFromText(inputStream, output);
}

template <typename T> void Serializer::deserializeFromText(std::stringstream& input, T& output) {
	deserializeFromText(input, typeid(T).name(), &output);
}

template <typename T> void Serializer::serializeToXML(const T& data, rapidxml::xml_node<>* root) {
	serializeToXML(typeid(T).name(), (void*)&data, root);
}

template <typename T> std::string Serializer::serializeToXML(const T& data, const std::string& name) {
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	rapidxml::xml_node<>* rootNode = doc.allocate_node(rapidxml::node_element, doc.allocate_string(name.c_str()));
	doc.append_node(rootNode);
	
	serializeToXML(data, rootNode);

	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	return xml_as_string;
}

template <typename T> T* Serializer::deserializeFromXML(const std::string& input, const std::string& name) {
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_non_destructive>(const_cast<char*>(input.c_str()));

	rapidxml::xml_node<>* rootNode = doc.first_node(name.c_str());
	if(!rootNode) {
		throw SerializationXmlNodeNotFoundException("The document root node \""+name+"\" was not found!");
	}
	
	T* result = new T();
	deserializeFromXML(rootNode, *result);
	return result;
}

template <typename T> void Serializer::deserializeFromXML(rapidxml::xml_node<>* root, T& output) {
	deserializeFromXML(typeid(T).name(), root, &output);
}
	