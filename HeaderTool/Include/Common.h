#pragma once

#include "clang/Tooling/Tooling.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace TinyReflect
{
	using SmallString16 = llvm::SmallString<16>;
	using SmallString32 = llvm::SmallString<32>;
	using SmallString64 = llvm::SmallString<64>;

	enum class ReflectionType
	{
		Class,
		Struct,
		Enum,
		Field
	}; 
	
	void tolower(std::string& str);
	void ltrim(std::string& str);
	void rtrim(std::string& str);
	void trim(std::string& str);

	llvm::StringRef getAnnotations(const clang::Decl* decl, SmallString64& str);
	void getAttributes(llvm::StringRef annotaions, std::unordered_map<std::string, std::string>& attributes);

	bool isReflected(const clang::Decl* decl, ReflectionType type);
	bool createPath(const std::string& fileName);

	void createFileNames(const std::string& inFileName, const std::string& inSrcDir, 
		const std::string& inDestDir, std::string& outFileName);
}