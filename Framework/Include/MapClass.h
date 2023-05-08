#pragma once

#include "TemplateClass.h"
#include "ClassVisitor.h"
#include <unordered_map>

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

			const Type* keyType = GetType<typename T::key_type>();
			const Type* valueType = GetType<typename T::mapped_type>();
			const T* umap = (const T*)instance;

			visitor->mapBegin(this, depth, (uint32_t)umap->size());

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

	template <typename T, typename V>
	const Class* GetClassImpl(ClassTag<std::unordered_map<T, V>>)
	{
		static uint32_t numFields = 0;
		static Field fields[1];

		static uint32_t numTemplateArgs = 2;
		static Field templateArgs[3] = {
			Field(GetType<T>(), TypeName<T>::get(), 0, 0, {}, {}),
			Field(GetType<V>(), TypeName<V>::get(), 0, 0, {}, {})
		};

		static std::string typeName =
			std::string("std::unordered_map<") +
			std::string(TypeName<T>::get()) +
			std::string(", ") +
			std::string(TypeName<V>::get()) +
			std::string(">");

		static MapClass<std::unordered_map<T, V>> cls(typeName.c_str(), sizeof(std::unordered_map<T, V>),
			fields, fields + numFields,	templateArgs, 
			templateArgs + numTemplateArgs);

		return &cls;
	}

	template <typename T, typename V>
	const Type* GetTypeImpl(TypeTag<std::unordered_map<T, V>>)
	{
		return GetClassImpl(ClassTag<std::unordered_map<T, V>>());
	}
}