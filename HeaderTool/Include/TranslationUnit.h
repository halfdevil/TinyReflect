#pragma once

#include "Common.h"
#include "Generator.h"
#include <unordered_map>

#include "clang/ASTMatchers/ASTMatchFinder.h"
using namespace clang::ast_matchers;

namespace TinyReflect
{
	class TranslationUnit
	{
	public:

		TranslationUnit() = default;
		TranslationUnit(const std::string& sourceDir, const std::string& destDir);

		void onResult(clang::ASTContext* context, clang::SourceManager* sourceManager);
		void onStart();
		void onEnd();

		void setSourceDir(const std::string& sourceDir);
		void setDestDir(const std::string& destDir);

		void onRecordFound(const clang::CXXRecordDecl* record);
		void onEnumFound(const clang::EnumDecl* enumDecl);
		void onFieldFound(const clang::FieldDecl* field);

	private:

		std::string mSourceDir;
		std::string mDestDir;
		MatchFinder mMatchFinder;
		clang::ASTContext* mContext{ nullptr };
		clang::SourceManager* mSourceManager{ nullptr };
		Generator* mCurrentGenerator{ nullptr };
		std::unordered_map<std::string, Generator> mGenerators;
	};
}