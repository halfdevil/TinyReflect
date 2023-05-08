#pragma once

#include "File.h"
#include <vector>
#include <unordered_map>

namespace TinyReflect
{
	class FileReader
	{
	public:

		FileReader(File& file)
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

		bool isEOF() const
		{
			return mFile.isEOF();
		}

		template <typename T>
		bool read(T* data, uint32_t count = 1)
		{
			return mFile.read(data, sizeof(T) * count);
		}

		std::string readAsString();
		std::string readString();

		bool seek(SeekOrigin origin, uint32_t offset);

	private:

		File& mFile;
	};
}