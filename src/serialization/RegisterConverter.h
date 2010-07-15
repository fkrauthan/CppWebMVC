/*
 * RegisterConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef REGISTERCONVERTER_H_
#define REGISTERCONVERTER_H_

#include "TextSerializer.h"

#include "GenericDataConverter.h"
#include "MapDataConverter.h"
#include "PairDataConverter.h"
#include "VectorDataConverter.h"
#include "StringDataConverter.h"


#define SERIALIZATION_REGISTER_START(id) struct SerializerRegister ## id { \
	SerializerRegister ## id() { \

#define SERIALIZATION_REGISTER_END(id) \
	} \
}; \
SerializerRegister ## id serializerRegister ## id ## Instance;


#define SERIALIZATION_PAIR_STRING(keyType, valueType) std::pair<keyType, valueType>
#define SERIALIZATION_MAP_STRING(keyType, valueType) std::map<keyType, valueType>


#define SERIALIZATION_GENERIC(type) TextSerializer::getInstance().registerDataConverter(new GenericDataConverter<type>());
#define SERIALIZATION_STRING() TextSerializer::getInstance().registerDataConverter(new StringDataConverter());
#define SERIALIZATION_VECTOR(type) TextSerializer::getInstance().registerDataConverter(new VectorDataConverter<type>());

#define SERIALIZATION_PAIR(type) TextSerializer::getInstance().registerDataConverter(new PairDataConverter<type, type>());
#define SERIALIZATION_PAIR_TWICE(keyType, valueType) \
		TextSerializer::getInstance().registerDataConverter(new PairDataConverter<keyType, valueType>()); \
		TextSerializer::getInstance().registerDataConverter(new PairDataConverter<valueType, keyType>());

#define SERIALIZATION_MAP(type) TextSerializer::getInstance().registerDataConverter(new MapDataConverter<type, type>());
#define SERIALIZATION_MAP_TWICE(keyType, valueType) \
		TextSerializer::getInstance().registerDataConverter(new MapDataConverter<keyType, valueType>()); \
		TextSerializer::getInstance().registerDataConverter(new MapDataConverter<valueType, keyType>());

#endif /* REGISTERCONVERTER_H_ */
