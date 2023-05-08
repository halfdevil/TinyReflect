#pragma once

#include "ReflectedField.h"
#include <vector>
#include <unordered_map>

namespace TinyReflect
{
	class ReflectedStruct
	{
	public:

		ReflectedStruct() = default;
		ReflectedStruct(const clang::CXXRecordDecl* record);

		void generate(clang::ASTContext* context, llvm::raw_ostream& os) const;
		void addField(const clang::FieldDecl* fieldDecl);

	private:

		const clang::CXXRecordDecl* mRecord{ nullptr };
		std::vector<ReflectedField> mFields;
		std::unordered_map<std::string, std::string> mAttributes;
	};
}