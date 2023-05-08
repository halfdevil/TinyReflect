#pragma once

#include <stdint.h>
#include <typeinfo>

namespace TinyReflect
{
	template <typename T>
	class TypeTag
	{
	};

	template <typename T>
	struct TypeName
	{
		static const char* get()
		{
			return typeid(T).name();
		}
	};

	class Type
	{
	public:

		Type() = default;
		Type(const char* name, uint32_t size);

		const char* getName() const
		{
			return mName;
		}

		uint32_t getSize() const
		{
			return mSize;
		}

		uint64_t getHash() const
		{
			return mHash;
		}

		virtual bool isRecord() const;
		virtual bool isEnum() const;

	private:

		void calculateHash();

	private:

		const char* mName{ nullptr };
		uint32_t mSize{ 0 };
		uint64_t mHash{ 0 };
	};

	template <typename T>
	const Type* GetTypeImpl(TypeTag<T>);

	template <typename T>
	const Type* GetType()
	{
		return GetTypeImpl(TypeTag<T>());
	}

	template <typename T>
	const Type* GetType();
}