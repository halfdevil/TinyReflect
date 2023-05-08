#include "ReflectedField.h"
#include "Field.h"
#include <iostream>

namespace TinyReflect
{
	const clang::Type* TypeVisitor::getLeaf() const
	{
		return mLeaf;
	}

	bool TypeVisitor::visitType(clang::Type* type)
	{
		mLeaf = type;
		return true;
	}

	ReflectedField::ReflectedField(const clang::FieldDecl* fieldDecl, uint32_t index)
		: mFieldDecl(fieldDecl), mIndex(index)
	{
		SmallString64 str;
		llvm::StringRef ptr = getAnnotations(fieldDecl, str);

		getAttributes(ptr, mAttributes);
	}

	bool ReflectedField::isRecordType() const
	{
		const clang::QualType type = getRealType();
		const clang::Type* t = type.getTypePtrOrNull();

		return t && t->isRecordType();
	}

	bool ReflectedField::isPointerType() const
	{
		const clang::QualType type = mFieldDecl->getType();
		const clang::Type* t = type.getTypePtrOrNull();

		return t && t->isPointerType();
	}

	void ReflectedField::generate(clang::ASTContext* context, const llvm::StringRef& parentType,
		llvm::raw_ostream& os) const
	{
		std::string fieldName = mFieldDecl->getNameAsString();
		SmallString64 typeName = getRealTypeName(context);
		SmallString64 qualifier = getQualifier(context);
		SmallString16 flags = getFlags();

		os << "        TinyReflect::Field(" << "\n";
		os << "            TinyReflect::GetType<" << typeName << ">()," << "\n";
		os << "            \"" << fieldName << "\"," << "\n";
		os << "            offsetof(" << parentType << ", " << fieldName << ")," << "\n";
		os << "            " << flags << "," << "\n";
		os << "            " << qualifier << ")";
	}

	SmallString64 ReflectedField::getQualifier(clang::ASTContext* context) const
	{
		const clang::QualType type = mFieldDecl->getType();
		const clang::Type* t = type.getTypePtrOrNull();

		uint32_t cvQual{ 0 };
		uint32_t refQual{ 0 };

		if (type.isConstant(*context))
		{
			cvQual |= (uint32_t)FieldCVQualifier::Const;
		}

		if (type.isVolatileQualified())
		{
			cvQual |= (uint32_t)FieldCVQualifier::Volatile;
		}

		if (t->isLValueReferenceType())
		{
			refQual |= (uint32_t)FieldRefQualifier::Ref;
		}

		if (t->isRValueReferenceType())
		{
			refQual |= (uint32_t)FieldRefQualifier::RefRef;
		}

		bool isPointer = t->isPointerType();
		bool isArray = t->isArrayType();
		uint64_t arrayLen{ 0 };

		if (isArray)
		{
			const clang::ArrayType* arr = t->getAsArrayTypeUnsafe();
			if (arr && arr->isConstantArrayType())
			{
				auto carr = (const clang::ConstantArrayType*)arr;
				auto size = carr->getSize();
				arrayLen = *size.getRawData();
			}
		}

		SmallString64 out;
		llvm::raw_svector_ostream os(out);

		os << "TinyReflect::FieldQualifier{ " << cvQual << ", " << refQual << ", " <<
			isPointer << ", " << isArray << ", " << arrayLen << " }";

		return out;
	}

	SmallString64 ReflectedField::getRealTypeName(clang::ASTContext* context) const
	{
		const clang::QualType realType = getRealType();

		SmallString64 out;
		llvm::raw_svector_ostream os(out);

		realType.print(os, context->getPrintingPolicy());
		return out;
	}

	SmallString16 ReflectedField::getFlags() const
	{
		SmallString64 str;
		llvm::StringRef ptr = getAnnotations(mFieldDecl, str);

		llvm::SmallVector<llvm::StringRef> attrs;
		ptr.split(attrs, ",");

		uint32_t flags{ 0 };
		for (auto& attr : attrs)
		{
			if (attr.equals_insensitive("readonly"))
			{
				flags |= (uint32_t)FieldFlags::ReadOnly;
			}
			else if (attr.equals_insensitive("cstring"))
			{
				flags |= (uint32_t)FieldFlags::CString;
			}
		}

		SmallString16 out;
		llvm::raw_svector_ostream os(out);

		os << flags;
		return out;
	}

	clang::QualType ReflectedField::getRealType() const
	{
		const clang::QualType type = mFieldDecl->getType();
		const clang::Type* t = type.split().Ty;

		const clang::BuiltinType* builtIn = t->getAs<clang::BuiltinType>();
		if (builtIn)
		{
			return clang::QualType(builtIn, 0);
		}

		const clang::RecordType* recordType = t->getAs<clang::RecordType>();
		if (recordType)
		{
			return clang::QualType(recordType, 0);
		}

		const clang::EnumType* enumType = t->getAs<clang::EnumType>();
		if (enumType)
		{
			return clang::QualType(enumType, 0);
		}

		const clang::PointerType* pointerType = t->getAs<clang::PointerType>();
		if (pointerType)
		{
			return pointerType->getPointeeType();
		}

		const clang::ArrayType* arrayType = clang::dyn_cast_or_null<clang::ArrayType>(t);
		if (arrayType)
		{
			return arrayType->getElementType();
		}

		TypeVisitor visitor;
		visitor.TraverseType(type);

		return clang::QualType(visitor.getLeaf(), 0);
	}
}