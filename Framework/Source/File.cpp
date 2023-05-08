#include "File.h"
#include <iostream>

namespace TinyReflect
{
	File::~File()
	{
		close();
	}

	bool File::create(const fs::path& filePath, FileOpenMode fileOpenMode)
	{
		std::ios_base::openmode fileMode = std::ios::binary;

		switch (fileOpenMode)
		{
		case FileOpenMode::OpenRead:
			fileMode = std::ios::in | fileMode;
			break;

		case FileOpenMode::OpenWrite:
			fileMode = std::ios::out | fileMode;
			break;

		case FileOpenMode::Append:
			fileMode = std::ios::app | fileMode;
			break;

		default:
			break;
		}

		mHandle.open(filePath.string(), fileMode);
		if (!mHandle.good())
		{
			std::cerr << "Unable to open file: %s" << filePath.string() << std::endl;
			return false;
		}

		mHandle.seekg(0, mHandle.end);
		mSize = (uint32_t)mHandle.tellg();
		mHandle.seekg(0, mHandle.beg);

		mOpenMode = fileOpenMode;
		mPath = filePath;

		return true;
	}

	void File::close()
	{
		if (mHandle.is_open())
		{
			mHandle.close();
		}
	}

	bool File::isEOF() const
	{
		return mHandle.eof() || !mHandle.good();
	}

	bool File::seek(SeekOrigin origin, int32_t offset)
	{
		switch (origin)
		{
		case SeekOrigin::Beginning:
			mHandle.seekg(offset, mHandle.beg);
			break;

		case SeekOrigin::Current:
			mHandle.seekg(offset, mHandle.cur);
			break;

		case SeekOrigin::End:
			mHandle.seekg(offset, mHandle.end);
			break;

		default:
			break;
		}

		mPosition = (uint32_t)mHandle.tellg();
		return true;
	}

	bool File::read(void* data, uint32_t size)
	{
		if (!canRead())
		{
			std::cerr << "File not opened for reading: " << mPath.string() << std::endl;
			return false;
		}

		if (mHandle.eof())
		{
			return true;
		}

		mHandle.read((char*)data, size);

		if (!mHandle.good() && !mHandle.eof())
		{
			std::cerr << "Error reading from file: " << mPath.string() << std::endl;
			return false;
		}

		mPosition = (uint32_t)mHandle.tellg();
		return true;
	}

	bool File::write(const void* data, uint32_t size)
	{
		if (!canWrite())
		{
			std::cerr << "File not opened for writing: " << mPath.string() << std::endl;
			return false;
		}

		mHandle.write((const char*)data, size);

		if (!mHandle.good())
		{
			std::cerr << "Error writing to file: " << mPath.string() << std::endl;
			return false;
		}

		mPosition = (uint32_t)mHandle.tellg();
		return true;
	}
}