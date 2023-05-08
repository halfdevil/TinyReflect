#include "FileReader.h"
#include <vector>
#include <memory>

namespace TinyReflect
{
	std::string FileReader::readAsString()
	{
		const uint32_t len = mFile.getSize();
		std::vector<char> stringBytes(len + 1);

		read(stringBytes.data(), len);
		stringBytes[len] = 0;

		return { stringBytes.data() };
	}

	std::string FileReader::readString()
	{
		const uint32_t len = mFile.getSize();

		std::vector<char> stringBytes(len + 1);
		read(stringBytes.data(), len);
		stringBytes[len] = 0;

		return std::string{ stringBytes.data() };
	}
	
	bool FileReader::seek(SeekOrigin origin, uint32_t offset)
	{
		return mFile.seek(origin, offset);
	}
}