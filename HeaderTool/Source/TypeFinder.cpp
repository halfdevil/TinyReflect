#include "TypeFinder.h"

namespace TinyReflect
{
	TypeFinder::TypeFinder(TranslationUnit* translationUnit)
		: mTranslationUnit(translationUnit)
	{
	}

	void TypeFinder::setTranslationUnit(TranslationUnit* translationUnit)
	{
		mTranslationUnit = translationUnit;
	}

	void TypeFinder::run(const MatchFinder::MatchResult& result)
	{
		mTranslationUnit->onResult(result.Context, result.SourceManager);

		const clang::CXXRecordDecl* record = result.Nodes.getNodeAs<
			clang::CXXRecordDecl>("id");

		if (record)
		{
			mTranslationUnit->onRecordFound(record);
		}

		const clang::EnumDecl* enumDecl = result.Nodes.getNodeAs<
			clang::EnumDecl>("id");

		if (enumDecl)
		{
			mTranslationUnit->onEnumFound(enumDecl);
		}

		const clang::FieldDecl* field = result.Nodes.getNodeAs<
			clang::FieldDecl>("id");

		if (field)
		{
			mTranslationUnit->onFieldFound(field);
		}
	}

	void TypeFinder::onStartOfTranslationUnit()
	{
		mTranslationUnit->onStart();
	}

	void TypeFinder::onEndOfTranslationUnit()
	{
		mTranslationUnit->onEnd();
	}
}