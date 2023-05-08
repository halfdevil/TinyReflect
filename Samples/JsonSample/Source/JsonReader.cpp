#include "JsonReader.h"
#include "Field.h"
#include "DefaultTypes.h"
#include "Vector.h"
#include "Map.h"

namespace TinyReflect
{
	JsonReader::JsonReader()
	{
	}

	void JsonReader::fromString(const std::string& jsonStr)
	{
		mRoot = json::parse(jsonStr);
		mCurrent = &mRoot;
		mJsonStack.push(mCurrent);
	}

	void JsonReader::read(const std::string& fileName)
	{
		
	}

	void JsonReader::classBegin(const Class* c, int32_t depth, const void* instance)
	{
		
	}

	void JsonReader::classEnd(const Class* c, int32_t depth)
	{
		popCurrent();
	}

	void JsonReader::classMember(const Field* f, int32_t depth)
	{
		pushCurrent(f->getName());
	}

	void JsonReader::arrayBegin(const Type* t, int32_t depth, int32_t length, const void* instance)
	{

	}

	void JsonReader::arrayEnd(const Type* t, int32_t depth)
	{
		popCurrent();
	}

	void JsonReader::arrayElement(const Type* t, int32_t depth, int32_t elem)
	{
		if (mCurrent != nullptr)
		{
			json& newElement = (*mCurrent)[elem];
			mCurrent = &newElement;
			mJsonStack.push(mCurrent);
		}
	}

	void JsonReader::vectorBegin(const Type* t, int32_t depth, int32_t length, const void* instance)
	{
		if (!instance)
		{
			return;
		}

		VectorBase* vectorBase = (VectorBase*)instance;
		vectorBase->Resize((uint32_t)mCurrent->size());
	}

	void JsonReader::vectorEnd(const Type* t, int32_t depth)
	{
		popCurrent();
	}

	void JsonReader::vectorElement(const Type* t, int32_t depth, int32_t elem)
	{
		if (mCurrent != nullptr)
		{
			json& newElement = (*mCurrent)[elem];
			mCurrent = &newElement;
			mJsonStack.push(mCurrent);
		}
	}

	void JsonReader::mapBegin(const Type* t, int32_t depth, int32_t count, const void* instance)
	{
		if (!instance)
		{
			return;
		}

		MapBase* mapBase = (MapBase*)instance;
		for (auto& [key, val] : mCurrent->items())
		{
			mapBase->InsertDefault(key);
		}
	}

	void JsonReader::mapEnd(const Type* t, int32_t depth)
	{
	}

	void JsonReader::mapElement(const Type* kt, const Type* vt, int32_t depth, const void* key)
	{
		const std::string* keyStr = (const std::string*)key;
		pushCurrent(keyStr->c_str());
	}

	void JsonReader::enumElement(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				return;
			}

			*((uint32_t*)instance) = mCurrent->get<uint32_t>();
			popCurrent();
		}
	}

	void JsonReader::primitive(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				return;
			}

			if (t->getHash() == GetType<bool>()->getHash())
			{
				*((bool*)instance) = mCurrent->get<bool>();
			}
			else if (t->getHash() == GetType<float>()->getHash())
			{
				*((float*)instance) = mCurrent->get<float>();
			}
			else if (t->getHash() == GetType<int8_t>()->getHash())
			{
				*((int8_t*)instance) = mCurrent->get<int8_t>();
			}
			else if (t->getHash() == GetType<uint8_t>()->getHash())
			{
				*((uint8_t*)instance) = mCurrent->get<uint8_t>();
			}
			else if (t->getHash() == GetType<int16_t>()->getHash())
			{
				*((int16_t*)instance) = mCurrent->get<int16_t>();
			}
			else if (t->getHash() == GetType<uint16_t>()->getHash())
			{
				*((uint16_t*)instance) = mCurrent->get<uint16_t>();
			}
			else if (t->getHash() == GetType<int32_t>()->getHash())
			{
				*((int32_t*)instance) = mCurrent->get<int32_t>();
			}
			else if (t->getHash() == GetType<uint32_t>()->getHash())
			{
				*((uint32_t*)instance) = mCurrent->get<uint32_t>();
			}
			else if (t->getHash() == GetType<int64_t>()->getHash())
			{
				*((int64_t*)instance) = mCurrent->get<int64_t>();
			}
			else if (t->getHash() == GetType<uint64_t>()->getHash())
			{
				*((uint64_t*)instance) = mCurrent->get<uint64_t>();
			}

			popCurrent();
		}
	}

	void JsonReader::stringPrimitive(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				return;
			}

			popCurrent();
		}
	}

	void JsonReader::stringElement(const Type* t, const void* instance)
	{
		if (mCurrent != nullptr)
		{
			if (!instance)
			{
				return;
			}

			std::string* str = (std::string*)instance;
			*str = mCurrent->get<std::string>();

			popCurrent();
		}
	}

	void JsonReader::pushCurrent(const char* name)
	{
		if (mCurrent != nullptr)
		{
			mCurrent = &((*mCurrent)[name]);
			mJsonStack.push(mCurrent);
		}
	}

	void JsonReader::popCurrent()
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