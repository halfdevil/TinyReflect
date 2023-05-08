#pragma once

#include "Type.h"

namespace TinyReflect
{
	enum class FieldFlags : uint32_t
	{
		None = 0x0,
		ReadOnly = 0x1,
		CString = 0x2
	};

	enum class FieldCVQualifier : uint32_t
	{
		None = 0x0,
		Const = 0x1,
		Volatile = 0x2,
		ConstVolatile = 0x1 | 0x2
	};

	enum class FieldRefQualifier : uint8_t
	{
		None = 0x0,
		Ref = 0x1,
		RefRef = 0x2
	};

	struct FieldQualifier
	{
		uint32_t cvQual{ (uint32_t)FieldCVQualifier::None };
		uint32_t refQual{ (uint32_t)FieldRefQualifier::None };
		bool isPointer{ false };
		bool isArray{ false };
		uint32_t arrayLen{ 0 };
	};

	class Field
	{
	public:

		Field() = default;
		Field(const Type* type, const char* name, uint32_t offset,
			uint32_t flags, FieldQualifier qualifier);

		const Type* getType() const
		{
			return mType;
		}

		const char* getName() const
		{
			return mName;
		}

		uint32_t getFlags() const
		{
			return mFlags;
		}

		uint32_t getOffset() const
		{
			return mOffset;
		}

		const FieldQualifier& getQualifier() const
		{
			return mQualifier;
		}

		template <typename T>
		void setValue(void* instance, const T& value) const noexcept
		{
			memcpy(((char*)instance + mOffset), &value, sizeof(T));
		}

		template <typename T>
		T getAs(const void* instance) const noexcept
		{
			T ret;
			memcpy(&ret, ((char*)instance + mOffset), sizeof(T));
		}

		template <typename T>
		const T* getPointer(const void* instance) const noexcept
		{
			return (const T*)((char*)instance + mOffset);
		}

		template <typename T>
		T* getPointer(const void* instance) const noexcept
		{
			return (const T*)((char*)instance + mOffset);
		}

		const void* getVoidPointer(const void* instance) const noexcept;

	protected:

		const Type* mType{ nullptr };
		const char* mName{ nullptr };
		uint32_t mFlags{ (uint8_t)FieldFlags::None };
		uint32_t mOffset{ 0 };
		FieldQualifier mQualifier;
	};
}