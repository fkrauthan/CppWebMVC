/*
 * RegisterConverter.h
 *
 *  Created on: 15.07.2010
 *      Author: fkrauthan
 */

#ifndef REGISTERCONVERTER_H_
#define REGISTERCONVERTER_H_

#include "Serializer.h"

#include "GenericDataConverter.h"
#include "StringDataConverter.h"


#define SERIALIZATION_REGISTER_START(id) struct SerializerRegister ## id { \
	SerializerRegister ## id() { \

#define SERIALIZATION_REGISTER_END(id) \
	} \
}; \
SerializerRegister ## id serializerRegister ## id ## Instance;


#define SERIALIZATION_GENERIC(type) Serializer::getInstance().registerDataConverter(new GenericDataConverter<type>());
#define SERIALIZATION_STRING() Serializer::getInstance().registerDataConverter(new StringDataConverter());

#endif /* REGISTERCONVERTER_H_ */
