#pragma once

#include "Property.h"

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
		BODY()

	public:

		PROPERTY()
		std::string mObjectName;

		PROPERTY()
		TestEnum mEnum { TestEnum::Enum1 };

		PROPERTY()
		TestStruct mStruct;
	};
}