#pragma once

#include "File.h"
#include <vector>
#include <unordered_map>

namespace TinyReflect
{
	class FileWriter
	{
	public:

		FileWriter(File& file)
			: mFile(file)
		{
		}

		const File& getFile() const
		{
			return mFile;
		}

		uint32_t getSize() const
		{
			return mFile.getSize();
		}

		uint32_t getPosition() const
		{
			return mFile.getPosition();
		}

		const fs::path& getPath() const
		{
			return mFile.getPath();
		}

		template <typename T>
		bool write(const T* data, uint32_t count = 1)
		{
			return mFile.write(data, sizeof(T) * count);
		}

		bool writeString(const std::string& str);
		bool seek(SeekOrigin origin, uint32_t offset);

	private:

		File& mFile;
	};
}