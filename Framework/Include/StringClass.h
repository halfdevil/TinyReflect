#pragma once

#include "Class.h"
#include "ClassVisitor.h"
#include <string>

namespace TinyReflect
{
	class StringClass : public Class
	{
	public:

		using Class::Class;

		virtual void visit(const void* instance, ClassVisitor* visitor,
			int32_t depth = 0) const override;
	};

	const Class* GetClassImpl(ClassTag<std::string>);
	const Type* GetTypeImpl(TypeTag<std::string>);
}