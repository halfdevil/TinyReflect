#include "EnumMember.h"

namespace TinyReflect
{
	EnumMember::EnumMember(const char* name, uint32_t value) : 
		mName(name), 
		mValue(value)
	{
	}
}