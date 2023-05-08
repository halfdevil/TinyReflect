#include "Field.h"

namespace TinyReflect
{
	Field::Field(const Type* type, const char* name, uint32_t offset,
		uint32_t flags, FieldQualifier qualifier) : 
		mType(type),
		mName(name),
		mOffset(offset),
		mFlags(flags),
		mQualifier(qualifier)
	{
	}

	const void* Field::getVoidPointer(const void* instance) const noexcept
	{
		return (const void*)((char*)instance + mOffset);
	}
}