#pragma once

#include "Common.h"
#include "clang/AST/RecursiveASTVisitor.h"

namespace TinyReflect
{
	class TypeVisitor : public clang::RecursiveASTVisitor<TypeVisitor>
	{
	public:

		TypeVisitor() = default;

		const clang::Type* getLeaf() const;
		bool visitType(clang::Type* type);

	private:

		clang::Type* mLeaf{ nullptr };
	};

	class ReflectedField
	{
	public:

		ReflectedField() = default;
		ReflectedField(const clang::FieldDecl* fieldDecl, uint32_t index);

		bool isRecordType() const;
		bool isPointerType() const;

		void generate(clang::ASTContext* context, const llvm::StringRef& parentType,
			llvm::raw_ostream& os) const;

	private:

		SmallString64 getQualifier(clang::ASTContext* context) const;
		SmallString64 getRealTypeName(clang::ASTContext* context) const;

		SmallString16 getFlags() const;
		clang::QualType getRealType() const;

	private:

		const clang::FieldDecl* mFieldDecl{ nullptr };
		std::unordered_map<std::string, std::string> mAttributes;
		uint32_t mIndex{ 0 };
	};
}