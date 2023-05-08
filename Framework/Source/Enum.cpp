#include "Enum.h"
#include <string.h>

namespace TinyReflect
{
	Enum::Enum(const char* name, uint32_t size,	EnumMember* members, EnumMember* lastMember) : 
		Type(name, size),
		mMembers(members),
		mLastMember(lastMember)
	{
	}

	Iterator<EnumMember> Enum::getMembers() const
	{
		return Iterator<EnumMember>(mMembers, mLastMember);
	}

	const EnumMember* Enum::getMember(const char* name) const
	{
		for (const auto& member : getMembers())
		{
			if (strcmp(member.getName(), name) == 0)
			{
				return &member;
			}
		}

		return nullptr;
	}

	bool Enum::isEnum() const
	{
		return true;
	}
}