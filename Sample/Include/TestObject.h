#pragma once

#include "Property.h"
#include "TestObjectCustom.h"

namespace TinyReflect
{
	enum class ENUM() TestEnum : uint32_t
	{
		Enum1 = 0,
		Enum2
	};

	struct STRUCT() TestStruct
	{
		BODY()

		PROPERTY()
		float value1{ 0.0f };

		PROPERTY()
		int32_t value2{ 0 };

		PROPERTY()
		uint32_t value3{ 0 };
	};

	class CLASS() TestObject
	{
	public:

		BODY()

		TestObject() = default;
		TestObject(const std::string & name) : 
			mObjectName(name)
		{
		}

	private:

		PROPERTY()
		std::string mObjectName;

		PROPERTY()
		TestStruct mStruct;

		PROPERTY()
		TestEnum mEnum { TestEnum::Enum1 };

		PROPERTY()
		TestObjectCustom mCustomObject;
	};
}