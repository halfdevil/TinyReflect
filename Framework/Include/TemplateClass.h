#pragma once

#include "Class.h"

namespace TinyReflect
{
	class TemplateClass : public Class
	{
	public:

		TemplateClass() = default;
		TemplateClass(const Class* parent, const char* name, uint32_t size, 
			Field* fields, Field* lastField, Field* templateArgs,
			Field* lastTemplateArg);

		Iterator<Field> getTemplateArgs() const;
		const Field* getTemplateArg(const char* name) const;

	private:

		Field* mTemplateArgs{ nullptr };
		Field* mLastTemplateArg{ nullptr };
	};
}