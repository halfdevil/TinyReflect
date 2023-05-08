#include "ReflectedStruct.h"
#include <sstream>
#include <iostream>

namespace TinyReflect
{
	ReflectedStruct::ReflectedStruct(const clang::CXXRecordDecl* record)
		: mRecord(record)
	{
		SmallString64 str;
		llvm::StringRef ptr = getAnnotations(record, str);
		getAttributes(ptr, mAttributes);
	}

	void ReflectedStruct::generate(clang::ASTContext* context, llvm::raw_ostream& os) const
	{
		std::string typeName = mRecord->getQualifiedNameAsString();

		os << "template <>" << "\n";
		os << "const TinyReflect::Class* TinyReflect::GetClassImpl(TinyReflect::ClassTag<" << typeName << ">)" << "\n";
		os << "{ " << "\n";
		os << "    static uint32_t numFields = " << mFields.size() << ";" << "\n";
		os << "    static TinyReflect::Field fields[" << mFields.size() + 1 << "] = {" << "\n";

		for (auto& field : mFields)
		{
			field.generate(context, typeName, os);
			os << "," << "\n";
		}

		os << "    };" << "\n";
		os << "" << "\n";

		if (auto* p = mRecord->getParent(); p != nullptr)
		{
			if (auto* pr = dyn_cast<clang::CXXRecordDecl>(p); pr != nullptr)
			{
				std::string parentTypeName = pr->getQualifiedNameAsString();
				os << "    const TinyReflect::Class* parentCls = TinyReflect::GetClass<" << parentTypeName << ">();" << "\n";
			}
			else
			{
				os << "    const TinyReflect::Class* parentCls = nullptr;" << "\n";
			}
		}
		else
		{
			os << "    const TinyReflect::Class* parentCls = nullptr;" << "\n";
		}

		os << "    static TinyReflect::Class cls(parentCls, \"" << typeName << "\", sizeof(" << typeName << "), " << "\n";
		os << "        fields, fields + numFields);" << "\n";
		os << "" << "\n";
		os << "    return &cls;" << "\n";
		os << "}" << "\n";
		os << "" << "\n";

		os << "template <>" << "\n";
		os << "const TinyReflect::Type* TinyReflect::GetTypeImpl(TinyReflect::TypeTag<" << typeName << ">)" << "\n";
		os << "{ " << "\n";
		os << "    return TinyReflect::GetClass<" << typeName << ">();" << "\n";
		os << "}" << "\n\n";
	}

	void ReflectedStruct::addField(const clang::FieldDecl* fieldDecl)
	{
		if (isReflected(fieldDecl, ReflectionType::Field))
		{
			mFields.emplace_back(fieldDecl, (uint32_t)mFields.size());
		}
	}
}