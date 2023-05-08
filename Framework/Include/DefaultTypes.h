#pragma once

#include "Type.h"

#define XSTRINGIFY(s) #s
#define STRINGIFY(s) XSTRINGIFY(s)

#define DEFINE_TYPE_EXTERN(t)                                       \
	extern const Type* GetTypeImpl(TypeTag<t>)                      \

#define DEFINE_TYPE(t)                                              \
	const Type* GetTypeImpl(TypeTag<t>)                             \
	{                                                               \
		static Type type{ STRINGIFY(t), sizeof(t) };                \
		return &type;                                               \
	}

namespace TinyReflect
{
	extern const Type* GetTypeImpl(TypeTag<void>);

	DEFINE_TYPE_EXTERN(float);
	DEFINE_TYPE_EXTERN(int8_t);
	DEFINE_TYPE_EXTERN(int16_t);
	DEFINE_TYPE_EXTERN(int32_t);
	DEFINE_TYPE_EXTERN(int64_t);
	DEFINE_TYPE_EXTERN(uint8_t);
	DEFINE_TYPE_EXTERN(uint16_t);
	DEFINE_TYPE_EXTERN(uint32_t);
	DEFINE_TYPE_EXTERN(uint64_t);
}