#include "TemplateClass.h"

namespace TinyReflect
{
	TemplateClass::TemplateClass(const Class* parent, const char* name, uint32_t size, Field* fields, 
		Field* lastField, Field* templateArgs, Field* lastTemplateArg) : 
		Class(parent, name, size, fields, lastField),
		mTemplateArgs(templateArgs),
		mLastTemplateArg(lastTemplateArg)
	{

	}

	Iterator<Field> TemplateClass::getTemplateArgs() const
	{
		return Iterator<Field>(mTemplateArgs, mLastTemplateArg);
	}

	const Field* TemplateClass::getTemplateArg(const char* name) const
	{
		for (const auto& arg : getTemplateArgs())
		{
			if (strcmp(arg.getName(), name) == 0)
			{
				return &arg;
			}
		}

		return nullptr;
	}
}