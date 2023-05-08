#include "DefaultTypes.h"

namespace TinyReflect
{
	const Type* GetTypeImpl(TypeTag<void>)
	{
		static Type type{ "void", 0 };
		return &type;
	}

	DEFINE_TYPE(bool);
	DEFINE_TYPE(float);
	DEFINE_TYPE(int8_t);
	DEFINE_TYPE(int16_t);
	DEFINE_TYPE(int32_t);
	DEFINE_TYPE(int64_t);
	DEFINE_TYPE(uint8_t);
	DEFINE_TYPE(uint16_t);
	DEFINE_TYPE(uint32_t);
	DEFINE_TYPE(uint64_t);
}