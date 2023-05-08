#pragma once

#include "Property.h"

namespace TinyReflect
{
	class CLASS() TestObjectCustom
	{
	public:

		BODY()

		TestObjectCustom() = default;
		TestObjectCustom(const std::string & name) :
			mName(name)
		{
		}

		const std::string& getName() const
		{
			return mName;
		}

	private:

		PROPERTY()
		std::string mName;
	};
}
