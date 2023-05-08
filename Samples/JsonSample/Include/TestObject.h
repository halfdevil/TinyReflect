#pragma once

#include "Property.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdio.h>

namespace TinyReflect
{
	char const* spaces =
		"                                                                             "
		"                                                                             "
		"                                                                             ";

	enum class ENUM() TestEnum : uint32_t
	{
		Enum1 = 0,
		Enum2
	};

	struct STRUCT() InnerStruct
	{
		BODY()

		PROPERTY()
		int32_t mValue{ 2 };

		void dump(int32_t depth)
		{
			printf("%.*smValue = %d\n", depth * 4, spaces, mValue);
		}
	};

	struct STRUCT() TestStruct
	{
		BODY()

		PROPERTY()
		int32_t mValue{ 0 };

		PROPERTY()
		InnerStruct mInnerStruct;

		void dump(int32_t depth)
		{
			printf("%.*smValue = %d\n", depth * 4, spaces, mValue);
			printf("%.*s{\n", depth * 4, spaces);
			mInnerStruct.dump(depth + 1);
			printf("%.*s}\n", depth * 4, spaces);
		}
	};

	class CLASS() TestObject
	{
		BODY()

	public:

		void dump(int32_t depth)
		{
			printf("%.*smValue = %d\n", depth * 4, spaces, mValue);
			printf("%.*smStruct = {\n", depth * 4, spaces);
			mStruct.dump(depth + 1);
			printf("%.*s}\n", depth * 4, spaces);

			printf("%.*smArray = {\n", depth * 4, spaces);
			printf("%.*s%d, %d, %d, %d\n", (depth + 1) * 4, spaces, 
				mArray[0], mArray[1], mArray[2], mArray[3]);
			printf("%.*s}\n", depth * 4, spaces);

			printf("%.*smVec = {\n", depth * 4, spaces);
			for (auto& i : mVec)
			{
				printf("%.*s %d,\n", (depth + 1) * 4, spaces, i);
			}
			printf("%.*s}\n", depth * 4, spaces);

			printf("%.*smString = %s\n", depth * 4, spaces, mString.c_str());

			printf("%.*smMap = {\n", depth * 4, spaces);
			for (auto& it : mMap)
			{
				printf("%.*sKey = %s\n", (depth + 1) * 4, spaces, it.first.c_str());
				printf("%.*sInnerStruct = {\n", (depth + 1) * 4, spaces);
				it.second.dump(depth + 2); 
				printf("%.*s}\n", (depth + 1) * 4, spaces);
			}
			printf("%.*s}\n", depth * 4, spaces);
		}

	public:

		PROPERTY()
		int32_t mValue{ 0 };

		PROPERTY()
		TestStruct mStruct;

		PROPERTY()
		int mArray[4];

		PROPERTY()
		Vector<int32_t> mVec;

		PROPERTY()
		std::string mString;

		PROPERTY()
		Map<TestStruct> mMap;
	};
}