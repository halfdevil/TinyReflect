#include "Generator.h"
#include "Common.h"
#include <iostream>

namespace TinyReflect
{
	Generator::Generator(clang::ASTContext* context, const std::string& fileName,
		const std::string& sourceDir, const std::string& destDir)
		: mContext(context)
	{
		createFileNames(fileName, sourceDir, destDir, mOutputFileName);
		createPath(mOutputFileName);
	}

	void Generator::addRecord(const clang::CXXRecordDecl* record)
	{
		if (isReflected(record, ReflectionType::Class))
		{
			mClasses.emplace_back(record);
			mLastRecordIsClass = true;
		}
		else if (isReflected(record, ReflectionType::Struct))
		{
			mStructs.emplace_back(record);
			mLastRecordIsClass = false;
		}
	}

	void Generator::addEnum(const clang::EnumDecl* enumDecl)
	{
		if (isReflected(enumDecl, ReflectionType::Enum))
		{
			mEnums.emplace_back(enumDecl);
		}
	}

	void Generator::addField(const clang::FieldDecl* field)
	{
		if (mLastRecordIsClass)
		{
			ReflectedClass& cls = mClasses.back();
			cls.addField(field);
		}
		else
		{
			ReflectedStruct& strt = mStructs.back();
			strt.addField(field);
		}
	}

	bool Generator::generate(const std::string& sourceDir, const std::string& destDir) const
	{
		std::error_code ec;

		llvm::raw_fd_ostream os(mOutputFileName, ec);
		if (ec)
		{
			llvm::errs() << "Error opening file: " << mOutputFileName.c_str();
			return false;
		}

		os << "#pragma once" << "\n";
		os << "" << "\n";
		os << "/* This is an auto generated file. !!DO NOT EDIT THIS!! */" << "\n";
		os << "" << "\n";
		os << "#include \"Property.h\"" << "\n";
		os << "#include <cstddef>" << "\n";
		os << "" << "\n";

		for (auto& enm : mEnums)
		{
			enm.generate(mContext, os);
		}

		for (auto& strt : mStructs)
		{
			strt.generate(mContext, os);
		}

		for (auto& cls : mClasses)
		{
			cls.generate(mContext, os);
		}

		os << "\n";

		return true;
	}
}