#pragma once

namespace TinyReflect
{
	template <typename T>
	class Iterator
	{
	public:

		Iterator(const T* inBegin, const T* inEnd)
			: mBegin(inBegin), mEnd(inEnd)
		{
		}

		const T* begin() const
		{
			return mBegin;
		}

		const T* end() const
		{
			return mEnd;
		}

		size_t length() const
		{
			return mEnd - mBegin;
		}

		const T& operator[](size_t idx) const
		{
			return mBegin[idx];
		}

	private:

		const T* mBegin{ nullptr };
		const T* mEnd{ nullptr };
	};
}