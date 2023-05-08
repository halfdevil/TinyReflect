#pragma once

#include "TranslationUnit.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
using namespace clang::ast_matchers;

namespace TinyReflect
{
	class TypeFinder : public MatchFinder::MatchCallback
	{
	public:

		TypeFinder() = default;
		TypeFinder(TranslationUnit* translationUnit);

		void setTranslationUnit(TranslationUnit* translationUnit);

		virtual void run(const MatchFinder::MatchResult& result) override;
		virtual void onStartOfTranslationUnit() override;
		virtual void onEndOfTranslationUnit() override;

	private:

		TranslationUnit* mTranslationUnit{ nullptr };
	};
}