#include "StringClass.h"

namespace TinyReflect
{
	void StringClass::visit(const void* instance, ClassVisitor* visitor, int32_t depth) const
	{
		if (!instance)
		{
			visitor->primitive(this, instance);
			return;
		}

		visitor->stringElement(this, instance);
	}

	template <>
	const Class* GetClassImpl(ClassTag<std::string>)
	{
		static uint32_t numFields = 0;
		static Field fields[1];

		static StringClass cls(nullptr, "std::string", sizeof(std::string),
			fields, fields + numFields);

		return &cls;
	}

	template <>
	const Type* GetTypeImpl(TypeTag<std::string>)
	{
		return GetClassImpl(ClassTag<std::string>());
	}
}