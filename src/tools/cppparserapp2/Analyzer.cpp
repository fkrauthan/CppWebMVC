#include "Analyzer.h"

#include <iostream>
#include <fstream>

namespace AnalyzerNS
{
	Analyzer::Analyzer()
	{
	}


	Analyzer::~Analyzer()
	{
	}


	void Analyzer::Analyze(const std::string& filePath)
	{
		MainObjects.clear();
		currentAnnotationsForNext.clear();

		std::string buffer = ReadContentFromFile(filePath);
		buffer = RemoveComments(buffer);

		std::string::size_type pos = 0;
		while (std::string::npos != (pos = ParseObjects(buffer, NULL, Qualifier::Public, pos)));
	}


	std::string Analyzer::ReadContentFromFile(const std::string& filePath)
	{
		std::stringstream stream;
		std::ifstream readFile;
		readFile.open(filePath.c_str());
		if (readFile.is_open())
		{
			char s[1024];
			while(readFile.getline(s, 1024))
			{
				stream << s << std::endl;
			}
		}
		readFile.close();

		return stream.str();
	}


	std::string Analyzer::RemoveComments(const std::string& input)
	{
		std::string buffer = input;

		std::string::size_type pos = 0;
		while (true)
		{
			// Single comments
			{
				std::string::size_type start = buffer.find("//", pos);
				if (start != std::string::npos)
				{
					std::string::size_type end = buffer.find("\n", start);
					if (end == std::string::npos)
						end = buffer.size();

					if (IsAnnotation(buffer.substr(start, end - start)))
					{
						pos = end;
						continue;
					}
					buffer.erase(start, end - start);
					continue;
				}
			}

			/* Block comments */
			{
				std::string::size_type start = buffer.find("/*", pos);
				if (start != std::string::npos)
				{
					std::string::size_type end = buffer.find("*/", start);
					if (end == std::string::npos)
						end = buffer.size();
					buffer.erase(start, (end+2) - start);
					continue;
				}
			}
			break;
		}

		return buffer;
	}

	std::string Analyzer::ExtractData(const std::string& input, std::string::size_type pos, const std::vector<std::string>& delimters, std::string::size_type& outPos)
	{
		std::string::size_type lastPos = std::string::npos;
		std::string::size_type tmpOutPos = pos;
		for (unsigned int i = 0; i < delimters.size(); ++i)
		{
			std::string::size_type newPos = input.find(delimters[i], pos);
			if (newPos != std::string::npos)
			{
				if (lastPos == std::string::npos)
				{
					lastPos = newPos;
					tmpOutPos = lastPos + delimters[i].size();
				}
				else if (lastPos > newPos)
				{
					lastPos = newPos;
					tmpOutPos = lastPos + delimters[i].size();
				}
			}
		}

		if (lastPos == std::string::npos)
			return "";

		outPos = tmpOutPos;
		return input.substr(pos, lastPos - pos);
	}

	std::string Analyzer::ExtractDataReverse(const std::string& input, std::string::size_type pos, const std::vector<std::string>& delimters, std::string::size_type& outPos)
	{
		std::string::size_type lastPos = std::string::npos;
		std::string::size_type tmpOutPos = pos;
		for (unsigned int i = 0; i < delimters.size(); ++i)
		{
			std::string::size_type newPos = input.rfind(delimters[i], pos);
			if (newPos != std::string::npos)
			{
				if (lastPos == std::string::npos)
				{
					lastPos = newPos;
					tmpOutPos = lastPos + delimters[i].size();
				}
				else if (lastPos < newPos)
				{
					lastPos = newPos;
					tmpOutPos = lastPos + delimters[i].size();
				}
			}
		}

		if (lastPos == std::string::npos)
		{
			outPos = input.size();
			return input;
		}

		outPos = tmpOutPos;
		return input.substr(0, outPos);
	}


	int Analyzer::FindFirstOf(const std::string& input, std::string::size_type pos, const std::vector<std::string>& words, std::string::size_type& outPos)
	{
		int index = -1;

		std::string::size_type lastPos = std::string::npos;
		for (unsigned int i = 0; i < words.size(); ++i)
		{
			std::string::size_type newPos = input.find(words[i], pos);
			if (newPos != std::string::npos)
			{
				if (lastPos == std::string::npos)
				{
					lastPos = newPos;
					index = i;
				}
				else if (lastPos > newPos)
				{
					lastPos = newPos;
					index = i;
				}
			}
		}

		if (index != -1)
			lastPos += words[index].size();
		outPos = lastPos;
		return index;
	}


	std::vector<InheritanceData> Analyzer::ExtractInheritanceData(const std::string& input)
	{
		std::vector<InheritanceData> result;

		std::vector<std::string> tokens = ParseSymbols(input);
		for (unsigned int i = 0; i < tokens.size(); ++i)
		{
			InheritanceData inheritanceData;

			std::vector<std::string> qualifierDelimiters;
			qualifierDelimiters.push_back("private ");
			qualifierDelimiters.push_back("protected ");
			qualifierDelimiters.push_back("public ");
			qualifierDelimiters.push_back("virtual ");

			std::string::size_type pos;
			int index = FindFirstOf(tokens[i], 0, qualifierDelimiters, pos);
			if (index == -1)
			{
				index = 0;
				pos = 0;
			}
			std::string qualifier = trim(qualifierDelimiters[index]);
			if (qualifier == "private")
				inheritanceData.mQualifier = Qualifier::Private;
			else if (qualifier == "protected")
				inheritanceData.mQualifier = Qualifier::Protected;
			else if (qualifier == "public")
				inheritanceData.mQualifier = Qualifier::Public;
			else if (qualifier == "virtual")
				inheritanceData.mQualifier = Qualifier::Virtual;


			inheritanceData.mType = ParseTypeInfo(tokens[i].substr(pos));

			result.push_back(inheritanceData);
		}

		return result;
	}


	std::string Analyzer::ReadBlockContent(const std::string& input, std::string::size_type pos, std::string::size_type& endPos)
	{
		std::stringstream stream;

		int openBrackets = 0;
		endPos = pos;
		for (std::string::const_iterator it(input.begin() + pos); it != input.end(); ++it, ++endPos)
		{
			if (*it == '{')
				openBrackets++;
			else if (*it == '}')
				openBrackets--;

			stream << *it;

			if (openBrackets == 0)
				break;
		}

		return stream.str();
	}


	std::string::size_type Analyzer::ParseObjects(const std::string& input, ObjectData* parent, Qualifier::Enumeration parentQualifier, std::string::size_type pos)
	{
		//FIXME: mAnnotations is the first time empty becouse there is a missing parseAnnotation!!!
		ObjectData newClass;
		newClass.mQualifier = parentQualifier;
		newClass.mAnnotations = currentAnnotationsForNext;
		currentAnnotationsForNext.clear();

		// get type
		std::vector<std::string> typeDelimiters;
		typeDelimiters.push_back("class ");
		typeDelimiters.push_back("struct ");
		typeDelimiters.push_back("enum ");
		typeDelimiters.push_back("namespace ");
		int typeIndex = FindFirstOf(input, pos, typeDelimiters, pos);
		switch (typeIndex)
		{
			case 0: newClass.mObjectType = ObjectType::Class;
				break;
			case 1: newClass.mObjectType = ObjectType::Struct;
				break;
			case 2: newClass.mObjectType = ObjectType::Enum;
				break;
			case 3: newClass.mObjectType = ObjectType::Namespace;
				break;
		}

		// check if this is an forward declaration
		std::vector<std::string> classDelimiters;
		classDelimiters.push_back(";");
		classDelimiters.push_back("{");

		std::string::size_type endPos = pos + 1;
		if (FindFirstOf(input, pos, classDelimiters, endPos) != 1)
		{
			// no class declaration, maybe forward declaration so we ignore that here
			return endPos;
		}

		// get name of class
		std::vector<std::string> endClassNameDelimiters;
		endClassNameDelimiters.push_back("\n");
		endClassNameDelimiters.push_back(" ");
		endClassNameDelimiters.push_back("\t");
		endClassNameDelimiters.push_back(":");
		endClassNameDelimiters.push_back("{");

		newClass.mName = ExtractData(input, pos, endClassNameDelimiters, pos);

		// get inheritance
		std::vector<std::string> inheritanceDelimiters;
		inheritanceDelimiters.push_back(":");
		inheritanceDelimiters.push_back("{");

		endPos = pos + 1;
		if (FindFirstOf(input, pos, inheritanceDelimiters, endPos) == 0)
		{
			std::vector<std::string> inheritanceEndDelimiters;
			inheritanceEndDelimiters.push_back("{");

			// read inheritance
			std::string inheritanceList = ExtractData(input, endPos, inheritanceEndDelimiters, pos);
			newClass.mBaseClasses = ExtractInheritanceData(inheritanceList);
		}
		else
			pos = endPos;

		// read content
		std::stringstream current;
		Qualifier::Enumeration currentQualifier = Qualifier::Public;
		if (newClass.mObjectType == ObjectType::Class)
			currentQualifier = Qualifier::Private;

		for (std::string::size_type i = pos; i < input.size();)
		{
			if (input[i] == '/' && input[i + 1] == '/')
			{
				std::string::size_type endAnnotationPos = input.find("\n", i);
				if (endAnnotationPos == std::string::npos)
					endAnnotationPos = input.size();

				std::string annotationBlock = input.substr(i + 2, endAnnotationPos - (i + 2));
				currentAnnotationsForNext.push_back(ParseAnnotation(annotationBlock));

				i = endAnnotationPos;
				current.str("");
				continue;
			}
			else if (input[i] == ' ')
			{
				std::string full = trim(current.str());
				if (full == "class" || full == "struct" || full == "enum" || full == "namespace")
				{
					current.str("");
					i = ParseObjects(input, &newClass, currentQualifier, i - full.size());
					continue;
				}
			}
			else if (input[i] == '}')
			{
				pos = i + 1;
				break;
			}
			else if (input[i] == ':')
			{
				std::string full = trim(current.str());
				if (full == "public" || full == "private" || full == "protected")
				{
					if (full == "private")
						currentQualifier = Qualifier::Private;
					else if (full == "protected")
						currentQualifier = Qualifier::Protected;
					else if (full == "public")
						currentQualifier = Qualifier::Public;
					current.str("");
					i++;
					continue;
				}
			}
			else if (input[i] == ';' || input[i] == '{')
			{
				std::string full = trim(current.str());
				current.str("");

				if (!full.empty())
				{
					if (full.find("(") != std::string::npos)
						newClass.mMethods.push_back(ParseMethod(full, currentQualifier));
					else
						newClass.mFields.push_back(ParseField(full, currentQualifier));
				}
				if (input[i] == '{')
				{
					ReadBlockContent(input, i, i);
				}

				i++;
				continue;
			}
			current << input[i];
			i++;
		}

		if (parent == NULL)
			MainObjects.push_back(newClass);
		else
			parent->mChildObjects.push_back(newClass);
		return pos;
	}


	std::vector<std::string> Analyzer::ParseSymbols(const std::string& input)
	{
		std::vector<std::string> result;

		int openCurlyBracked = 0; // {
		int openBracket = 0; // (
		int openSharpBracket = 0; // <

		std::string current;
		for (std::string::const_iterator it(input.begin()); it != input.end(); ++it)
		{
			if (*it == '{')
				openCurlyBracked ++;
			else if (*it == '}')
				openCurlyBracked --;
			else if (*it == '<')
				openSharpBracket ++;
			else if (*it == '>')
				openSharpBracket --;
			else if (*it == '(')
				openBracket ++;
			else if (*it == ')')
				openBracket --;
			else if (*it == ',' || *it == ';')
			{
				if (openBracket == 0 && openSharpBracket == 0 && openCurlyBracked == 0)
				{
					current = trim(current);
					if (!current.empty())
						result.push_back(current);
					current = "";
					continue;
				}
			}
			if (openBracket < 0 || openSharpBracket < 0 || openCurlyBracked < 0)
				break;
			current += *it;
		}

		current = trim(current);
		if (!current.empty())
			result.push_back(current);

		return result;
	}


	TypeInfo Analyzer::ParseTypeInfo(const std::string& typeString)
	{
		std::string input = typeString;

		TypeInfo result;
		result.mIsPointer = input[input.size() - 1] == '*';
		result.mIsReference = input[input.size() - 1] == '&';

		std::string constDelimiter = "const ";
		std::string::size_type pos = input.find(constDelimiter);
		if (pos != std::string::npos)
		{
			input.replace(pos, constDelimiter.size(), "");
			result.mIsConst = true;
		}
		else
			result.mIsConst = false;

		std::string staticDelimiter = "static ";
		pos = input.find(staticDelimiter);
		if (pos != std::string::npos)
		{
			input.replace(pos, staticDelimiter.size(), "");
			result.mIsStatic = true;
		}
		else
			result.mIsStatic = false;

		pos = 0;

		// get name of class
		std::vector<std::string> endTypeNameDelimiters;
		endTypeNameDelimiters.push_back("{");
		endTypeNameDelimiters.push_back("<");
		endTypeNameDelimiters.push_back("(");
		endTypeNameDelimiters.push_back("*");
		endTypeNameDelimiters.push_back("&");

		std::string::size_type oldPos = pos;
		result.mTypeName = trim(ExtractData(input, pos, endTypeNameDelimiters, pos));
		if (result.mTypeName.empty())
		{
			result.mTypeName = trim(input.substr(oldPos));
			return result;
		}
		// search template parameters
		if (pos > 0 && input[pos -1] == '<')
		{
			std::vector<std::string> tokens = ParseSymbols(input.substr(pos));
			for (unsigned int i = 0; i < tokens.size(); ++i)
			{
				result.mTemplateParameter.push_back(ParseTypeInfo(trim(tokens[i])));
			}
		}
		return result;
	}

	FieldInfo Analyzer::ParseField(const std::string& input, Qualifier::Enumeration qualifier)
	{
		FieldInfo result;
		result.mQualifier = qualifier;

		std::vector<std::string> endTypeNameDelimiters;
		endTypeNameDelimiters.push_back("*");
		endTypeNameDelimiters.push_back(" ");
		endTypeNameDelimiters.push_back("&");

		std::string::size_type pos;
		std::string typePart = ExtractDataReverse(input, std::string::npos, endTypeNameDelimiters, pos);
		std::string namePart = input;
		namePart.erase(0, pos);
		result.mType = ParseTypeInfo(trim(typePart));
		result.mName = namePart;
		return result;
	}


	MethodInfo Analyzer::ParseMethod(const std::string& input, Qualifier::Enumeration qualifier)
	{
		MethodInfo result;
		result.mAnnotations = currentAnnotationsForNext;
		currentAnnotationsForNext.clear();
		result.mQualifier = qualifier;

		std::string::size_type startPos = input.find("(");
		std::string::size_type endPos = input.find(")");
		std::string parameters = input.substr(startPos + 1, endPos - startPos - 1);
		std::string beforeParameters = input.substr(0, startPos);
		std::string afterParameters = input.substr(endPos + 1);

		std::vector<std::string> endTypeNameDelimiters;
		endTypeNameDelimiters.push_back("*");
		endTypeNameDelimiters.push_back(" ");
		endTypeNameDelimiters.push_back("&");

		std::string::size_type pos;
		std::string typePart = ExtractDataReverse(beforeParameters, std::string::npos, endTypeNameDelimiters, pos);
		std::string namePart = beforeParameters;
		namePart.erase(0, pos);

		std::string virtualString = "virtual ";
		pos = typePart.find(virtualString);
		if (pos != std::string::npos)
		{
			typePart.replace(pos, virtualString.size(), "");
			result.mIsVirtual = true;
			if (typePart.empty())
			{
				typePart = namePart;
				namePart = "";
			}
		}
		else
			result.mIsVirtual = false;

		result.mType = ParseTypeInfo(trim(typePart));
		result.mName = namePart;

		if (namePart.empty())
		{
			result.mName = typePart;
			result.mIsClassConstructor = typePart.find("~") != 0;
			result.mIsClassDestructor = !result.mIsClassConstructor;
		}
		else
		{
			result.mIsClassConstructor = false;
			result.mIsClassDestructor = false;
		}

		if (afterParameters.find("=") != std::string::npos && afterParameters.find("0") != std::string::npos)
			result.mIsAbstract = true;
		else
			result.mIsAbstract = false;

		if (afterParameters.find("const") != std::string::npos)
			result.mIsConst = true;
		else
			result.mIsConst = false;

		std::vector<std::string> argumentsRaw = ParseSymbols(parameters);
		for (unsigned int i = 0; i < argumentsRaw.size(); ++i)
			result.mParameters.push_back(ParseField(argumentsRaw[i], Qualifier::Public));

		return result;
	}

	Annotation Analyzer::ParseAnnotation(const std::string& input)
	{
		Annotation result;

		std::string buffer = input;
		std::string::size_type pos = buffer.find("@");
		buffer.erase(0, pos + 1);
		buffer = trim(buffer);
		pos = buffer.find("(");
		if (pos == std::string::npos)
			pos = buffer.size();

		result.mName = trim(buffer.substr(0, pos));
		if (pos != buffer.size())
		{
			std::string params = buffer.substr(pos + 1, buffer.size() - pos);

			std::string name;
			std::string value;
			bool openQuotationMarks = false;
			bool readsName = true;
			for (unsigned int i = 0; i < params.size(); ++i)
			{
				if (params[i] == '\"')
				{
					if (i == 0 || params[i - 1] != '\\') // "My foo is \"bla"."
						openQuotationMarks = !openQuotationMarks;
				}
				else if (params[i] == '=' && !openQuotationMarks)
				{
					readsName = false;
					continue;
				}
				else if ((params[i] == ',' || params[i] == ')') && !openQuotationMarks)
				{
					value = trim(value);
					if(value[0] == '\"') {
						value = value.substr(1, value.size() - 2);
						value = replaceAll(value, "\\\"", "\"");
					}
					result.mParameters[trim(name)] = value;

					name = "";
					value = "";
					readsName = true;
					continue;
				}

				if (readsName)
					name += params[i];
				else
					value += params[i];
			}
		}

		return result;
	}

	bool Analyzer::IsAnnotation(const std::string& input)
	{
		std::string::size_type start = input.find("//");
		if (start == std::string::npos)
			return false;

		bool foundAnnotation = false;
		for (unsigned int i = start + 2; i < input.length(); ++i)
		{
			if (input[i] == '@')
			{
				foundAnnotation = true;
				break;
			}
			else if (input[i] != ' ' && input[i] != '\t')
				break;
		}
		return foundAnnotation;
	}
}
