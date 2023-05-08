#include "HeaderTool.h"
#include "clang/Frontend/FrontendActions.h"

namespace TinyReflect
{
	HeaderTool::~HeaderTool()
	{
		destroy();
	}

	bool HeaderTool::create(const std::string& sourceDir, const std::string& destDir)
	{
		mTranslationUnit.setSourceDir(sourceDir);
		mTranslationUnit.setDestDir(destDir);
		mTypeFinder.setTranslationUnit(&mTranslationUnit);

		static const DeclarationMatcher recordMatcher = cxxRecordDecl(decl().bind("id"),
			hasAttr(clang::attr::Annotate));

		static const DeclarationMatcher enumMatcher = enumDecl(decl().bind("id"),
			hasAttr(clang::attr::Annotate));

		static const DeclarationMatcher fieldMatcher = fieldDecl(decl().bind("id"),
			hasAttr(clang::attr::Annotate));

		mMatchFinder.addMatcher(recordMatcher, &mTypeFinder);
		mMatchFinder.addMatcher(enumMatcher, &mTypeFinder);
		mMatchFinder.addMatcher(fieldMatcher, &mTypeFinder);

		return true;
	}

	void HeaderTool::destroy()
	{
	}

	int HeaderTool::run(CommonOptionsParser& optionsParser)
	{
		ClangTool clangTool(optionsParser.getCompilations(),
			optionsParser.getSourcePathList());

		return clangTool.run(newFrontendActionFactory(&mMatchFinder).get());
	}
}

static llvm::cl::OptionCategory HeaderToolCategory("HeaderTool options");
static llvm::cl::opt<std::string> SourcePath("src-dir", llvm::cl::desc("source directory of the input files"),
	llvm::cl::Required, llvm::cl::cat(HeaderToolCategory));

static llvm::cl::opt<std::string> DestinationPath("dest-dir",
	llvm::cl::desc("destination directory to put the generated files"),
	llvm::cl::Required, llvm::cl::cat(HeaderToolCategory));

int main(int argc, const char** argv)
{
	auto expectedParser = CommonOptionsParser::create(argc, argv, HeaderToolCategory);
	if (!expectedParser)
	{
		llvm::errs() << expectedParser.takeError();
		return 1;
	}

	TinyReflect::HeaderTool headerTool;
	headerTool.create(SourcePath.c_str(), DestinationPath.c_str());

	CommonOptionsParser& optionsParser = expectedParser.get();
	int result = headerTool.run(optionsParser);

	return result;
}