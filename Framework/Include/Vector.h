#pragma once

#include <vector>

namespace TinyReflect
{
	class VectorBase
	{
	public:

		virtual void Resize(uint32_t newSize) = 0;
	};

	template <typename T>
	class Vector : public std::vector<T>, public VectorBase
	{
	public:

		using VectorT = std::vector<T>;
		using VectorT::VectorT;

		virtual void Resize(uint32_t newSize) override
		{
			VectorT::resize(newSize);
		}
	};
}