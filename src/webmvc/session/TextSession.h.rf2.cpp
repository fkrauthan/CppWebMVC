/*
 * Reflection registration for header: TextSession.h
 *
 *   Created on: 20.07.2010
 *       Author: CodeGenerator V1.0
 */

#include "TextSession.h"
#include <reflections/Reflection.h>
#include <reflections/ReflectionConverter.h>
#include <stddef.h>
#include <boost/any.hpp>


void* TextSessionConstructorCreateFunction0(const std::vector<boost::any>& params) {
	return (void*)new TextSession();
}

boost::any TextSessionCallFunction_startNewSession2(void* instance, const std::vector<boost::any>& params) {
	((TextSession*)instance)->startNewSession();
	return boost::any(0);
}



struct TextSession_ReflectionStruct {
	TextSession_ReflectionStruct() {
		std::vector<std::string> superClasses;
		std::vector<ReflectionMember*> membersHolder;
		std::vector<ReflectionCTor*> ctorsHolder;
		std::vector<ReflectionParam*> paramsHolder;
		std::vector<ReflectionFunction*> functionsHolder;

		superClasses.push_back("HttpSession");

		paramsHolder.clear();
		ctorsHolder.push_back(new ReflectionCTor(paramsHolder, &TextSessionConstructorCreateFunction0));

		ReflectionClass* tmpClass = new ReflectionClass("TextSession", typeid(TextSession).name(), superClasses, ctorsHolder, functionsHolder, membersHolder, ReflectionClass::CLASS);
		Reflection::getInstance().registerClass(tmpClass);
	}
};
TextSession_ReflectionStruct refStructTextSession;

