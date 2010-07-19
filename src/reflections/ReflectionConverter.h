/*
 * ReflectionConverter.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONCONVERTER_H_
#define REFLECTIONCONVERTER_H_

#include "Reflection.h"
#include "ReflectionConvertException.h"
#include <string>
#include <vector>
#include <boost/any.hpp>
#include <cstring>


class ReflectionConverter {
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
				retValue.push_back(ReflectionConverter::convertPointer<T>(value[i]));
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

		template<typename M, typename T> static std::vector<std::pair<M, T> > convertVectorPair(const std::vector<std::pair<boost::any, boost::any> >& value) {
			std::vector<std::pair<M, T> > retValue;
			for(unsigned int i=0; i<value.size(); i++) {
				retValue.push_back(std::pair<M, T>(boost::any_cast<M>(value[i].first,  boost::any_cast<T>(value[i].second))));
			}
			return retValue;
		}

		template<typename M, typename T> static std::vector<std::pair<M, T> > convertVectorPairWithPointer(const std::vector<std::pair<boost::any, boost::any> >& value) {
			std::vector<std::pair<M, T> > retValue;
			for(unsigned int i=0; i<value.size(); i++) {
				retValue.push_back(std::pair<M, T>(boost::any_cast<M>(value[i].first), ReflectionMacroConverter::convertPointer<T>(value[i].second)));
			}
			return retValue;
		}

		template<typename T> static T convertPointer(const boost::any& value) {
			if(std::strcmp(value.type().name(), typeid(void*).name())==0) {
				return reinterpret_cast< T >(boost::any_cast< void* >(value));
			}
			else if(std::strcmp(value.type().name(), typeid(T).name())==0) {
				return boost::any_cast< T >(value);
			}
			else {
				throw ReflectionConvertException("Can't convert from type: "+std::string(value.type().name())+" to type "+std::string(typeid(T).name()));
			}
		}

		template<typename T> static T convertPointer(const T& value) {
			return value;
		}
};

#endif /* REFLECTIONCONVERTER_H_ */
