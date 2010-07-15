/*
 * ReflectionMacros.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONMACROS_H_
#define REFLECTIONMACROS_H_

#include "Reflection.h"
#include "ReflectionMacroConvertException.h"
#include <string>
#include <vector>
#include <boost/any.hpp>
#include <cstring>


class ReflectionMacroConverter {
	public:
		template<typename T> static std::vector<T> convertVector(const std::vector<boost::any>& value) {
			std::vector<T> retValue;
			for(unsigned int i=0; i<value.size(); i++) {
				retValue.push_back(boost::any_cast<T>(value[i]));
			}
			return retValue;
		}

		template<typename T> static std::vector<T> convertVectorWithPointer(const std::vector<boost::any>& value) {
			std::vector<T> retValue;
			for(unsigned int i=0; i<value.size(); i++) {
				retValue.push_back(ReflectionMacroConverter::convertPointer<T>(value[i]));
			}
			return retValue;
		}

		template<typename M, typename T> static std::map<M, T> convertMap(const std::vector<std::pair<boost::any, boost::any> >& value) {
			std::map<M, T> retValue;
			for(unsigned int i=0; i<value.size(); i++) {
				retValue[boost::any_cast<M>(value[i].first)] = boost::any_cast<T>(value[i].second);
			}
			return retValue;
		}

		template<typename M, typename T> static std::map<M, T> convertMapWithPointer(const std::vector<std::pair<boost::any, boost::any> >& value) {
			std::map<M, T> retValue;
			for(unsigned int i=0; i<value.size(); i++) {
				retValue[boost::any_cast<M>(value[i].first)] = ReflectionMacroConverter::convertPointer<T>(value[i].second);
			}
			return retValue;
		}

		template<typename T> static T convertPointer(const boost::any& value) {
			if(std::strcmp(value.type().name(), "Pv")==0) {
				return reinterpret_cast< T >(boost::any_cast< void* >(value));
			}
			else if(std::strcmp(value.type().name(), typeid(T).name())==0) {
				return boost::any_cast< T >(value);
			}
			else {
				throw ReflectionMacroConvertException("Can't convert from type: "+std::string(value.type().name())+" to type "+std::string(typeid(T).name()));
			}
		}
};


#define MAP(a, b) std::map<a,b>
#define PAIR(a, b) std::pair<a,b>
//-------------------------------------------------------------------------------------------------
#define BEGIN_CREATE_CONSTRUCTOR_CALL(className, functionCount) \
	void* className ## ConstructorCreateFunction ## functionCount(const std::vector<boost::any>& params) { \
		return (void*)new className(
//-------------------------------------------------------------------------------------------------
#define END_CREATE_CONSTRUCTOR_CALL() \
		); \
	}
//-------------------------------------------------------------------------------------------------
#define BEGIN_CREATE_FUNCTIONCALL_VOID(className, functionName, functionCount) \
	boost::any className ## CallFunction_ ## functionName ## functionCount(void* instance, const std::vector<boost::any>& params) { \
		((className*)instance)->functionName(
//-------------------------------------------------------------------------------------------------
#define BEGIN_CREATE_FUNCTIONCALL(className, functionName, functionCount) \
	boost::any className ## CallFunction_ ## functionName ## functionCount(void* instance, const std::vector<boost::any>& params) { \
		return boost::any(((className*)instance)->functionName(
//-------------------------------------------------------------------------------------------------
#define ADD_PARAMETER(type, index) boost::any_cast< type >(params[index])
//-------------------------------------------------------------------------------------------------
#define ADD_POINTER_PARAMETER(type, index) ReflectionMacroConverter::convertPointer< type >(params[index])
//-------------------------------------------------------------------------------------------------
#define ADD_VECTOR_PARAMETER(type, index) ReflectionMacroConverter::convertVector<type>(boost::any_cast<std::vector<boost::any> >(params[index]))
//-------------------------------------------------------------------------------------------------
#define ADD_VECTOR_POINTER_PARAMETER(type, index) ReflectionMacroConverter::convertVectorWithPointer<type>(boost::any_cast<std::vector<boost::any> >(params[index]))
//-------------------------------------------------------------------------------------------------
#define ADD_MAP_PARAMETER(keyType, valueType, index) ReflectionMacroConverter::convertMap<keyType, valueType>(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[index]))
//-------------------------------------------------------------------------------------------------
#define ADD_MAP_POINTER_PARAMETER(keyType, valueType, index) ReflectionMacroConverter::convertMapWithPointer<keyType, valueType>(boost::any_cast<std::vector<std::pair<boost::any, boost::any> > >(params[index]))
//-------------------------------------------------------------------------------------------------
#define END_CREATE_FUNCTIONCALL() )); \
		}
//-------------------------------------------------------------------------------------------------
#define END_CREATE_FUNCTIONCALL_VOID() ); \
			return boost::any(0); \
		}
//-------------------------------------------------------------------------------------------------
#define BEGIN_REGISTER_CLASS(className) \
	struct className ## _ReflectionStruct { \
		className ## _ReflectionStruct() { \
			const std::string sClassName = #className; \
			std::string tmpFunctionName; \
			std::vector<std::string> superClasses; \
			std::vector<ReflectionMember*> membersHolder; \
			std::vector<ReflectionCTor*> ctorsHolder; \
			std::vector<ReflectionParam*> paramsHolder; \
			std::vector<ReflectionFunction*> functionsHolder;
//-------------------------------------------------------------------------------------------------
#define REGISTER_INTERFACE(interfaceClass) \
			superClasses.push_back(#interfaceClass);
//-------------------------------------------------------------------------------------------------
#define START_REGISTER_CTOR() \
			paramsHolder.clear();
//-------------------------------------------------------------------------------------------------
#define END_REGISTER_CTOR(className, functionCount) \
			ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &className ## ConstructorCreateFunction ## functionCount));
//-------------------------------------------------------------------------------------------------
#define START_REGISTER_FUNCTION(functionName) \
			paramsHolder.clear(); \
			tmpFunctionName = #functionName;
//-------------------------------------------------------------------------------------------------
#define REGISTER_PARAM(type, paramName) \
			paramsHolder.push_back(new ReflectionParam(#paramName, typeid(type).name(), #type));
//-------------------------------------------------------------------------------------------------
#define END_REGISTER_FUNCTION(className, functionName, returnType, functionCount) \
			functionsHolder.push_back(new ReflectionFunction(tmpFunctionName, #returnType, paramsHolder, &className ## CallFunction_ ## functionName ## functionCount));
//-------------------------------------------------------------------------------------------------
#define REGISTER_MEMBER(type, memberName, offset) \
			membersHolder.push_back(new ReflectionMember(#memberName, typeid(type).name(), #type, offset));
//-------------------------------------------------------------------------------------------------
#define END_REGISTER_CLASS(className) \
			ReflectionClass* tmpClass = new ReflectionClass(sClassName, typeid(className).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS); \
			Reflection::getInstance().registerClass(tmpClass); \
		} \
	}; \
	className ## _ReflectionStruct refStruct ## className;
//-------------------------------------------------------------------------------------------------
#define END_REGISTER_STRUCT(className) \
			ReflectionClass* tmpClass = new ReflectionClass(sClassName, typeid(className).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::STRUCT); \
			Reflection::getInstance().registerClass(tmpClass); \
		} \
	}; \
	className ## _ReflectionStruct refStruct ## className;

#endif /* REFLECTIONMACROS_H_ */
