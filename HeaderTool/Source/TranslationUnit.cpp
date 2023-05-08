#include "TranslationUnit.h"

namespace TinyReflect
{
	TranslationUnit::TranslationUnit(const std::string& sourceDir, const std::string& destDir)
		: mSourceDir(sourceDir), mDestDir(destDir)
	{
	}

	void TranslationUnit::onResult(clang::ASTContext* context, clang::SourceManager* sourceManager)
	{
		mContext = context;
		mSourceManager = sourceManager;
	}

	void TranslationUnit::onStart()
	{
	}

	void TranslationUnit::onEnd()
	{
		for (auto& it : mGenerators)
		{
			auto& generator = it.second;

			if (!generator.generate(mSourceDir, mDestDir))
			{
				llvm::errs() << "Generator::generate() failed!!";
			}
		}

		mGenerators.clear();
	}

	void TranslationUnit::setSourceDir(const std::string& sourceDir)
	{
		mSourceDir = sourceDir;
	}

	void TranslationUnit::setDestDir(const std::string& destDir)
	{
		mDestDir = destDir;
	}

	void TranslationUnit::onRecordFound(const clang::CXXRecordDecl* record)
	{
		std::string fileName = mSourceManager->getFilename(
			record->getLocation()).data();

		if (!mGenerators.contains(fileName))
		{
			mGenerators.insert(std::pair(fileName, Generator{ mContext, fileName,
				mSourceDir, mDestDir }));
		}

		auto it = mGenerators.find(fileName);
		if (it != mGenerators.end())
		{
			mCurrentGenerator = &it->second;
		}

		if (mCurrentGenerator)
		{
			mCurrentGenerator->addRecord(record);
		}
	}

	void TranslationUnit::onEnumFound(const clang::EnumDecl* enumDecl)
	{
		std::string fileName = mSourceManager->getFilename(
			enumDecl->getLocation()).data();

		if (!mGenerators.contains(fileName))
		{
			mGenerators.insert(std::pair(fileName, Generator{ mContext, fileName,
				mSourceDir, mDestDir }));
		}

		auto it = mGenerators.find(fileName);
		if (it != mGenerators.end())
		{
			mCurrentGenerator = &it->second;
		}

		if (mCurrentGenerator)
		{
			mCurrentGenerator->addEnum(enumDecl);
		}
	}

	void TranslationUnit::onFieldFound(const clang::FieldDecl* field)
	{
		if (mCurrentGenerator)
		{
			mCurrentGenerator->addField(field);
		}
	}
}