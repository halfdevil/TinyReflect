#pragma once

#include <cstdint>
#include <string>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

namespace TinyReflect
{
	enum class FileOpenMode
	{
		OpenRead,
		OpenWrite,
		Append
	};

	enum class SeekOrigin
	{
		Beginning,
		Current,
		End
	};

	class File
	{
	public:

		File() = default;
		virtual ~File();

		FileOpenMode getOpenMode() const
		{
			return mOpenMode;
		}

		bool canRead() const
		{
			return mOpenMode == FileOpenMode::OpenRead;
		}

		bool canWrite() const
		{
			return mOpenMode == FileOpenMode::OpenWrite;
		}

		uint32_t getSize() const
		{
			return mSize;
		}

		uint32_t getPosition() const
		{
			return mPosition;
		}

		const fs::path& getPath() const
		{
			return mPath;
		}

		virtual bool create(const fs::path& filePath, FileOpenMode fileOpenMode);
		virtual void close();

		virtual bool isEOF() const;
		virtual bool seek(SeekOrigin origin, int32_t offset);
		virtual bool read(void* data, uint32_t size);
		virtual bool write(const void* data, uint32_t size);

	protected:

		FileOpenMode mOpenMode{ FileOpenMode::OpenRead };
		uint32_t mSize{ 0 };
		uint32_t mPosition{ 0 };
		fs::path mPath;
		std::fstream mHandle;
	};
}