#include "ReflectedEnum.h"
#include "Enum.h"

namespace TinyReflect
{
	ReflectedEnum::ReflectedEnum(const clang::EnumDecl* enumDecl)
		: mEnumDecl(enumDecl)
	{
	}

	void ReflectedEnum::generate(clang::ASTContext* context, llvm::raw_ostream& os) const
	{
		std::string typeName = mEnumDecl->getQualifiedNameAsString();

		std::vector<clang::EnumConstantDecl*> members;
		for (auto itemDecl : mEnumDecl->enumerators())
		{
			members.push_back(itemDecl);
		}

		os << "template <>" << "\n";
		os << "const TinyReflect::Enum* TinyReflect::GetEnumImpl(TinyReflect::EnumTag<" << typeName << ">)" << "\n";
		os << "{ " << "\n";
		os << "    static uint32_t numMembers = " << members.size() << ";" << "\n";
		os << "    static TinyReflect::EnumMember members[" << members.size() + 1 << "] = {" << "\n";

		for (auto& member : members)
		{
			generateMember(context, member, typeName, os);
		}

		os << "    };" << "\n";
		os << "" << "\n";
		os << "    static TinyReflect::Enum enm(\"" << typeName << "\", sizeof(" << typeName << "), " << "\n";
		os << "        members, members + numMembers);" << "\n";
		os << "" << "\n";
		os << "        return &enm;" << "\n";
		os << "}" << "\n";
		os << "" << "\n";

		os << "template <>" << "\n";
		os << "const TinyReflect::Type* TinyReflect::GetTypeImpl(TinyReflect::TypeTag<" << typeName << ">)" << "\n";
		os << "{ " << "\n";
		os << "    return TinyReflect::GetEnum<" << typeName << ">();" << "\n";
		os << "} " << "\n\n";
	}

	void ReflectedEnum::generateMember(clang::ASTContext* context, clang::EnumConstantDecl* memberDecl,
		const std::string& parentType, llvm::raw_ostream& os) const
	{
		std::string typeName = memberDecl->getNameAsString();

		os << "        { \"" << typeName << "\", (uint32_t)" << parentType << "::" << typeName << " }, " << "\n";
	}
}