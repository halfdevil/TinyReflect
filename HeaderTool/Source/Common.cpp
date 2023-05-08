#include "Common.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include <iostream>
#include <algorithm>

namespace TinyReflect
{
	void tolower(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char ch) {
			return std::tolower(ch);
		});
	}

	void ltrim(std::string& str)
	{
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	void rtrim(std::string& str)
	{
		str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), str.end());
	}

	void trim(std::string& str)
	{
		ltrim(str);
		rtrim(str);
	}

	llvm::StringRef getAnnotations(const clang::Decl* decl, SmallString64& str)
	{
		llvm::raw_svector_ostream os(str);

		for (auto& attr : decl->attrs())
		{
			if (attr->getKind() == clang::attr::Annotate)
			{
				attr->printPretty(os, { {} });
				return str.slice(26, str.size() - 4);
			}
		}

		return {};
	}

	void getAttributes(llvm::StringRef annotaions, std::unordered_map<std::string, std::string>& attributes)
	{
		std::string input = std::string(annotaions.data());
		if (auto pos = input.rfind("\""); pos != input.npos)
		{
			input = input.substr(0, pos);
		}

		std::istringstream is(input);
		std::string s;

		while (getline(is, s, ','))
		{
			if (auto pos = s.find("="); pos != s.npos)
			{
				std::string key = s.substr(0, pos);
				std::string value = s.substr(pos + 1);

				trim(key);
				trim(value);
				tolower(key);
				tolower(value);

				if (value.starts_with("\""))
				{
					value = value.substr(1);
				}

				if (value.ends_with("\""))
				{
					value = value.substr(0, value.length() - 1);
				}

				attributes.insert(std::pair(key, value));
			}
			else
			{
				trim(s);
				tolower(s);

				attributes.insert(std::pair(s, "true"));
			}
		}
	}

	bool isReflected(const clang::Decl* decl, ReflectionType type)
	{
		SmallString64 str;
		std::string typeStr;
		llvm::StringRef ptr = getAnnotations(decl, str);

		switch (type)
		{
		case ReflectionType::Class:
			typeStr = "reflect-class";
			break;

		case ReflectionType::Struct:
			typeStr = "reflect-struct";
			break;

		case ReflectionType::Enum:
			typeStr = "reflect-enum";
			break;

		case ReflectionType::Field:
			typeStr = "reflect-field";
			break;
		}

		if (ptr.startswith(typeStr))
		{
			return true;
		}

		return false;
	}

	bool createPath(const std::string& fileName)
	{
		fs::path filePath(fileName);

		if (!fs::is_directory(fileName))
		{
			filePath.remove_filename();
		}

		return fs::create_directories(filePath);
	}

	void createFileNames(const std::string& inFileName, const std::string& inSrcDir, 
		const std::string& inDestDir, std::string& outFileName)
	{
		std::string fileName = inFileName;
		std::string srcDir = inSrcDir;
		std::string destDir = inDestDir;

		std::replace(std::begin(fileName), std::end(fileName), '\\', '/');
		std::replace(std::begin(srcDir), std::end(srcDir), '\\', '/');
		std::replace(std::begin(destDir), std::end(destDir), '\\', '/');

		fs::path outputPath(destDir);
		if (fileName.starts_with(srcDir))
		{
			outFileName = fileName.substr(srcDir.length());
			outputPath.append(fileName.substr(srcDir.length()));
		}
		else
		{
			outFileName = inFileName;
			outputPath.append(fileName);
		}

		outputPath.replace_extension("generated.h");
		outFileName = outputPath.string();
	}
}