#pragma once

#include "Common.h"
#include "clang/AST/RecursiveASTVisitor.h"

namespace TinyReflect
{
	class ReflectedEnum
	{
	public:

		ReflectedEnum() = default;
		ReflectedEnum(const clang::EnumDecl* enumDecl);

		void generate(clang::ASTContext* context, llvm::raw_ostream& os) const;

	private:

		void generateMember(clang::ASTContext* context, clang::EnumConstantDecl* memberDecl,
			const std::string& parentType, llvm::raw_ostream& os) const;

	private:

		const clang::EnumDecl* mEnumDecl{ nullptr };
	};
}