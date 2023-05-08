#pragma once

#include "TemplateClass.h"
#include "ClassVisitor.h"
#include "Map.h"

namespace TinyReflect
{
	template <typename T>
	class MapClass : public TemplateClass
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

			const Type* keyType = GetType<std::string>();
			const Type* valueType = GetType<typename T::mapped_type>();
			const T* umap = (const T*)instance;

			visitor->mapBegin(this, depth, (uint32_t)umap->size(), instance);

			for (const auto& it : *umap)
			{
				visitor->mapElement(keyType, valueType, depth + 1, &it.first);

				if (valueType->isRecord())
				{
					const Class* cls = (const Class*)valueType;
					cls->visit(&it.second, visitor, depth + 1);
				}
				else
				{
					visitor->primitive(valueType, &it.second);
				}
			}

			visitor->mapEnd(this, depth);
		}
	};

	template <typename T>
	const Class* GetClassImpl(ClassTag<Map<T>>)
	{
		static uint32_t numFields = 0;
		static Field fields[1];

		static uint32_t numTemplateArgs = 1;
		static Field templateArgs[2] = {
			Field(GetType<T>(), TypeName<T>::get(), 0, 0, {})
		};

		static std::string typeName =
			std::string("Map<") +
			std::string(TypeName<T>::get()) +
			std::string(">");

		static MapClass<Map<T>> cls(nullptr, typeName.c_str(), sizeof(Map<T>),
			fields, fields + numFields,	templateArgs, 
			templateArgs + numTemplateArgs);

		return &cls;
	}

	template <typename T>
	const Type* GetTypeImpl(TypeTag<Map<T>>)
	{
		return GetClassImpl(ClassTag<Map<T>>());
	}
}