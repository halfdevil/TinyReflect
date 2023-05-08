#include "JsonWriter.h"
#include "FileWriter.h"
#include "Field.h"
#include "DefaultTypes.h"

namespace TinyReflect
{
	JsonWriter::JsonWriter()
	{
		mCurrent = &mRoot;
		mJsonStack.push(mCurrent);
	}

	std::string JsonWriter::toString(uint32_t numSpaces) const
	{
		return mRoot.dump(numSpaces);
	}

	void JsonWriter::write(const std::string& fileName) const
	{
		
	}

	void JsonWriter::classBegin(const Class* c, int32_t depth, const void* instance)
	{
	}

	void JsonWriter::classEnd(const Class* c, int32_t depth)
	{
		popCurrent();
	}

	void JsonWriter::classMember(const Field* f, int32_t depth)
	{
		pushCurrent(f->getName());
	}

	void JsonWriter::arrayBegin(const Type* t, int32_t depth, int32_t length, const void* instance)
	{

	}

	void JsonWriter::arrayEnd(const Type* t, int32_t depth)
	{
		popCurrent();
	}

	void JsonWriter::arrayElement(const Type* t, int32_t depth, int32_t elem)
	{		
		if (mCurrent != nullptr)
		{
			mCurrent->push_back(json());

			json& newElement = mCurrent->back();
			mCurrent = &newElement;
			mJsonStack.push(mCurrent);
		}
	}

	void JsonWriter::vectorBegin(const Type* t, int32_t depth, int32_t length, const void* instance)
	{

	}

	void JsonWriter::vectorEnd(const Type* t, int32_t depth)
	{
		popCurrent();
	}

	void JsonWriter::vectorElement(const Type* t, int32_t depth, int32_t elem)
	{
		if (mCurrent != nullptr)
		{
			mCurrent->push_back(json());

			json& newElement = mCurrent->back();
			mCurrent = &newElement;
			mJsonStack.push(mCurrent);
		}
	}

	void JsonWriter::mapBegin(const Type* t, int32_t depth, int32_t count, const void* instance)
	{

	}

	void JsonWriter::mapEnd(const Type* t, int32_t depth)
	{
		popCurrent();
	}

	void JsonWriter::mapElement(const Type* kt, const Type* vt, int32_t depth, const void* key)
	{
		if (mCurrent != nullptr)
		{
			if (kt->getHash() == GetType<std::string>()->getHash())
			{
				std::string keyStr = *((std::string*)key);
				pushCurrent(keyStr.c_str());
			}
		}
	}

	void JsonWriter::enumElement(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				*mCurrent = json("nullptr");
				return;
			}

			*mCurrent = json(*((uint32_t*)instance));

			popCurrent();
		}
	}

	void JsonWriter::primitive(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				*mCurrent = json("nullptr");
				return;
			}

			if (t->getHash() == GetType<bool>()->getHash())
			{
				*mCurrent = json(*((bool*)instance));
			}
			else if (t->getHash() == GetType<float>()->getHash())
			{
				*mCurrent = json(*((float*)instance));
			}
			else if (t->getHash() == GetType<int8_t>()->getHash())
			{
				*mCurrent = json(*((int8_t*)instance));
			}
			else if (t->getHash() == GetType<uint8_t>()->getHash())
			{
				*mCurrent = json(*((uint8_t*)instance));
			}
			else if (t->getHash() == GetType<int16_t>()->getHash())
			{
				*mCurrent = json(*((int16_t*)instance));
			}
			else if (t->getHash() == GetType<uint16_t>()->getHash())
			{
				*mCurrent = json(*((uint16_t*)instance));
			}
			else if (t->getHash() == GetType<int32_t>()->getHash())
			{
				*mCurrent = json(*((int32_t*)instance));
			}
			else if (t->getHash() == GetType<uint32_t>()->getHash())
			{
				*mCurrent = json(*((uint32_t*)instance));
			}
			else if (t->getHash() == GetType<int64_t>()->getHash())
			{
				*mCurrent = json(*((int64_t*)instance));
			}
			else if (t->getHash() == GetType<uint64_t>()->getHash())
			{
				*mCurrent = json(*((uint64_t*)instance));
			}

			popCurrent();
		}
	}

	void JsonWriter::stringPrimitive(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				*mCurrent = json("nullptr");
				return;
			}
			
			const char** str = (const char**)instance;
			*mCurrent = json(*str);

			popCurrent();
		}
	}

	void JsonWriter::stringElement(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				*mCurrent = json("nullptr");
				return;
			}

			const std::string* str = (const std::string*)instance;
			*mCurrent = json(*str);

			popCurrent();
		}
	}

	void JsonWriter::pushCurrent(const char* name)
	{
		if (mCurrent != nullptr)
		{
			(*mCurrent)[name] = json();
			mCurrent = &((*mCurrent)[name]);
			mJsonStack.push(mCurrent);
		}
	}

	void JsonWriter::popCurrent()
	{
		mJsonStack.pop();
		if (!mJsonStack.empty())
		{
			mCurrent = mJsonStack.top();
		}
		else
		{
			mCurrent = nullptr;
		}
	}
}