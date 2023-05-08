#pragma once

#include "TypeFinder.h"
#include "clang/Tooling/CommonOptionsParser.h"
using namespace clang::tooling;

namespace TinyReflect
{
	class HeaderTool
	{
	public:

		HeaderTool() = default;
		~HeaderTool();

		bool create(const std::string& sourceDir, const std::string& destDir);
		void destroy();
		int run(CommonOptionsParser& optionsParser);

	private:

		TranslationUnit mTranslationUnit;
		TypeFinder mTypeFinder;
		MatchFinder mMatchFinder;
	};
}