#pragma once

#include "TemplateClass.h"
#include "ClassVisitor.h"
#include "Vector.h"

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

			visitor->vectorBegin(this, depth, (uint32_t)vec->size(), instance);

			for (const auto& e : *vec)
			{
				visitor->vectorElement(type, depth + 1, i++);

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

			visitor->vectorEnd(this, depth);
		}
	};

	template <class T>
	const Class* GetClassImpl(ClassTag<Vector<T>>)
	{
		static uint32_t numFields = 0;
		static Field fields[1];

		static uint32_t numTemplateArgs = 1;
		static Field templateArgs[2] = {
			Field(GetType<T>(), TypeName<T>::get(), 0, 0, {})
		};

		static std::string typeName =
			std::string("Vector<") +
			std::string(TypeName<T>::get()) +
			std::string(">");

		static VectorClass<Vector<T>> cls(nullptr, typeName.c_str(), sizeof(Vector<T>),
			fields, fields + numFields,	templateArgs, 
			templateArgs + numTemplateArgs);

		return &cls;
	}

	template <typename T>
	const Type* GetTypeImpl(TypeTag<Vector<T>>)
	{
		return GetClassImpl(ClassTag<Vector<T>>());
	}
}