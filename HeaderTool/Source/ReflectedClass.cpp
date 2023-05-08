#include "ReflectedClass.h"
#include <sstream>
#include <iostream>

namespace TinyReflect
{
	ReflectedClass::ReflectedClass(const clang::CXXRecordDecl* record)
		: mRecord(record)
	{
		SmallString64 str;
		llvm::StringRef ptr = getAnnotations(record, str);
		getAttributes(ptr, mAttributes);
	}

	void ReflectedClass::generate(clang::ASTContext* context, llvm::raw_ostream& os) const
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

		bool foundParent = false;

		for (auto& base : mRecord->bases())
		{
			if (auto* parent = base.getType()->getAsCXXRecordDecl(); parent != nullptr)
			{
				std::string parentTypeName = parent->getQualifiedNameAsString();
				os << "    const TinyReflect::Class* parentCls = TinyReflect::GetClass<" << parentTypeName << ">();" << "\n";
				foundParent = true;
				break;
			}
		}

		if (!foundParent)
		{
			os << "    const Class* parentCls = nullptr;" << "\n";
		}

		os << "    static TinyReflect::Class cls(parentCls, \"" << typeName << "\", sizeof(" << typeName << "), " << "\n";
		os << "        fields, fields + numFields);" << "\n";
		os << "\n";
		os << "    if (parentCls)" << "\n";
		os << "    { " << "\n";
		os << "        parentCls->addChild(&cls);" << "\n";
		os << "    } " << "\n";
		os << "\n";
		os << "    return &cls;" << "\n";
		os << "}" << "\n";
		os << "\n";

		os << "template <>" << "\n";
		os << "const TinyReflect::Type* TinyReflect::GetTypeImpl(TinyReflect::TypeTag<" << typeName << ">)" << "\n";
		os << "{ " << "\n";
		os << "    return TinyReflect::GetClass<" << typeName << ">();" << "\n";
		os << "}" << "\n\n";
	}

	void ReflectedClass::addField(const clang::FieldDecl* fieldDecl)
	{
		if (isReflected(fieldDecl, ReflectionType::Field))
		{
			mFields.emplace_back(fieldDecl, (uint32_t)mFields.size());
		}
	}
}