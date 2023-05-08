#pragma once

#include "ReflectedClass.h"
#include "ReflectedStruct.h"
#include "ReflectedEnum.h"

namespace TinyReflect
{
	class Generator
	{
	public:

		Generator() = default;
		Generator(clang::ASTContext* context, const std::string& fileName,
			const std::string& sourceDir, const std::string& destDir);

		void addRecord(const clang::CXXRecordDecl* record);
		void addEnum(const clang::EnumDecl* enumDecl);
		void addField(const clang::FieldDecl* field);
		bool generate(const std::string& sourceDir, const std::string& destDir) const;

	private:

		clang::ASTContext* mContext{ nullptr };
		std::string mOutputFileName;
		std::vector<ReflectedClass> mClasses;
		std::vector<ReflectedStruct> mStructs;
		std::vector<ReflectedEnum> mEnums;
		bool mLastRecordIsClass{ true };
	};
}