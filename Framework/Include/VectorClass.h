#pragma once

#include "TemplateClass.h"
#include "ClassVisitor.h"
#include <vector>

namespace TinyReflect
{
	template <typename T>
	class VectorClass : public TemplateClass
	{
	public:

		using TemplateClass::TemplateClass;

		virtual void visit(const void* instance, ClassVisitor* visitor,
			int32_t depth = 0) const override
		{
			if (!instance)
			{
				visitor->primitive(this, instance);
				return;
			}

			uint32_t i = 0;

			const Type* type = GetType<typename T::value_type>();
			const T* vec = (const T*)instance;

			visitor->arrayBegin(this, depth, (uint32_t)vec->size());

			for (const auto& e : *vec)
			{
				visitor->arrayElement(type, depth + 1, i++);

				if (type->isRecord())
				{
					const Class* cls = (const Class*)type;
					cls->visit(&e, visitor, depth + 1);
				}
				else
				{
					visitor->primitive(type, &e);
				}
			}

			visitor->arrayEnd(this, depth);
		}
	};

	template <class T>
	const Class* GetClassImpl(ClassTag<std::vector<T>>)
	{
		static uint32_t numFields = 0;
		static Field fields[1];

		static uint32_t numTemplateArgs = 1;
		static Field templateArgs[2] = {
			Field(GetType<T>(), TypeName<T>::get(), 0, 0, {}, {})
		};

		static std::string typeName =
			std::string("std::vector<") +
			std::string(TypeName<T>::get()) +
			std::string(">");

		static VectorClass<std::vector<T>> cls(typeName.c_str(), sizeof(std::vector<T>),
			fields, fields + numFields,	templateArgs, 
			templateArgs + numTemplateArgs);

		return &cls;
	}

	template <typename T>
	const Type* GetTypeImpl(TypeTag<std::vector<T>>)
	{
		return GetClassImpl(ClassTag<std::vector<T>>());
	}
}