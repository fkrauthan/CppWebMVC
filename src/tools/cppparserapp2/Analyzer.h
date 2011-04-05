#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace AnalyzerNS
{
	//@ FancyShit
	//@ FancyShit2(Name="   Test-\"Name\"", Bar=    test   , Foo="bla")
	struct Annotation
	{
		std::string mName;
		std::map<std::string, std::string> mParameters;
	};

	struct Qualifier
	{
		enum Enumeration
		{
			Private,
			Protected,
			Public,
			Virtual
		};
	};

	struct ObjectType
	{
		enum Enumeration
		{
			Namespace,
			Class,
			Struct,
			Enum
		};
	};

	struct TypeInfo
	{
		std::string mTypeName;
		std::vector<TypeInfo> mTemplateParameter;
		bool mIsPointer;
		bool mIsConst;
		bool mIsReference;
		bool mIsStatic;
	};

	struct InheritanceData
	{
		Qualifier::Enumeration mQualifier;
		TypeInfo mType;
	};

	struct FieldInfo
	{
		std::string mName;
		Qualifier::Enumeration mQualifier;
		TypeInfo mType;
		std::vector<Annotation> mAnnotations;
	};

	struct MethodInfo
	{
		Qualifier::Enumeration mQualifier;
		bool mIsClassConstructor;
		bool mIsClassDestructor;
		bool mIsVirtual;
		bool mIsAbstract;
		bool mIsConst;

		std::string mName;
		TypeInfo mType;
		std::vector<FieldInfo> mParameters;
		std::vector<Annotation> mAnnotations;
	};

	struct ObjectData
	{
		Qualifier::Enumeration mQualifier;
		ObjectType::Enumeration mObjectType;
		std::string mName;
		std::vector<InheritanceData> mBaseClasses;

		std::vector<MethodInfo> mMethods;
		std::vector<FieldInfo> mFields;

		std::vector<ObjectData> mChildObjects;
		std::vector<Annotation> mAnnotations;
	};

	class Analyzer
	{
	public:
		Analyzer();
		virtual ~Analyzer();

		virtual void Analyze(const std::string& filePath);
		std::vector<ObjectData> MainObjects;

	protected:
		std::string ReadContentFromFile(const std::string& filePath);
		std::string RemoveComments(const std::string& input);

		std::string ExtractData(const std::string& input, std::string::size_type pos, const std::vector<std::string>& delimters, std::string::size_type& outPos);
		std::string ExtractDataReverse(const std::string& input, std::string::size_type pos, const std::vector<std::string>& delimters, std::string::size_type& outPos);
		int FindFirstOf(const std::string& input, std::string::size_type pos, const std::vector<std::string>& words, std::string::size_type& outPos);
		std::vector<InheritanceData> ExtractInheritanceData(const std::string& input);
		std::string ReadBlockContent(const std::string& input, std::string::size_type pos, std::string::size_type& endPos);

		std::string::size_type ParseObjects(const std::string& input, ObjectData* parent, Qualifier::Enumeration parentQualifier, std::string::size_type pos);
		std::vector<std::string> ParseSymbols(const std::string& input);
		TypeInfo ParseTypeInfo(const std::string& input);
		FieldInfo ParseField(const std::string& input, Qualifier::Enumeration qualifier);
		MethodInfo ParseMethod(const std::string& input, Qualifier::Enumeration qualifier);
		Annotation ParseAnnotation(const std::string& input);

		bool IsAnnotation(const std::string& input);

	private:
		std::vector<Annotation> currentAnnotationsForNext;

	private:
		void split(const std::string& string, const char delemiter, std::vector<std::string>& destination, bool removeEmpty)
		{
			std::string::size_type  last_position(0);
			std::string::size_type position(0);
			for (std::string::const_iterator it(string.begin()); it != string.end(); ++it, ++position)
			{
				if (*it == delemiter)
				{
					std::string trimmed = trim(string.substr(last_position, position - last_position));
					if (trimmed == "" && removeEmpty)
						continue;
					destination.push_back(trimmed);
					last_position = position + 1;
				}
			}
			std::string trimmed = trim(string.substr(last_position, position - last_position));
			if (trimmed == "" && removeEmpty)
				return;
			destination.push_back(trimmed);
		}

		std::string trim(std::string str)
		{
			std::string::size_type pos = str.find_first_not_of(" \t\n\r");
			str = str.erase(0, pos);
			pos = str.find_last_not_of(" \t\n\r") + 1;
			str = str.erase(pos);
			return str;
		}

		std::string& replaceAll(std::string& context, const std::string& from, const std::string& to)
		{
			size_t lookHere = 0;
			size_t foundHere;
			while((foundHere = context.find(from, lookHere)) != std::string::npos)
			{
				context.replace(foundHere, from.size(), to);
				lookHere = foundHere + to.size();
			}
			return context;
		}
	};
}
