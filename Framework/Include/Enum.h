#pragma once

#include "Type.h"
#include "EnumMember.h"
#include "Iterator.h"

namespace TinyReflect
{
	template <typename T>
	class EnumTag
	{
	};

	class Enum : public Type
	{
	public:

		Enum() = default;
		Enum(const char* name, uint32_t size, EnumMember* members, EnumMember* lastMember);

		Iterator<EnumMember> getMembers() const;
		const EnumMember* getMember(const char* name) const;

		virtual bool isEnum() const override;

	private:

		EnumMember* mMembers{ nullptr };
		EnumMember* mLastMember{ nullptr };
	};

	template <typename T>
	const Enum* GetEnumImpl(EnumTag<T>);

	template <typename T>
	const Enum* GetEnum()
	{
		return GetEnumImpl(EnumTag<T>());
	}
}