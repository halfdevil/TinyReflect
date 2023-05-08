#include "Type.h"
#include <functional>
#include <string>

namespace TinyReflect
{
	Type::Type(const char* name, uint32_t size) : 
		mName(name), 
		mSize(size)
	{
		calculateHash();
	}

	bool Type::isRecord() const
	{
		return false;
	}

	bool Type::isEnum() const
	{
		return false;
	}

	void Type::calculateHash()
	{
		mHash = std::hash<std::string>{}(std::string(mName));
	}

	template <typename T>
	const Type* GetTypeImpl(TypeTag<T>)
	{
		static Type type{ TypeName<T>::get(), TypeName<T>::get(), sizeof(T) };
		return &type;
	};
}