#pragma once

#include <cstdint>

namespace TinyReflect
{
	class EnumMember
	{
	public:

		EnumMember() = default;
		EnumMember(const char* name, uint32_t value);

		const char* getName() const
		{
			return mName;
		}

		uint32_t getValue() const
		{
			return mValue;
		}

	private:

		const char* mName{ nullptr };
		uint32_t mValue{ 0 };
	};
}